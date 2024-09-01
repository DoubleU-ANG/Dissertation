# Dissertation: Connected Seat System
## Introduction: 
Smart Connected Seats serve as a helpful guide in public places like libraries and teaching theatres, assisting people in finding available and suitable seating. The Smart Connected Seats system combines a sensor-enabled chair and data communication centre. Every chair includes a millimetre-wave radar, to detect if someone is sitting down, along with sensors for carbon dioxide, temperature, humidity and light, to monitor the surrounding environment to ensure comfort. The communication centre visualises the data from the sensors. It includes model of the chairs, which rise when someone sits on real chairs, and an e-ink display to communicate the environmental conditions. 

## Hypothesis: 
How can a smart connected seat system using millimeter-wave radar and various environmental sensors help people to find a seat with better learning or working experience.

## Aims:
This project aims to implementing a smart Internet of Things (IoT) strategy on chairs, in order to transform the way we interact with these spaces

## Methodologies:
The Smart Connected System includes smart chair detector equipped with few sensors and physical twins of chair.

Project Overview:

<img src="Picture/overview.png" height="350em" />

### Hardware:

#### Hardware List:

##### 1. Microcontrollers:
ESP8266 HUZZAH (Smart Chair Detector)
ESP32 E-paper screen driver board (Communication Center)

##### 2. Sensors:
This project use mm-Wave radar SEN0395, CO2, temperature and humidity sensor SCD30, and light sensor TCS3472. Use the code provided to test each sensor before integration.

SEN0395:

<img src="Picture/SEN0395.png" height="200em" />

SCD30:

<img src="Picture/SCD30.png" height="200em" />

TCS3472:

<img src="Picture/TCS3472.png" height="200em" />

##### 3. Actuators:
Actuators are mainly used in communication center, they are: servos, LED rings and OLED screens.

#### Circuit:
##### Circuit Connection:
Connect all the sensor as the schematic shown as below:

Smart chair detector circuit schematic:

<img src="Picture/SMART CHAIR DETECTOR CIRCUIT SCHEMATIC.png" height="500em" />

<img src="Picture/Smart Chair First Circuit Prototype.jpg" height="500em" />

Communication center circuit schematic:

<img src="Picture/Communication Center Circuit Schematic.png" height="500em" />

<img src="Picture/Control Center First Circuit.jpg" height="500em" />

It worth noting that when connect two OLED screens to circuit, physical address of one of them should be changed by soldering the resister behind the screen (shown as picture below) to another position for another address, otherwise the microcontroller is not able to recognise these two screens. It has two physical address； 0x78 and 0x7A，and 0x78 is the default one.

0x78；

<img src="Picture/OLED screen 1.png" height="500em" />

0x7A:(manually modification needed)

<img src="Picture/OLED screen 2.png" height="500em" />

After successfully assembling the circuit board and connecting all components, test the circuit functions in Arduino IDE by uploding the code provided to the microcontroller.

Code for smart chair detector:

<img src="Picture/codecc.png" height="500em" />

Code for communication center:

<img src="Picture/codescd.png" height="500em" />

##### Printed Circuit Board (PCB)
PCB has been designed for ensuring a more stable and wireless circuit. You can build your own PCB or modified mine which I designed on LCEDA according to your project.

<img src="Picture/PCB Detector.jpg" height="400em" />

<img src="Picture/Smart Chair PCB Design.jpg" height="500em" />

<img src="Picture/PCB CC.jpg" height="400em" />

<img src="Picture/PCB CC PROTOTYPE.jpg" height="500em" />

#### Enclosure：
Custom-designed enclosures were developed for the circuit boards, sensors and actuators to facilitate their deployment in targeted scenarios. You can build your own enclosure or modified mine on Fusion 360 according to your project.

Smart Chair Detector Enclosure:

<img src="Picture/SCD enclosure.jpg" height="300em" />

Base of Communication Center:

<img src="Picture/base11.jpg" height="350em" />

<img src="Picture/base22.jpg" height="350em" />

Servo Holder:

<img src="Picture/sh.jpg" height="200em" />

Top of Communication Center

<img src="Picture/TOP3.jpg" height="350em" />

<img src="Picture/TOP4.jpg" height="200em" />

Chair Holder:

<img src="Picture/chair holder1.jpg" height="200em" />

<img src="Picture/chair holder2.jpg" height="200em" />

Chair:

<img src="Picture/chair.jpg" height="200em" />

## Result:

Smart Chair Detector:

<img src="Picture/SMART CHAIR DETECTOR.jpg" height="300em" />

Deployment:

<img src="Picture/deployment1.jpg" height="350em" /> <img src="Picture/deployment2.jpg" height="350em" />

Communication Center:

<img src="Picture/NORMAL.jpg" height="500em" />

When people sit on one of the chair:

<img src="Picture/people.jpg" height="500em" />

## Steps for recreation:

1. Prepare the hardware needed.

2. Connect all the components and test the functions by code. Remember to replace the key information for WiFi and MQTT broker with your own one.

3. Design your PCB (optional) and Enclosure or modified mine according to your own requirement.

4. Assemble all the electronic components and enclosure.

5. Run the code and deploy on your chair
