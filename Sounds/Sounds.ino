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

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to
int outputValue = 0;        // value output to the PWM (analog out)
int sensorValue = 0;        // value read from the pot

void setup() {
    Serial.begin(9600);
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
  int fall = 0;
  int slow = 0;
  int cR = 0;
  public:
  Effect(int dir){
    movDir = dir;
  }
  void Update()
  {
    if(slow == 1){
        for(int i = 0; i < NUM_LEDS; i++){
          leds[i] += CRGB(sensorValue,sensorValue,0);
        }
      }
    slow++;
    if(slow > 1){slow = 0;}

      sensorValue = analogRead(analogInPin);
      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, outputValue);
        Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
  fall += sensorValue/5;
  if(fall >= NUM_LEDS){
    fall = 0;
  }
  leds[fall] += CRGB(128,128,128);
  fadeToBlackBy( leds, NUM_LEDS, 30);  
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
