#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SINGLE_PIN 15
#define FULL_PIN 1
#define selectorPin 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(53, FULL_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int sparkle1 = 0;
int sparkle2 = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

//  pinMode(selectorPin, INPUT_PULLUP);
//  pinMode(14, OUTPUT);
//  digitalWrite(14, HIGH);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Here I'm assigning the two sparkle locations a random number between zero and the number of pixels minus 1.
  // This is the same numbering system that the pixel array uses, so you will always have two LEDs lit up in white.
  sparkle1 = random(strip.numPixels() - 1);
  sparkle2 = random(strip.numPixels() - 1);
  
  // This is the loop that actually fills the pixel array with the information for what color to light each LED.
    // The first quarter of the strip should be pink, so the first if statement is checking that we are in the first
    // quarter of the strand. It assigns all of those LEDs the same color.
    // The 0.67 multiplier is a gain factor to bring the brightness down by a third to conserve battery. In testing,
    // this turned out to be a great compromise between brigthness and power-saving. Also, running the string at 100%
    // had a tendency to over-current the battery we were using upon start-up. The battery's smarts were tricked into
    // thinking that the huge onrush of current at start-up was a short between power and ground, and the battery
    // would shut down immediatly.
    // The else section is generating the soft gradient from the pink to an off-white color. Again, I've implemented
    // a multiplier of 0.67 for each RGB value for power saving and to prevent battery shutdown.
    // The last if section catches the random numbers generated for sparkle1 and sparkle2 and sets those LEDs to white
    // to create the glittering effect.
  for(int i=0; i< strip.numPixels(); i++) {
    if(i < strip.numPixels() / 4)
      strip.setPixelColor(i, 255*.67, 0*.67, 75*.67);
    else
      strip.setPixelColor(i, 255*.67, .67*((i - strip.numPixels() / 4) * 100 / (0.75 * strip.numPixels())), 75*.67);
    if(i == sparkle1 || i == sparkle2)
      strip.setPixelColor(i, 255, 255, 255);
  }
  strip.show();
  delay(50); // This delay is just to make sure the sparkle flashes are lit up long enough to be seen.
}
