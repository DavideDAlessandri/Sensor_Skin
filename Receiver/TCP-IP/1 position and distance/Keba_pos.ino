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

EthernetClient client;
IPAddress server(192,168,0,100); //192,168,0,100 ,192,168,100,100, 192,168,100,103

 int val = 0;
 int incrementalVal = 0;   

int distanceArray[8] = {0};
int distanceMinArray[3] = {0};
int minDistance0 = 0;
int minDistance1 = 0;
int minDistance2 = 0;
int minMinDistance = 0;
int roundedRssiScaled = 0;
int rssi = 0;

int minPosition0 = 0;
int minPosition1 = 0;
int minPosition2 = 0;
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
int distance0;
int distance1;
int distance2;
int distance3;
int distance4;
int distance5;
int distance6;
int distance7;

int oldDistance0, oldDistance1, oldDistance2, oldDistance3, oldDistance4, oldDistance5, oldDistance6, oldDistance7;
int oldDistance10, oldDistance11, oldDistance12, oldDistance13, oldDistance14, oldDistance15, oldDistance16, oldDistance17;
int oldDistance20, oldDistance21, oldDistance22, oldDistance23, oldDistance24, oldDistance25, oldDistance26, oldDistance27;

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
  /*
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  */
  memcpy(&myData, incomingData, sizeof(myData));
  // Serial.printf("Board %u, Strip %u: ", myData.id, myData.st);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].d0 = myData.d0;
  boardsStruct[myData.id-1].d1 = myData.d7;
  boardsStruct[myData.id-1].d2 = myData.d1;
  boardsStruct[myData.id-1].d3 = myData.d6;
  boardsStruct[myData.id-1].d4 = myData.d2;
  boardsStruct[myData.id-1].d5 = myData.d5;
  boardsStruct[myData.id-1].d6 = myData.d3;
  boardsStruct[myData.id-1].d7 = myData.d4;


  strip = myData.st;
  distance0 = boardsStruct[myData.id-1].d0;
  distance1 = boardsStruct[myData.id-1].d1;
  distance2 = boardsStruct[myData.id-1].d2;
  distance3 = boardsStruct[myData.id-1].d3;
  distance4 = boardsStruct[myData.id-1].d4;
  distance5 = boardsStruct[myData.id-1].d5;
  distance6 = boardsStruct[myData.id-1].d6;
  distance7 = boardsStruct[myData.id-1].d7;

  if(strip == 2){
    if(distance0>1000){
    distance0=1000;
  }
  if(distance1>1000){
    distance1=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance3>1000){
    distance3=1000;
  }
  if(distance4>1000){
    distance4=1000;
  }
  if(distance5>1000){
    distance5=1000;
  }
  if(distance6>1000){
    distance6=1000;
  }
  if(distance7>1000){
    distance7=1000;
  }


  distanceArray[0] = distance0;
  distanceArray[1] = distance1;
  distanceArray[2] = distance2;
  distanceArray[3] = distance3;
  distanceArray[4] = distance4;
  distanceArray[5] = distance5;
  distanceArray[6] = distance6;
  distanceArray[7] = distance7;

  minDistance0 = getMin(distanceArray, 8);
  minPosition0 = findSmallestPosition(distanceArray,8);

  }

  if(strip == 1){
  if(distance0>1000){
    distance0=1000;
  }
  if(distance1>1000){
    distance1=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance3>1000){
    distance3=1000;
  }
  if(distance4>1000){
    distance4=1000;
  }
  if(distance5>1000){
    distance5=1000;
  }
  if(distance6>1000){
    distance6=1000;
  }
  if(distance7>1000){
    distance7=1000;
  }


  distanceArray[0] = distance0;
  distanceArray[1] = distance1;
  distanceArray[2] = distance2;
  distanceArray[3] = distance3;
  distanceArray[4] = distance4;
  distanceArray[5] = distance5;
  distanceArray[6] = distance6;
  distanceArray[7] = distance7;

  minDistance1 = getMin(distanceArray, 8);
  minPosition1 = findSmallestPosition(distanceArray,8);

  }
  

  if(strip == 0){
  if(distance0>1000){
    distance0=1000;
  }
  if(distance1>1000){
    distance1=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance2>1000){
    distance2=1000;
  }
  if(distance3>1000){
    distance3=1000;
  }
  if(distance4>1000){
    distance4=1000;
  }
  if(distance5>1000){
    distance5=1000;
  }
  if(distance6>1000){
    distance6=1000;
  }
  if(distance7>1000){
    distance7=1000;
  }


  distanceArray[0] = distance0;
  distanceArray[1] = distance1;
  distanceArray[2] = distance2;
  distanceArray[3] = distance3;
  distanceArray[4] = distance4;
  distanceArray[5] = distance5;
  distanceArray[6] = distance6;
  distanceArray[7] = distance7;

  minDistance2 = getMin(distanceArray, 8);
  minPosition2 = findSmallestPosition(distanceArray,8);

  }

  distanceMinArray[0] = minDistance0;
  distanceMinArray[1] = minDistance1;
  distanceMinArray[2] = minDistance2;
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

  distanceMinPosition[0] = minPosition0;
  distanceMinPosition[1] = minPosition1;
  distanceMinPosition[2] = minPosition2;

  MinPositionLocation = minMinPosition << 3 | distanceMinPosition[minMinPosition];


  //sendToPC(&minMinDistance, &roundedRssiScaled, &MinPositionLocation);


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

    // Attempt to connect to the server running at IP address 192.168.1.81 and port 5000.
    if (client.connect(server,8075))
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
      char val[20];  // Assumendo una dimensione sufficientemente grande per contenere la stringa formattata
      sprintf(val, "%dA%d", minMinDistance, MinPositionLocation); //roundedRssiScaled
      //Serial.println((String)minMinDistance + 'A' + MinPositionLocation);
      //*
      incrementalVal=incrementalVal+1;
      Serial.print(roundedRssiScaled);
      Serial.print(',');
      Serial.println(minMinDistance);
      //Serial.print(',');
      //Serial.println(incrementalVal);
      //*/

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
