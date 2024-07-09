/*!
   @file DFRobot_mmWave_Radar.ino
   @可以读取到传感器探测范围内有无人或物在动，可以配置传感器感应区域，可以配置传感器输出延迟时间，可以将传感器恢复出厂设置。
   @n Experimental phenomenon: 传感器设备启动成功后，将在串口显示器上打印0或1，0表示探测范围内没有人或物在动，1表示探测范围内有人或物在动
   @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @licence     The MIT License (MIT)
   @version  V1.0
   @date  2023-3-13
   @https://github.com/DFRobot
*/

#include <SoftwareSerial.h>
#include <DFRobot_mmWave_Radar.h>

int LED_BLINK = 2;

SoftwareSerial mySerial(12, 14);
DFRobot_mmWave_Radar sensor(&mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(LED_BLINK, OUTPUT);

  sensor.factoryReset();       //恢复出厂设置
  sensor.DetRangeCfg(0, 0.6);    //设置感应距离，最远为9m
  sensor.OutputLatency(0, 0);  //设置输出延时
}

void loop() {
  int val = sensor.readPresenceDetection();
  digitalWrite(LED_BLINK, val);
  Serial.println(val);
  delay(1000);
}

