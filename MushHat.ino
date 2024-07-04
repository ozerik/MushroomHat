/* -------- JUANITO'S MUSHROOM HAT BLINKY LIGHTS!!!!!! -----------
    Here's code for an Arduino-powered audio-reactive blinky light thing that
    uses a lot of analog audio electronics to feed voltages into an Arduino
    that controls a string of addressable WS2812 LEDs. You can alter this code
    to allow you to use faster addressable LEDs (APA102, for instance) or a
    longer or shorter string of LEDs... but it's up to you to figure out the
    things you need to modify.

    The schematic for this is over on Github.
    https://github.com/ozerik/MushroomHat/
    I'm using a couple modules that aren't on the schematic. Details
    on the Github readme
    -- battery power, charging, protection
    -- bipolar power for the audio electronics
    -- microphone driver
    -- Very Bright LED driver (1W? 5W?)
*/
#include <FastLED.h>

#define NUM_LEDS 144
#define DATA_PIN 2

CRGB leds[NUM_LEDS];
CRGB tLeds1[16];  
CRGB tLeds2[16];  
CRGB tLeds3[16];  
CRGB mLeds1[16];  
CRGB mLeds2[16];  
CRGB mLeds3[16];  
CRGB bLeds1[16];  
CRGB bLeds2[16];  
CRGB bLeds3[16];  

uint16_t bass;
uint16_t mid;
uint16_t treb;
uint8_t gain;

long timer;
long flash;

uint8_t hue1;
uint8_t hue2 = 55;
uint8_t hue3 = 111;
uint8_t hue4 = 140;
uint8_t hue5 = 200;
uint8_t hue6 = 225;

uint8_t flashEnable = 1;



void setup() {
  // Serial.begin(57600);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);


  pinMode(A0, INPUT);  // bass input
  pinMode(A1, INPUT);  // midrange input
  pinMode(A2, INPUT);  // treble input
  pinMode(5, OUTPUT);  // PWM out for mic gain
  pinMode(7, OUTPUT);  // flasher for white LEDs
}

void loop() {
  bass = (analogRead(A0));
  mid = (analogRead(A1));
  treb = (analogRead(A2));
  if (bass > 1022) {
    gain++;
    if (flashEnable == 1) {
      bitWrite(PORTD, 7, 1);
      flash = millis();
    flashEnable = 0;
    }
  }
  if (mid > 1022) {
    gain++;
    if (flashEnable == 1) {
      bitWrite(PORTD, 7, 1);
      flash = millis();
    flashEnable = 0;
    }
  }
  if (treb > 1022) {
    gain++;
    if (flashEnable == 1) {
      bitWrite(PORTD, 7, 1);
      flash = millis();
    flashEnable = 0;
    }
  }
  if (gain > 254) gain = 254;
  analogWrite(5, gain);
  if (millis() > timer + 50 && gain > 1) {
    gain--;
    timer = millis();
    hue1++;
    hue2++;
    hue3++;
    hue4++;
    hue5++;
    hue6++;
  }
  if (millis() > flash + 20) {
    bitWrite(PORTD, 7, 0);
  }
  if (millis() > flash + 175 && flashEnable == 0) {
    flashEnable = 1;
    flash = millis();
  }


  fill_solid(tLeds1, 16, 0);
  fill_solid(tLeds2, 16, 0);
  fill_solid(tLeds3, 16, 0);
  fill_solid(mLeds1, 16, 0);
  fill_solid(mLeds2, 16, 0);
  fill_solid(mLeds3, 16, 0);
  fill_solid(bLeds1, 16, 0);
  fill_solid(bLeds2, 16, 0);
  fill_solid(bLeds3, 16, 0);
  fill_solid(tLeds1, map(treb, 0, 1023, 0, 16), CHSV(hue1 + (mid >> 2), map(treb, 0, 1023, 100, 255), map(treb, 0, 1023, 0, 255)));
  fill_solid(tLeds2, map(treb, 0, 1023, 0, 16), CHSV(hue2 + (bass >> 2), map(mid, 0, 1023, 100, 255), map(treb, 0, 1023, 0, 255)));
  fill_solid(tLeds3, map(treb, 0, 1023, 0, 16), CHSV(hue3 + (treb >> 2), map(bass, 0, 1023, 255, 50), map(treb, 0, 1023, 0, 255)));
  fill_solid(mLeds1, map(mid, 0, 1023, 0, 16),  CHSV(hue2 + mid, map(treb, 0, 1023, 100, 255), map(mid, 0, 1023, 0, 255)));
  fill_solid(mLeds2, map(mid, 0, 1023, 0, 16),  CHSV(hue3 + (bass >> 2), map(mid, 0, 1023, 100, 255), map(mid, 0, 1023, 0, 255)));
  fill_solid(mLeds3, map(mid, 0, 1023, 0, 16),  CHSV(hue4 + (mid >> 2), map(treb, 0, 1023, 255, 50), map(mid, 0, 1023, 0, 255)));
  fill_solid(bLeds1, map(bass, 0, 1023, 0, 16), CHSV(hue5 + (treb >> 2), map(mid, 0, 1023, 100, 255), map(bass, 0, 1023, 0, 255)));
  fill_solid(bLeds2, map(bass, 0, 1023, 0, 16), CHSV(hue6 + mid, map(treb, 0, 1023, 100, 255), map(bass, 0, 1023, 0, 255)));
  fill_solid(bLeds3, map(bass, 0, 1023, 0, 16), CHSV(hue1 + (mid >> 2), map(treb, 0, 1023, 50, 255), map(bass, 0, 1023, 0, 255)));


  for (int i = 0; i < 16; i++) {
    leds[i] = tLeds1[i];
    leds[i + 16] = tLeds2[i];
    leds[i + 32] = tLeds3[i];
    leds[i + 48] = mLeds1[i];
    leds[i + 64] = mLeds2[i];
    leds[i + 80] = mLeds3[i];
    leds[i + 96] = bLeds1[i];
    leds[i + 112] = bLeds2[i];
    leds[i + 128] = bLeds3[i];
  }



  Serial.println(flash);

  FastLED.show();
}
