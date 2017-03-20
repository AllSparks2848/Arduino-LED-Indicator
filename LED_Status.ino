
#include <FastLED.h>

// Setup LED strip
#define COLOR_ORDER       RGB
#define MAX_BRIGHTNESS    255
#define NUM_LEDS          15

// This is an array of leds. One item for each led in your strip
CRGB leds[NUM_LEDS];

#define DATA_PIN          13 //White wire from the http://www.andymark.com/product-p/am-2917.htm power connector

//DIO pins from RoboRio
//loc = Arduino pin location
//val = value of the bit when read

int locBit0 = 2;
int locBit1 = 3;
int valBit0 = 0;
int valBit1 = 0;

// Status value meaning
// 00 = default (Blue Cylon pattern)
// 10 = Gear in intale (All Red)

void setup()
{


   FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

   //clear() turns all LEDs off
   FastLED.clear();
   FastLED.setBrightness(MAX_BRIGHTNESS);
   fill_solid( leds, NUM_LEDS /*number of leds*/, CRGB( 125, 125, 125) );
   FastLED.show();

   pinMode(locBit0, INPUT);
   pinMode(locBit1, INPUT); 

   cylon(CRGB::Blue, 60, 1);
}

void loop()
{

    valBit0 = digitalRead(locBit0);
    valBit1 = digitalRead(locBit1);

    if ((valBit0==HIGH)){
      red();
    }else
    {
      green();
//       cylon(CRGB::Blue, 60, 1);
    }
    if(valBit1==HIGH)
    {
      off();
    } else
    {
      white();
    }
    
}

//Set strip red for gear intake
void red()
{
   //Step thru some brightness levels from max to 10. led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
       for (int i = 0; i<=5; i++) {
    leds[i] = CRGB::Green;  //Green = Red, still troubeshooting lol
      }
      for (int i = 9; i<=14; i++) {
    leds[i] = CRGB::Green;  //Green = Red, still troubeshooting lol
      }
    FastLED.show();
    delay(50);
}

void white()
{
  //Step thru some brightness levels from max to 10. led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
       for (int i = 6; i<=8; i++) {
    leds[i] = CRGB::White;  //Green = Red, still troubeshooting lol
      }
    FastLED.show();
    delay(50);
}

void off()
{
  //Step thru some brightness levels from max to 10. led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
       for (int i = 6; i<=8; i++) {
    leds[i] = CRGB::Black;  //Green = Red, still troubeshooting lol
      }
    FastLED.show();
    delay(50);
}

void green()
{
   //Step thru some brightness levels from max to 10. led_brightness/=2 is a cryptic shorthand way of saying led_brightness = led_brightness/2
       for (int i = 0; i<NUM_LEDS; i++) {
    for (int i = 0; i<=5; i++) {
    leds[i] = CRGB::Red;  //Green = Red, still troubeshooting lol
      }
      for (int i = 9; i<=14; i++) {
    leds[i] = CRGB::Red;  //Green = Red, still troubeshooting lol
      }
    FastLED.show();
    delay(50);
}

//Cylon - LED sweeps back and forth, with the color, delay and number of cycles of your choice
void cylon(CRGB color, uint16_t wait, uint8_t number_of_cycles)
{
   FastLED.setBrightness(MAX_BRIGHTNESS);
   for (uint8_t times = 0; times<=number_of_cycles; times++)
   {
      // Make it look like one LED is moving in one direction
      for(int led_number = 0; led_number < NUM_LEDS; led_number++)
      {
         //Apply the color that was passed into the function
         leds[led_number] = color;
         //Actually turn on the LED we just set
         FastLED.show();
         // Turn it back off
         leds[led_number] = CRGB::Black;
         // Pause before "going" to next LED
         delay(wait);
      }

      // Now "move" the LED the other direction
      for(int led_number = NUM_LEDS-1; led_number >= 0; led_number--)
      {
         //Apply the color that was passed into the function
         leds[led_number] = color;
         //Actually turn on the LED we just set
         FastLED.show();
         // Turn it back off
         leds[led_number] = CRGB::Black;
         // Pause before "going" to next LED
         delay(wait);
      }
   }
   return;
}



