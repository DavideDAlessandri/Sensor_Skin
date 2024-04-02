//Davide D'Alessandri 09.01.2024
// 24 VL63L4CX senssors using a demultiplexer, stream input form max 3 master via esp_now
// Data are send via TCP-IP, usiong ethernet library
// Work with LilyGo ethernet and display

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <SPI.h>
#include <Ethernet.h>
#include "SSD1306Wire.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

#define MYIPADDR 192,168,1,28
#define MYIPMASK 255,255,255,0
#define MYDNS 192,168,0,1
#define MYGW 192,168,0,1

#define     ETH_RST         4
#define     ETH_CS          5
#define     ETH_SCLK       18
#define     ETH_MISO       23
#define     ETH_MOSI       19
#define     OLED_SCL       22
#define     OLED_SDA       21
SSD1306Wire  display(0x3c, OLED_SDA, OLED_SCL);

//Set ip andress and port of the server:
EthernetClient client;
IPAddress server(192,168,0,100); 
int serverPort = 8075;

 int val = 0;
 int incrementalVal = 0;   

int distanceArray[8] = {0};
int distanceMinArray[3] = {0};
int minMinDistance = 0;
int roundedRssiScaled = 0;
int rssi = 0;

int minMinPosition = 0;
int MinPositionLocation = 0;
int distanceMinPosition[3] = {0};

unsigned long timer = 0;
long loopTime = 5000;   // microseconds

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

  rssi = ppkt->rx_ctrl.rssi;
  //Serial.println(rssi);

  //*
  float rssiScalsed = (rssi / -120.0) * 100; 
  roundedRssiScaled = 100-(static_cast<int>(rssiScalsed));
  //Serial.println(roundedRssiScaled);
  //*/
}

void ethernetReset(const uint8_t resetPin)
{
    pinMode(resetPin, OUTPUT);
    digitalWrite(resetPin, HIGH);
    delay(250);
    digitalWrite(resetPin, LOW);
    delay(50);
    digitalWrite(resetPin, HIGH);
    delay(350);
}

void setup() {//----------------------------------------------------------------------------------------------

    display.init();
    display.flipScreenVertically();

    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);

    display.drawString(0, 0, "ESP32 W5500 Start");
    display.display();
    
    Serial.begin(115200);
    delay(1000);
    Serial.println("Begin Ethernet");
 
    SPI.begin(ETH_SCLK, ETH_MISO, ETH_MOSI);

    ethernetReset(ETH_RST);
    Ethernet.init(ETH_CS);

    if (Ethernet.begin(mac)) { // Dynamic IP setup
        Serial.println("DHCP OK!");
        display.drawString(0, 12, "DHCP OK!");
        display.display();
    }else{
        Serial.println("Failed to configure Ethernet using DHCP");
        display.drawString(0, 12, "Failed to conf. Ethernet");
        display.display();
        // Check for Ethernet hardware present
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
          Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
          display.drawString(0, 24, "shield was not found");
          display.display();
          while (true) {
            delay(1); // do nothing, no point running without Ethernet hardware
          }
        }
        if (Ethernet.linkStatus() == LinkOFF) {
          Serial.println("Ethernet cable is not connected.");
          display.drawString(0, 36, "Cable is not connected.");
          display.display();
        }
 
          IPAddress ip(MYIPADDR);
          IPAddress dns(MYDNS);
          IPAddress gw(MYGW);
          IPAddress sn(MYIPMASK);
          Ethernet.begin(mac, ip, dns, gw, sn);
          Serial.println("STATIC OK!");
    }
    delay(5000);
 
 
    Serial.print("Local IP : ");
    Serial.println(Ethernet.localIP());
    Serial.print("Subnet Mask : ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway IP : ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("DNS Server : ");
    Serial.println(Ethernet.dnsServerIP());
 
   Serial.println("Ethernet Successfully Initialized");
  // if you get a connection, report back via serial:
    Serial.print("Attempting connection to ");
    Serial.print(server);
    Serial.println("...");
    display.drawString(0, 24, "Ethernet initialized");
    display.display();

    // Set tcp-ip port:
    if (client.connect(server,serverPort))
    {
        Serial.print("Connected to server running at ");
        Serial.println(client.remoteIP());
        display.drawString(0, 36, "Connected to server");
        display.display();
    }
    else 
    {
        Serial.println("Connection to server failed.");
        Serial.println("Server disconnected... Restart ESP in ten seconds...");
        display.drawString(0, 36, "Server disc., restarting...");
        display.display();
        delay(10000);
        ESP.restart();
    }

  //Set device as a Wi-Fi Station----------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

  for (int thisReading = 0; thisReading < numreadings; thisReading++) {
    readings[thisReading] = 0;
  }
}//-----------------------------------------------------------------------------------------------------------

void loop() {

  if (client.available() > 0){

    if (!client.connected()) {
        Serial.println("Server disconnected... Restart ESP in five seconds...");
        display.drawString(0, 48, "Server disc., restarting...");
        display.display();
        delay(5000);
        ESP.restart();
    }

    if (client.connected()){
      char val[20];  // value must contain the formatted string
      sprintf(val, "%dA%d", minMinDistance, MinPositionLocation);

      Serial.print(roundedRssiScaled);
      Serial.print(',');
      Serial.println(minMinDistance);

      //Send via TCP/IP
      client.write(val);
    }
    delay(20);
    }
}

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
