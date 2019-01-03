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


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
//SimplePatternList gPatterns = {cuylerLights}; // rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm , confetti

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


class SnowFlake
{
  int movDir;
  int movPos;
  uint8_t movSpeed;
  uint8_t cR;
  uint8_t cG;
  uint8_t cB;
  uint8_t fadeTime;
  uint8_t rot;

  public:
  SnowFlake(int dir, int pos, uint8_t spe, uint8_t fade, uint8_t R, uint8_t G, uint8_t B){
    movSpeed = spe;
    fadeTime = fade;
    movDir = dir;
    movPos = pos;
    cR = R;
    cG = G;
    cB = B;
  }
  void Update()
  {
    rot++;
    leds[movPos] += CRGB(cR, cG, cB);
    
    if(rot%movSpeed == 0){
        movPos += movDir;
    }
    
    if(movPos >= NUM_LEDS){
      movPos = random(10)- 5 + NUM_LEDS/2;
      movSpeed = 3 + random(30);
      cR = 10 + random(10);
      cG = 10 + random(10);
      cB = 16 + random(16);
    }else if(movPos < 0){
      movPos = random(10)- 5 + NUM_LEDS/2;
      movSpeed = 3 + random(30);
      cR = 10 + random(10);
      cG = 10 + random(10);
      cB = 16 + random(16);
    }  
    

    fadeToBlackBy( leds, NUM_LEDS, fadeTime);  
  }
};

SnowFlake* snowFlake[] = {
  new SnowFlake(-1, random(128), random(10)+10,1,16,16,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,3,4,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,2,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,1,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,4,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,4,16),  
  new SnowFlake(-1, random(128), random(10)+10,1,16,16,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,3,4,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,2,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,1,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,4,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,4,16),
  new SnowFlake(-1, random(128), random(10)+10,1,16,16,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,3,4,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,2,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,1,16), 
  new SnowFlake(-1,random(128),random(10)+10,1,4,3,16), 
  new SnowFlake(1,random(128)+128,random(10)+10,1,4,4,16)
  
};

void loop(){
  // send the 'leds' array out to the actual LED strip
  FastLED.show(); 

for(int i = 0; i < sizeof(snowFlake)/sizeof(snowFlake[0]); ++i){
  snowFlake[i]->Update();
}
delay(25);

}
