#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    256
CRGB leds[NUM_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  240

void setup() {
  delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}

class Effect
{
  int movDir;
  int fall = NUM_LEDS/2;
  int slow = 0;
  public:
  Effect(int dir){
    movDir = dir;
  }
  void Update()
  {
    if(slow == 35){
      for(int i = 0; i <= 12; i++){
           leds[i+fall] = CRGB( 64, 64, 0);
           leds[NUM_LEDS-fall-i] = CRGB( 64, 64, 0); 
      }
      fall += 12;
      
      if(fall >= NUM_LEDS-10){
        fall = NUM_LEDS/2;
      }
    }
    slow++;
    if(slow > 35){slow = 0;}

    fadeToBlackBy( leds, NUM_LEDS, 10);  
  }
};

Effect* effect[] = {
  new Effect(0)
  

    
  
};

void loop(){
  // send the 'leds' array out to the actual LED strip
  FastLED.show(); 

for(int i = 0; i < sizeof(effect)/sizeof(effect[0]); ++i){
  effect[i]->Update();
}

delay(25);

}
