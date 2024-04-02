//Davide D'Alessandri
// 24 VL63L4CX senssors using a demultiplexer, stream output to a slave via esp_now
// Work with esp32 microcontrollers
//setup and read divided in differents files


#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "TCA9548A.h"
#include "SparkFun_VL53L1X.h"

long int t1;
long int t2;

// REPLACE WITH THE RECEIVER'S MAC Address
//uint8_t broadcastAddress[] = {0x84,0xF7,0x03,0xE3,0x37,0xF2}; //ESP32 s2
//uint8_t broadcastAddress[] = {0xC8,0xF0,0x9E,0x47,0xE5,0x54}; //ESP32
//uint8_t broadcastAddress[] = {0xF4,0x12,0xFA,0x56,0x3C,0x20}; //ESP32 s3
//uint8_t broadcastAddress[] = {0x34,0x85,0x18,0xAA,0xC5,0x40}; //ESP32 s3 display
uint8_t broadcastAddress[] = {0xD4,0xD4,0xDA,0x97,0xF3,0x74}; //lilzGo Lite

TCA9548A I2CMux(0x70);                  // Address can be passed into the constructor
TCA9548A I2CMux1(0x73);
TCA9548A I2CMux2(0x77);
SFEVL53L1X distanceSensor0, distanceSensor1, distanceSensor2, distanceSensor3, distanceSensor4, distanceSensor5, distanceSensor6, distanceSensor7;
SFEVL53L1X distanceSensor10, distanceSensor11, distanceSensor12, distanceSensor13, distanceSensor14, distanceSensor15, distanceSensor16, distanceSensor17;
SFEVL53L1X distanceSensor20, distanceSensor21, distanceSensor22, distanceSensor23, distanceSensor24, distanceSensor25, distanceSensor26, distanceSensor27;

int timeBudget = 20;  //Set the timing budget for a measurement in ms [15-20-33-50-100(def)-200-500]
int mesPeriod = 20;   //Intermeasurement period must be >/= timing budget

//Boolean to don't read value if strip is not connected
boolean strip0 = true;
boolean strip1 = true;
boolean strip2 = true;

int distance0;
int distance1;
int distance2;
int distance3;
int distance4;
int distance5;
int distance6;
int distance7;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int id; // must be unique for each sender board
    int st;
    int d0;
    int d1;
    int d2;
    int d3;
    int d4;
    int d5;
    int d6;
    int d7;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {//----------------------------------------<=SETUP-----------------
// Init Serial Monitor
  Serial.begin(115200);

  I2CMux.begin(Wire);
  I2CMux.closeAll();
  I2CMux1.begin(Wire);
  I2CMux1.closeAll();
  I2CMux2.begin(Wire);
  I2CMux2.closeAll();

  strip0 = true;
  strip1 = true;
  strip2 = true;

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  //sensor_setup
  setupSensors();
  setupSensors1();
  setupSensors2();

  Serial.println("Sensor configuration ok");

}

void loop() {//----------------------------------------<=LOOP-------------------

//read sensors data and sendit to slave
for(int i=0; i<=2; i++){
  t1 = millis();
  if(strip0 && i==0){
    //t1 = millis();
    readSensors();
    sendData(i);
  }

  if(strip1 && i==1){
    readSensors1();
    sendData(i);
  }

  if(strip2 && i==2){
    readSensors2();
    sendData(i);
    t2 = millis();
    Serial.print("Time taken by the task: "); Serial.print(t2-t1); Serial.println(" milliseconds");
    Serial.println("");
  }

}

}

void sendData(int i){
  // Set values to send
  myData.id = 1;
  myData.st = i;
  myData.d0 = distance0;
  myData.d1 = distance1;
  myData.d2 = distance2;
  myData.d3 = distance3;
  myData.d4 = distance4;
  myData.d5 = distance5;
  myData.d6 = distance6;
  myData.d7 = distance7;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

}