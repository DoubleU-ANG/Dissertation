#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN0 4 // On Trinket or Gemma, suggest changing this to 1
#define PIN1 16
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
 clock_prescale_set(clock_div_1);
#endif
 pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 pixels1.begin();
}

void loop() {
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
}