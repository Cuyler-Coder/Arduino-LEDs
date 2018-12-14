#include <FastLED.h>

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS    300
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


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = {cuylerLights}; // rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm , confetti

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


class Runner
{
  int movDir;
  int movPos;
  uint8_t cR;
  uint8_t cG;
  uint8_t cB;
  uint8_t fadeTime;

  public:
  Runner(int dir, int pos, uint8_t fade, uint8_t R, uint8_t G, uint8_t B){
    fadeTime = fade;
    movDir = dir;
    movPos = pos;
    cR = R;
    cG = G;
    cB = B;
  }
  void Update()
  {
    leds[movPos] += CRGB(cR, cG, cB);
    movPos += movDir;
    
    if(movPos >= NUM_LEDS){
      movPos = 0;
    }else if(movPos < 0){
      movPos = NUM_LEDS;
    }  
    

    fadeToBlackBy( leds, NUM_LEDS, fadeTime);  
  }
};

Runner* runners[] = {
  new Runner(1,0,1,64,64,64), 
  new Runner(-1,15,1,64,0,64), 
  new Runner(1,30,1,0,64,64), 
  new Runner(-1,45,1,64,64,0), 
  new Runner(1,60,1,64,0,0), 
  new Runner(-1,75,1,0,0,64) 
  
};

void loop(){
  // send the 'leds' array out to the actual LED strip
  FastLED.show(); 

for(int i = 0; i < sizeof(runners)/sizeof(runners[0]); ++i){
  runners[i]->Update();
}
delay(25);

}
