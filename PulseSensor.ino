#include <FastLED.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     5
#define NUM_LEDS    240

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int pulsePin = 0;
int heartPin = 13;    //pin to blink LED at each beat for testing

volatile int BPM;
volatile int Signal;
volatile int IBI = 600;
volatile boolean Pulse = false; //True when heartbeat is detected
volatile boolean QS = false;    //becomes true when arduino finds a beat

int BAM = ((BPM/60));

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(80);

  pinMode(heartPin, OUTPUT);
  interruptSetup();
}

void loop() {
    
    if (QS == true) {  
      if ((BPM < 140) && (BPM > 40)) {
        if ((IBI > 200) && (IBI < 1000)){
          red();
          strip.setBrightness(0);
          strip.show();
          delay(IBI);
          strip.setBrightness(80);
          strip.show();
          
  }
      }
        } else {
    rainbow(0);
        }
}


void red() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  strip.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
