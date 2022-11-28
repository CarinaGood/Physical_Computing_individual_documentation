// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 8 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_VL53L0X.h"

#define ledPin 11

DFRobot_VL53L0X sensor;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
   //initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //join i2c bus (address optional for master)
  Wire.begin();
  //Set I2C sub-device address
  sensor.begin(0x50);
  //Set to Back-to-back mode and high precision mode
  sensor.setMode(sensor.eContinuous,sensor.eHigh);
  //Laser rangefinder begins to work
  sensor.start();
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  //pixels.fill((0,0,0),10);
  
  //delay(DELAYVAL);

  int ledValue = map(sensor.getDistance(), 0, 2000, 0,255);
  Serial.print("Distance: ");Serial.println(sensor.getDistance());

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one.
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    if (i % 4 == 0){
      pixels.setPixelColor(i, pixels.Color(ledValue, 0, 0));
    }

    if (i % 4 == 1){
      pixels.setPixelColor(i, pixels.Color(0, ledValue, 0));
    }

    if (i % 4 == 2){
      pixels.setPixelColor(i, pixels.Color(0, 0, ledValue));
    }

    if (i % 4 == 3){
      pixels.setPixelColor(i, pixels.Color(ledValue, ledValue, 0));
    }

    pixels.show();   // Send the updated pixel colors to the hardware.
    

     // Pause before next pass through loop
  }
  delay(DELAYVAL);
}
