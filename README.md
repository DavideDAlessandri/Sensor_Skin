# Sensor skin repository

---
## Hardware
The sensor skin is composed of the actual skin and a receiver:

<img src="https://github.com/DavideDAlessandri/Sensor_Skin/blob/main/Skin/pic/Picture1.png" width="650">

To power the skin please use the special cable included in the box:

<img src="https://github.com/DavideDAlessandri/Sensor_Skin/blob/main/Skin/pic/Picture2.png" width="350">

To program the skin the external USB-to-UART bridge adapter is needed.

---
## Skin
### Requirements
This folder contains the code for the skin. To update the code on the ESP32 microcontroller [Arduino IDE](https://www.arduino.cc/en/software) or  [Arduino CLI](https://www.arduino.cc/pro/software-pro-cli/) is needed. To program ESP32 with Arduino please follow this [tutorial](https://shop.m5stack.com/blogs/news/step-by-step-guide-how-to-program-esp32-with-arduino-ide).

### Usage
This code reads the data of the sensors and sends them to the receiver via ESP-NOW. To send the data to a different receiver the MAC address of the receiver must be changed in the code:

  ```bash
  // REPLACE WITH THE RECEIVER'S MAC Address
//uint8_t broadcastAddress[] = {0xC8,0xF0,0x9E,0x47,0xE5,0x54}; //ESP32
//uint8_t broadcastAddress[] = {0xF4,0x12,0xFA,0x56,0x3C,0x20}; //ESP32 s3
uint8_t broadcastAddress[] = {0xD4,0xD4,0xDA,0x97,0xF3,0x74}; //lilzGo Lite
  ```
  
To find the MAC address of the receiver use the code "get_macAdress" in the receiver folder.

---
## micro-ROS (Receiver)
### Requirements
To update the code on the ESP32 microcontroller PlatformIO is needed:
- PlatformIO [local installation](https://docs.platformio.org/en/stable/core/installation.html) or [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
- PlatformIO Core version 6.1.0 or greater
- PlatformIO needs  `git`, `cmake` and `pip3` to handle micro-ROS internal dependencies:

  ```bash
  apt install -y git cmake python3-pip
  ```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.

### Usage
This folder contains two programs:
- 1 full data: to transmit all sensor data
- 2 position and distance: to transmit only the minimum distance and the sensor measuring the minimum distance

When one of these program is updated on the receiver connect the receiver via USB on a ROS2 computer. on the ROS2 computer start the **micro-ROS agent** by using this docker command:

```bash
# Serial micro-ROS Agent
docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:$ROS_DISTRO serial --dev [YOUR BOARD PORT] -v6
```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.

If the microcontroller doesn't send data try to push the reset button. Once the connection is established the sensor data are published on the ROS topic **micro_ros_platformio_node_publisher**. The display of the microcontroller turns off after 20 seconds.

---
## TCP-IP (Receiver)
### Requirements
To update the code on the ESP32 microcontroller [Arduino IDE](https://www.arduino.cc/en/software) or  [Arduino CLI](https://www.arduino.cc/pro/software-pro-cli/) is needed ([tutorial](https://shop.m5stack.com/blogs/news/step-by-step-guide-how-to-program-esp32-with-arduino-ide)).

### Usage
This code allows TCP-IP communication, the receiver is the slave and the robot controller is the master. To allow the communication connect the receiver with an RJ45 cable to the router connected also to the robot controller. Remember to set the **IP address** and the **port** of the server in the code:

```bash
EthernetClient client;
IPAddress server(192,168,0,100); 

// Set tcp-ip port:
if (client.connect(server,8075))
```

Once the connection is established the microcontroller starts to send the data to the master.