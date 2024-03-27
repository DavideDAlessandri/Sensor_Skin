//Davide D'Alessandri Nov22 2023
//Flexible skin value trasmitter via serial to ROS2 topic

#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/string.h>

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only avaliable for Arduino framework with serial transport.
#endif

rcl_publisher_t publisher;
std_msgs__msg__String msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

//-----------------------------------------------------------------------------------------------

int roundedRssiScaled = 0;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  int st;
  int d0;
  int d1;
  int d2;
  int d3;
  int d4;
  int d5;
  int d6;
  int d7;
}struct_message;

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];

  memcpy(&myData, incomingData, sizeof(myData));

  boardsStruct[myData.id-1].d0 = myData.d0;
  boardsStruct[myData.id-1].d1 = myData.d7;
  boardsStruct[myData.id-1].d2 = myData.d1;
  boardsStruct[myData.id-1].d3 = myData.d6;
  boardsStruct[myData.id-1].d4 = myData.d2;
  boardsStruct[myData.id-1].d5 = myData.d5;
  boardsStruct[myData.id-1].d6 = myData.d3;
  boardsStruct[myData.id-1].d7 = myData.d4;

  //Print signal strenght with text:
  //Serial.printf("Signal strength: %d%",(100-roundedRssiScaled));

  char formattedString[150]; 
  snprintf(formattedString, sizeof(formattedString), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
            myData.id,
            myData.st,
            boardsStruct[myData.id - 1].d0,
            boardsStruct[myData.id - 1].d1,
            boardsStruct[myData.id - 1].d2,
            boardsStruct[myData.id - 1].d3,
            boardsStruct[myData.id - 1].d4,
            boardsStruct[myData.id - 1].d5,
            boardsStruct[myData.id - 1].d6,
            boardsStruct[myData.id - 1].d7);

  //Print the string to a ROS2 topic
  msg.data.data = formattedString;
  RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
}

typedef struct {
  unsigned frame_ctrl: 16;
  unsigned duration_id: 16;
  uint8_t addr1[6]; /* receiver address */
  uint8_t addr2[6]; /* sender address */
  uint8_t addr3[6]; /* filtering address */
  unsigned sequence_ctrl: 16;
  uint8_t addr4[6]; /* optional */
} wifi_ieee80211_mac_hdr_t;

typedef struct {
  wifi_ieee80211_mac_hdr_t hdr;
  uint8_t payload[0]; /* network data ended with 4 bytes csum (CRC32) */
} wifi_ieee80211_packet_t;

void promiscuous_rx_cb(void *buf, wifi_promiscuous_pkt_type_t type) {
  // All espnow traffic uses action frames which are a subtype of the mgmnt frames so filter out everything else.
  if (type != WIFI_PKT_MGMT)
    return;

  const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
  const wifi_ieee80211_packet_t *ipkt = (wifi_ieee80211_packet_t *)ppkt->payload;
  const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;

  int rssi = ppkt->rx_ctrl.rssi;
  //Serial.println(rssi);

  float rssiScalsed = (rssi / -120.0) * 100; 
  roundedRssiScaled = static_cast<int>(rssiScalsed);
  //Serial.println(100-roundedRssiScaled);
}

//-----------------------------------------------------------------------------------------------

// Error handle loop
void error_loop() {
  while(1) {
    delay(100);
  }
}

void setup() {
  // Configure serial transport
  Serial.begin(115200);
  set_microros_serial_transports(Serial);
  delay(2000);

  allocator = rcl_get_default_allocator();

  //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support));

  // create publisher
  RCCHECK(rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
    "micro_ros_platformio_node_publisher"));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_timer(&executor, &timer));

  //-----------------------------------------------------------------------------------------

  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    //Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);
}

void loop() {
  delay(16);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1)));
}
