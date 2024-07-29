#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Define I2C addresses for the two OLED displays
#define OLED_ADDR_1 0x3C
#define OLED_ADDR_2 0x3D

// Initialize the OLED displays with their respective I2C addresses
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g21(U8G2_R0, /* reset=*/U8X8_PIN_NONE, /* clock=*/22, /* data=*/21);

void setup(void)
{
 u8g2.setI2CAddress(OLED_ADDR_1 << 1); // I2C address needs to be left-shifted by 1
 u8g2.begin();
 u8g2.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
 
 u8g21.setI2CAddress(OLED_ADDR_2 << 1); // I2C address needs to be left-shifted by 1
 u8g21.begin();
 u8g21.enableUTF8Print(); // enable UTF8 support for the Arduino print() function
}

void loop(void)
{ 
 u8g2.setFont(u8g2_font_unifont_t_chinese2); // use chinese2
 u8g2.firstPage();
 do
 {
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
  u8g21.print("I'm !"); 
  u8g21.setCursor(5, 45);
  u8g21.print("So happy to be"); 
  u8g21.setCursor(5, 60); 
  u8g21.print("in the CElab!");
 } while (u8g21.nextPage()); 
 
 delay(1000);
}