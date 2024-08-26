#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_SCD30.h>
#include <SoftwareSerial.h>
#include <Ticker.h>
#include <DFRobot_mmWave_Radar.h>
int LED_BLINK = 2;

#define SECRET_SSID "CE-Hub-Student"
#define SECRET_PASS "casa-ce-gagarin-public-service"
#define SECRET_MQTTUSER "student"
#define SECRET_MQTTPASS "ce2021-mqtt-forget-whale"

// Ticker timer;

const char* ssid     = SECRET_SSID;
const char* password = SECRET_PASS;
const char* mqttuser = SECRET_MQTTUSER;
const char* mqttpass = SECRET_MQTTPASS;

const char* mqtt_server = "mqtt.cetools.org";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
float temp=0;
float Humi=0;
float CO=0;
int value = 0;
int people = 0;
int people1 = 0;
int people2=0;
int people3=0;
uint16_t r, g, b, c, colorTemp, lux;
int val=-1;

SoftwareSerial mySerial(12, 14);
DFRobot_mmWave_Radar sensor(&mySerial);
Adafruit_SCD30  scd30;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// void onTimer() {
//   sensor.factoryReset();       
//   sensor.DetRangeCfg(0, 0.5);   
//   sensor.OutputLatency(0, 0); 
//     Serial.println("Timer triggered!");
// }

Ticker restartTimer;

void restartESP() {
    Serial.println("Restarting now...");
    ESP.restart();  
}

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  restartTimer.attach(90, restartESP);
    sensor.factoryReset();       
  sensor.DetRangeCfg(0, 0.5);   
  sensor.OutputLatency(0, 0); 
  // timer.attach(90, onTimer);
  mySerial.begin(115200);
  startWifi();
  pinMode(BUILTIN_LED, OUTPUT);     
  digitalWrite(BUILTIN_LED, HIGH);  
  // start MQTT server
  client.setServer(mqtt_server, 1884);
  client.setCallback(callback);
  pinMode(LED_BLINK, OUTPUT);
 
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit SCD30 test!");

  // Try to initialize!
  if (!scd30.begin()) {
    Serial.println("Failed to find SCD30 chip");
    while (1) { delay(10); }
  }
  Serial.println("SCD30 Found!");


  // if (!scd30.setMeasurementInterval(10)){
  //   Serial.println("Failed to set measurement interval");
  //   while(1){ delay(10);}
  // }
  Serial.print("Measurement Interval: "); 
  Serial.print(scd30.getMeasurementInterval()); 
  Serial.println(" seconds");
  
   if (tcs.begin()) {

  Serial.println("Found sensor");

 } else {

  Serial.println("No TCS34725 found ... check your connections");

  while (1);

 }
 
}

void loop() {

    people=0;
    people1=0;
    people2=0;
    people3=0;
    Serial.print(people);
  // put your main code here, to run repeatedly:
  if (scd30.dataReady()){
   // Serial.println("Data available!");

    if (!scd30.read()){ Serial.println("Error reading sensor data"); return; }

    Serial.print("Temperature: ");
    temp=scd30.temperature;
    Serial.print(temp);
    Serial.println(" degrees C");
    
    Serial.print("Relative Humidity: ");
    Humi=scd30.relative_humidity;
    Serial.print(Humi);
    Serial.println(" %");
    
    Serial.print("CO2: ");
    CO=scd30.CO2;
    Serial.print(scd30.CO2, 3);
    Serial.println(" ppm");
    Serial.println("");
  } else {
    //Serial.println("No data");
  }


 tcs.getRawData(&r, &g, &b, &c);

 // colorTemp = tcs.calculateColorTemperature(r, g, b);

 colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);

 lux = tcs.calculateLux(r, g, b);

 Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");

 Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");

 Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");

 Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");

 Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");

 Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");

 Serial.println(" ");

  val = sensor.readPresenceDetection();
  if(val==1)
  {

        Serial.println("People:Yes");
        people=2;
        people1=20;
        people2=200;
        people3=2000;

  }
  else if(val==0)
  {
    Serial.println("People:No");
    people=1;
    people1=10;
    people2=100;
    people3=1000;
  }
  else
  {
    Serial.println("Error");
  }
  delay(1000);

    sendMQTT();
  client.loop();
}

void startWifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // check to see if connected and wait until you are
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


  snprintf (msg, 50, "%.0i", colorTemp);
  // Serial.print("Publish message for t: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/Color Temperature", msg);


  snprintf (msg, 50, "%.0i", lux);
  // Serial.print("Publish message for h: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/Light Intensity", msg);

  //Moisture = analogRead(soilPin);   // moisture read by readMoisture function
  snprintf (msg, 50, "%.0i", people);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/People", msg);

  snprintf (msg, 50, "%.0i", people1);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/People1", msg);

  snprintf (msg, 50, "%.0i", people2);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/People2", msg);

  snprintf (msg, 50, "%.0i", people3);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/People3", msg);

  snprintf (msg, 50, "%.2f", temp);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/Temperature", msg);  

  snprintf (msg, 50, "%.2f", Humi);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/Humidity", msg);

  snprintf (msg, 50, "%.2f", CO);
  // Serial.print("Publish message for m: ");
  // Serial.println(msg);
  client.publish("student/CASA0014/plant/ucfnaaf/CO2", msg);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '2') {
  // Turn the LED on (Note that LOW is the voltage level
  digitalWrite(BUILTIN_LED, LOW);
    // but actually the LED is on; this is because it is active low on the ESP-01)
  } else if((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);

  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect with clientID, username and password
    if (client.connect(clientId.c_str(), mqttuser, mqttpass)) {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe("student/CASA0014/plant/ucfnaaf/People");

      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}