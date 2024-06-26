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
#include "SSD1306Wire.h"

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

#define     OLED_SCL       22
#define     OLED_SDA       21
SSD1306Wire  display(0x3c, OLED_SDA, OLED_SCL);

//-----------------------------------------------------------------------------------------------

int distanceArray[8] = {0};
int distanceMinArray[3] = {0};
int minMinDistance = 0;
int roundedRssiScaled = 0;
int rssi = 0;

int minMinPosition = 0;
int MinPositionLocation = 0;
int distanceMinPosition[3] = {0};

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

int strip;
const int numreadings = 15;

//-------------------------------------MinDistance-------------------------------------
int readings[numreadings];      
long readIndex = 0;              
int total = 0;                 
int average = 0;                

// Create a struct_message called myData
struct_message myData;

// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;

// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};

int getMin(int* array, int size)
{
  int minimum = array[0];
  for (int i = 0; i < size; i++)
  {
    if (array[i] < minimum) minimum = array[i];
  }
  return minimum;
}

int findSmallestPosition(int arr[], int size) {
  int smallest = arr[0];
  int smallestPos = 0;

  for (int i = 1; i < size; i++) {
    if (arr[i] < smallest) {
      smallest = arr[i];
      smallestPos = i;
    }
  }

  return smallestPos;
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];

  memcpy(&myData, incomingData, sizeof(myData));

  strip = myData.st;
  distanceArray[0]  = myData.d0;
  distanceArray[1]  = myData.d7;
  distanceArray[2]  = myData.d1;
  distanceArray[3]  = myData.d6;
  distanceArray[4]  = myData.d2;
  distanceArray[5]  = myData.d5;
  distanceArray[6]  = myData.d3;
  distanceArray[7]  = myData.d4;

  //Limit the measured distance to 1m
  for(int a = 0; a < 8; a++){
    if(distanceArray[a]>1000){
      distanceArray[a]=1000;
    }
  }

  //Find the minimum distace measured and the position where is it measured
  if(strip == 2){
    distanceMinArray[0] = getMin(distanceArray, 8);
    distanceMinPosition[0] = findSmallestPosition(distanceArray,8);
  }

  if(strip == 1){
    distanceMinArray[1] = getMin(distanceArray, 8);
    distanceMinPosition[1] = findSmallestPosition(distanceArray,8);
  }

  if(strip == 0){
    distanceMinArray[2] = getMin(distanceArray, 8);
    distanceMinPosition[2] = findSmallestPosition(distanceArray,8);
  }


  minMinDistance = getMin(distanceMinArray,3);

  total = total - readings[readIndex];
  readings[readIndex] = minMinDistance;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numreadings) {
    readIndex = 0;
  }
  minMinDistance = total / numreadings;
  
  minMinPosition = findSmallestPosition(distanceMinArray,3);

  MinPositionLocation = minMinPosition << 3 | distanceMinPosition[minMinPosition];


  //---------------------------------------ROS-----------------------------------------------

  char formattedString[150]; 
  snprintf(formattedString, sizeof(formattedString), "%d,%d",
            minMinDistance,
            MinPositionLocation);

  //Print the string to a ROS2 topic
  msg.data.data = formattedString;
  RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
  //*/
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


  display.init();
  display.flipScreenVertically();

  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);

  display.drawString(0, 0, "Micro-ROS");

  display.setFont(ArialMT_Plain_10);

  display.drawString(0, 18, "Please start agent..." );
  display.display();
  
  delay(7000);
  display.drawString(0, 30, "If not working, reboot..." );
  display.display();

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

  display.clear();

  delay(1000);

  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Micro-ROS");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 18, "Configuration: OK" );
  display.display();

  delay(2000);
  display.drawString(0, 30, "Sending data..." );
  display.display();

  delay(18000);

  display.drawString(0, 44, "© Davide D'Alessandri" );
  display.display();

  delay(2000);
  
  display.displayOff();

}

void loop() {
  delay(16);
  RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1)));

}