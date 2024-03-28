# Sensor skin repository

## Hardware
The sensor skin is composed of the actual skin and a receiver:
<img src="https://github.com/DavideDAlessandri/Sensor_Skin/blob/main/Skin/pic/Picture1.png" width="650">

To power the skin please use the special cable included in the box:

<img src="https://github.com/DavideDAlessandri/Sensor_Skin/blob/main/Skin/pic/Picture2.png" width="350">

To program the skin the external USB-to-UART bridge adapter is needed.

---
## micro-ROS
### Structure
This folder contains the PlatformIO project that enables the communication of the sensor data to a ROS topic. 

### Requirements
- PlatformIO [local installation](https://docs.platformio.org/en/stable/core/installation.html) or [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
- PlatformIO Core version 6.1.0 or greater
- PlatformIO needs  `git`, `cmake` and `pip3` to handle micro-ROS internal dependencies:

  ```bash
  apt install -y git cmake python3-pip
  ```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.


### Usage

Once the project is updated on an ESP32 microcontroller is possible to test the transmission by connecting via USB the microcontroller to a computer with ROS2 installed and with a **micro-ROS Agent** running. 
It is possible to use a **micro-ROS Agent** just by using this docker command:

```bash
# Serial micro-ROS Agent
docker run -it --rm -v /dev:/dev -v /dev/shm:/dev/shm --privileged --net=host microros/micro-ros-agent:$ROS_DISTRO serial --dev [YOUR BOARD PORT] -v6
```

See [micro-ROS for PlatformIO](https://github.com/micro-ROS/micro_ros_platformio) GitHub page for further information.