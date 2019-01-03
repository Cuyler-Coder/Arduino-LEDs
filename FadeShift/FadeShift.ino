#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    269
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
  int movDir2;
  int mod;
  int shift = 0;

  public:
  Effect(int dir){
    movDir = dir;
  }
  void Update()
  {
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i] += CRGB(random(3),random(3),random(3));

    }
    leds[movDir] -= CRGB(10,10,10);
      movDir2 += 1;
    if(movDir2 > 1){
      movDir++;
      movDir2 = 0;
    }
    if(movDir >= NUM_LEDS){movDir = 0;}
    fadeToBlackBy( leds, NUM_LEDS, 1);  
  }
};

Effect* effect[] = {
  new Effect(200)
  

    
  
};

void loop(){
  // send the 'leds' array out to the actual LED strip
  FastLED.show(); 

for(int i = 0; i < sizeof(effect)/sizeof(effect[0]); ++i){
  effect[i]->Update();
}

delay(25);

}
