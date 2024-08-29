#include <SoftwareSerial.h>
#include <DFRobot_mmWave_Radar.h>

int LED_BLINK = 2;

SoftwareSerial mySerial(12, 14);
DFRobot_mmWave_Radar sensor(&mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(LED_BLINK, OUTPUT);

  sensor.factoryReset();      
  sensor.DetRangeCfg(0, 0.6);    
  sensor.OutputLatency(0, 0);  
}

void loop() {
  int val = sensor.readPresenceDetection();
  digitalWrite(LED_BLINK, val);
  Serial.println(val);
  delay(1000);
}
