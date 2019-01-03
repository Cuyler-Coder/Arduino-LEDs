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

  int lead = 0;
  int follow = 0;

  
  public:
  Effect(int dir){
    movDir = dir;
  }
  void Update()
  {
    if(slow == 2){
      lead++;
      if(lead >= NUM_LEDS){lead = 0;}
    }
    follow = random(NUM_LEDS);
    cR = lead/3;
    leds[lead] = CRGB(cR,64,0);
    leds[follow] = leds[lead];
    slow++;
    if(slow > 2){slow = 0;}
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
