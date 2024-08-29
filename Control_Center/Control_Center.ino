#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"
#include <PubSubClient.h>
#include <stdlib.h>
#include <WiFi.h>
#include <ezTime.h>
#include "SPIFFS.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include <ESP32Servo.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN0 4 // On Trinket or Gemma, suggest changing this to 1
#define PIN1 16
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size
#define OLED_ADDR_1 0x3C
#define OLED_ADDR_2 0x3D
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g21(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21);
Servo myservo;
Servo myservo1;
int pos = 0;
int servoPin=18;
int servoPin1=17;

int h = 0; 
int h1 = 0; 
int t = 123;
int t1 = 0;

int uvLevel = 0;
int longtitude = 0;
int latitude = 0;
uint8_t hour = 0;
uint8_t minute = 0;

int light_temperature = 0;
int temperature = 0;
int humidity = 0;
int people = 0;
int light_intensity = 0;
int CO2 = 0;

#define SECRET_SSID "CE-Hub-Student"
#define SECRET_PASS "casa-ce-gagarin-public-service"
#define SECRET_MQTTUSER "student"
#define SECRET_MQTTPASS "ce2021-mqtt-forget-whale"

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

UBYTE *BlackImage;
UWORD Imagesize = ((EPD_7IN5_V2_WIDTH % 8 == 0) ? (EPD_7IN5_V2_WIDTH / 8 ) : (EPD_7IN5_V2_WIDTH / 8 + 1)) * EPD_7IN5_V2_HEIGHT;

PAINT_TIME sys_time;
UWORD width = EPD_7IN5_V2_WIDTH;
UWORD height = EPD_7IN5_V2_HEIGHT;

UWORD line1_y = height / 3;
UWORD line2_y = height * 2 / 3;
UWORD line3_y = width / 2;

unsigned long lastUpdate = 0;  
const unsigned long updateInterval = 10000; 


void moveServoTo180(Servo &servo) {
  for (int pos = 0; pos <= 180; pos += 1) { 
    servo.write(pos);
    delay(20);
  }
}

// Function to move myservo from 180 to 0 degrees
void moveServoTo0(Servo &servo) {
  for (int pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(20);
  }
}

void sentence01()
{
    u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g2.firstPage();
 do
 {
  u8g2.setCursor(5, 15);
  u8g2.print("Hello!");
  u8g2.setCursor(5, 30);
  u8g2.print("I'm better!"); 
  u8g2.setCursor(5, 45);
  u8g2.print("Come and"); 
  u8g2.setCursor(5, 60); 
  u8g2.print("sit on me!"); 
 } while (u8g2.nextPage()); 
}

void sentence11()
{
   u8g21.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g21.firstPage();
 do
 {
  u8g21.setCursor(5, 15);
  u8g21.print("Hello!");
  u8g21.setCursor(5, 30);
  u8g21.print("I'm good!"); 
  u8g21.setCursor(5, 45);
  u8g21.print("Come and"); 
  u8g21.setCursor(5, 60); 
  u8g21.print("sit on me!");
 } while (u8g21.nextPage()); 
}

void sentence02()
{
    u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g2.firstPage();
 do
 {
  u8g2.setCursor(5, 15);
  u8g2.print("   Welcome!");
  u8g2.setCursor(5, 35);
  u8g2.print("  Enjoy your"); 
  u8g2.setCursor(5, 50);
  u8g2.print("  seat here!"); 
 // u8g2.setCursor(5, 60); 

 } while (u8g2.nextPage()); 
}

void sentence12()
{
   u8g21.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g21.firstPage();
 do
 {
  u8g21.setCursor(5, 15);
  u8g21.print("Welcome!");
  u8g21.setCursor(5, 30);
  u8g21.print("Enjoy your"); 
  u8g21.setCursor(5, 45);
  u8g21.print("seat here!"); 
  u8g21.setCursor(5, 60); 
 
 } while (u8g21.nextPage()); 
}

void startWifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void sendMQTT() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  snprintf(msg, 50, "%.0i", t);
  Serial.print("Publish message for t: ");
  Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/rainrate1", msg);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  char buffer[length + 1];
  for (int i = 0; i < length; i++) {
    buffer[i] = (char)payload[i];
    Serial.print(buffer[i]);
  }
  buffer[length] = '\0';
  Serial.println();

  if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/Color Temperature") == 0) {
    light_temperature = atoi(buffer);
    Serial.println("for the Color Temperature");
  } else if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/Light Intensity") == 0) {
    light_intensity = atoi(buffer);
    Serial.println("for the Light Intensity");
  } else if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/Temperature") == 0) {
    temperature = atoi(buffer);
    Serial.println("for the Temperature");
  } else if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/Humidity") == 0) {
    humidity = atoi(buffer);
    Serial.println("for the Humidity");
  } else if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/CO2") == 0) {
    CO2 = atoi(buffer);
    Serial.println("for the CO2");
  } else if (strcmp(topic, "student/CASA0014/plant/ucfnaaf/People") == 0) {
    people = atoi(buffer);
    Serial.println("for the People");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      client.subscribe("student/CASA0014/plant/ucfnaaf/inTopic");
      client.subscribe("student/CASA0014/plant/ucfnaaf/Color Temperature");
      client.subscribe("student/CASA0014/plant/ucfnaaf/Light Intensity");
      client.subscribe("student/CASA0014/plant/ucfnaaf/Temperature");
      client.subscribe("student/CASA0014/plant/ucfnaaf/Humidity");
      client.subscribe("student/CASA0014/plant/ucfnaaf/CO2");
      client.subscribe("student/CASA0014/plant/ucfnaaf/People");
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
 clock_prescale_set(clock_div_1);
#endif
 pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 pixels1.begin();
 u8g2.setI2CAddress(OLED_ADDR_1 << 1); // I2C address needs to be left-shifted by 1
 u8g2.begin();
 u8g2.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
 
 u8g21.setI2CAddress(OLED_ADDR_2 << 1); // I2C address needs to be left-shifted by 1
 u8g21.begin();
 u8g21.enableUTF8Print(); // enable UTF8 support for the Arduino print() function

 ESP32PWM::allocateTimer(0);
 ESP32PWM::allocateTimer(1);
 ESP32PWM::allocateTimer(2);
 ESP32PWM::allocateTimer(3);
 myservo.setPeriodHertz(50);
 myservo.attach(servoPin, 0, 2000); // attaches the servo on pin 18 to the servo object
 myservo1.setPeriodHertz(50);
 myservo1.attach(servoPin1, 0, 2000); // attaches the servo on pin 18 to the servo object
  myservo.write(0);
  myservo.write(1);
  Serial.begin(115200);
  startWifi();
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);

  delay(100);
  DEV_Module_Init();
  EPD_7IN5_V2_Init();
  EPD_7IN5_V2_Clear();
  DEV_Delay_ms(500);

  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    Serial.println("Failed to apply for black memory...");
    while (1);
  }

  Paint_NewImage(BlackImage, EPD_7IN5_V2_WIDTH, EPD_7IN5_V2_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE); 
  Paint_DrawLine(line3_y, 0, line3_y, height, BLACK, DOT_PIXEL_5X5, LINE_STYLE_DOTTED);
  EPD_7IN5_V2_Display(BlackImage);
  delay(500);
   sentence01();
 delay(1000);
 sentence11();
 pixels.clear();
 pixels1.clear();
 pixels.show();
 pixels1.show();
 moveServoTo0(myservo);
 moveServoTo0(myservo1);
}

void loop() { 
  client.loop();
  sendMQTT();
  delay(1000);
  // 检查是否已经超过两分钟
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= updateInterval) {
    lastUpdate = currentMillis;  // 记录这次更新的时间

    // 清空显示并绘制新内容
    Paint_Clear(WHITE); 
    Paint_DrawLine(line3_y, 0, line3_y, height, BLACK, DOT_PIXEL_5X5, LINE_STYLE_DOTTED);
      
    Paint_DrawString_EN(20, 30, "Humidity:", &Font24, WHITE, BLACK);
    Paint_DrawNum(20, 60, humidity, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(60, 60, "%", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(20, 90, "Temperature:", &Font24, WHITE, BLACK);
    Paint_DrawNum(20, 120, temperature, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(60, 120, "C", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(20, 150, "Light Temperature:", &Font24, WHITE, BLACK);
    Paint_DrawNum(20, 180, light_temperature, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(20, 210, "Light Intensity:", &Font24, WHITE, BLACK);
    Paint_DrawNum(20, 240, light_intensity, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(20, 270, "CO2:", &Font24, WHITE, BLACK);
    Paint_DrawNum(20, 300, CO2, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(20, 330, "Available:", &Font24, WHITE, BLACK);
    
    if(people == 1) {
      Paint_DrawString_EN(20, 360, "YES", &Font24, WHITE, BLACK);  
      
      sentence01();
      pixels.clear();
    } else if(people == 2) {
      Paint_DrawString_EN(20, 360, "NO", &Font24, WHITE, BLACK);  
 pixels1.clear(); // Set all pixel colors to 'off'

 for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

 pixels1.setPixelColor(i, pixels.Color(0, 150, 250));

 pixels1.show();
// Pause before next pass through loop
 
 }
          sentence02();
  myservo1.write(180);
    }

    Paint_DrawString_EN(line3_y + 20, 30, "Humidity:", &Font24, WHITE, BLACK);
    Paint_DrawNum(line3_y + 20, 60, humidity, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 60, 60, "%", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 90, "Temperature:", &Font24, WHITE, BLACK);
    Paint_DrawNum(line3_y + 20, 120, temperature, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 60, 120, "C", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 150, "Light Temperature:", &Font24, WHITE, BLACK);
    Paint_DrawNum(line3_y + 20, 180, light_temperature +12, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 210, "Light Intensity:", &Font24, WHITE, BLACK);
    Paint_DrawNum(line3_y + 20, 240, light_intensity -6, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 270, "CO2:", &Font24, WHITE, BLACK);
    Paint_DrawNum(line3_y + 20, 300, CO2, &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 330, "Available:", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(line3_y + 20, 360, "YES", &Font24, WHITE, BLACK);  

    
    EPD_7IN5_V2_Display(BlackImage);
  }
}
