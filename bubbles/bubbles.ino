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
  int cR = 0;
  public:
  Effect(int dir){
    movDir = dir;
  }
  void Update()
  {
    if(slow == 10){
      for(int i = 0; i < 14; i++){
           leds[i+fall] = CRGB(cR, i*3, 0);
           leds[NUM_LEDS-fall-i] = CRGB(16, 16, 16);
      }
      fall += 14;
      
      if(fall >= NUM_LEDS-10){
        fall = NUM_LEDS/2;
      }
    }
    for(int i = 0; i < NUM_LEDS-2; i++){
      leds[i] += CRGB(0, 0, slow/5);
    }
    slow++;
    if(slow > 10){slow = 0;}
    cR = random(64);
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
