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
}

void loop() {
  u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g2.firstPage();
 do
 {
  u8g2.setCursor(5, 15);
  u8g2.print("Hello!");
  u8g2.setCursor(5, 30);
  u8g2.print("I'm Harry !"); 
  u8g2.setCursor(5, 45);
  u8g2.print("So happy to be"); 
  u8g2.setCursor(5, 60); 
  u8g2.print("in the CElab!");
 } while (u8g2.nextPage()); 
 
 delay(1000);
 u8g21.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g21.firstPage();
 do
 {
  u8g21.setCursor(5, 15);
  u8g21.print("Hello!");
  u8g21.setCursor(5, 30);
  u8g21.print("I'm Wang!"); 
  u8g21.setCursor(5, 45);
  u8g21.print("So happy to be"); 
  u8g21.setCursor(5, 60); 
  u8g21.print("in the CElab!");
 } while (u8g21.nextPage()); 
 
 delay(1000);
 pixels.clear(); // Set all pixel colors to 'off'

for(int i=0; i<NUMPIXELS; i++) { // For each pixel...


 pixels.setPixelColor(i, pixels.Color(0, 150, 250));
 
 pixels.show(); 
 delay(DELAYVAL); // Pause before next pass through loop
}
 pixels1.clear(); // Set all pixel colors to 'off'

 for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

 pixels1.setPixelColor(i, pixels.Color(0, 150, 250));

 pixels1.show();
 delay(DELAYVAL); // Pause before next pass through loop
 
 }
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  myservo.write(pos);
  delay(20); 
 }
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(pos);
  delay(20);
 }

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  myservo1.write(pos);
  delay(20); 
 }
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo1.write(pos);
  delay(20);
 }
}