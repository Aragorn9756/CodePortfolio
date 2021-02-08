//Created by Scott Schmader and Corbett Larsen
//Modified by Stephen Richardson

#include <FastLED.h>

//Initiate LED strip
#define pix 157
CRGB strip[pix];

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  FastLED.addLeds<NEOPIXEL, 6>(strip, pix);
  FastLED.setBrightness(100);
  FastLED.setDither(0);
  resetPixels();
}

//State of input pins
boolean state7 = false;
//Power button timer
int holdPower = 0;
int holdRed = 0;

void loop() {
//Check for Pi serial input
  char numin = Serial.read();
  
//Turn on "Ready" light
  if(numin == '2') {
    resetPixels();
    strip[3] = CRGB::Yellow;
    FastLED.show();
  }
  
//Play startup sequence
  if(numin == '6') {
    startup();
  }
  
//Play shutdown sequence
  if(numin == '8') {
    daisy();
  }
  
//Prepare for true shutdown
  if(numin == '7') {
    resetPixels();
  }
  
//Easter Egg
  if(numin == '5') {
    rainbow();
  }
  
//Red Button
  while(digitalRead(7) == HIGH) {
    holdRed = holdRed + 1;
    delay(50);
    if(holdRed >= 40) {
      Serial.println(2);
      break;
    }
  }
  if((holdRed > 0) && (holdRed < 40)) {
    Serial.println(1);
  }
  
//OLD RED BUTTON SCRIPT
//  if(digitalRead(7) == HIGH) {
//    if(state7 == false){
//      Serial.println(1);
//      state7 = true;
//      }
//    } else {
//      state7 = false;
//      }
  
//Power Button
  while(digitalRead(4) == HIGH) {
    holdPower = holdPower + 1;
    delay(50);
    if(holdPower >= 40) {
      Serial.println(4);
      break;
    }
  }
  if((holdPower > 0) && (holdPower < 40)) {
    Serial.println(3);
  }
  
// Reset Variables
  holdPower = 0;
  holdRed = 0;
//Speed of Loop
  delay(80);
}


//FUNCTIONS

//Sets all pixels to 0, 0, 0
void resetPixels() {
  for(int i = 0; i < pix; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
}

//Sets all pixels to one color H, S, V
void setAll(int h, int s, int v) {
  for(int i = 0; i < pix; i++) {
    strip[i] = CHSV(h, s, v);
  }
  FastLED.show();
}

//Startup sequence
void startup() {
  int timing = 1110;
  resetPixels();
  for(int i = 137; i < 157; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 117; i < 137; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 98; i < 117; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 79; i < 98; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 61; i < 79; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 45; i < 61; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 30; i < 45; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 17; i < 30; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 7; i < 17; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 0; i < 7; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  resetPixels();
  delay(4700);
  setAll(0, 0, 255);
  delay(1500);
  for(int b = 255; b >= 0; b = b-5) {
    setAll(0, 0, b);
    delay(7);
  }
  resetPixels();
  strip[3] = CRGB::Green;
    FastLED.show();
}

//Shutdown Sequence
void daisy() {
  int timing = 850;
  resetPixels();
  for(int i = 0; i < 157; i++) {
    strip[i] = CRGB::Red;
  }
  FastLED.show();
  delay(timing);
  for(int i = 0; i < 7; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 7; i < 17; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 17; i < 30; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 30; i < 45; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 45; i < 61; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 61; i < 79; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 79; i < 98; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 98; i < 117; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  for(int i = 117; i < 137; i++) {
    strip[i] = CRGB::Black;
  }
  FastLED.show();
  delay(timing);
  resetPixels();
  delay(1000);
  strip[3] = CRGB::Yellow;
  FastLED.show();
}

//Easter Egg Rainbow
//AKA Super Crappy Code
void rainbow() {
  int timing = 30;
  //Going Up
  for(int i = 0; i < 20; i++) {
    strip[i+137] = CHSV((19-i)*12.75, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 20; i++) {
    strip[i+117] = CHSV(i*12.75, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 19; i++) {
    strip[i+98] = CHSV((18-i)*13.42, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 19; i++) {
    strip[i+79] = CHSV(i*13.42, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 18; i++) {
    strip[i+61] = CHSV((17-i)*14.17, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 16; i++) {
    strip[i+45] = CHSV(i*15.94, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 15; i++) {
    strip[i+30] = CHSV((14-i)*17, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 13; i++) {
    strip[i+17] = CHSV(i*19.62, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 10; i++) {
    strip[i+7] = CHSV((9-i)*25.5, 255, 255);
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 7; i++) {
    strip[i] = CHSV(i*36.43, 255, 255);
    FastLED.show();
    delay(timing);
  }
  //Coming Down
  for(int i = 0; i < 20; i++) {
    strip[i+137] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 20; i++) {
    strip[i+117] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 19; i++) {
    strip[i+98] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 19; i++) {
    strip[i+79] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 18; i++) {
    strip[i+61] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 16; i++) {
    strip[i+45] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 15; i++) {
    strip[i+30] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 13; i++) {
    strip[i+17] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 10; i++) {
    strip[i+7] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  for(int i = 0; i < 7; i++) {
    strip[i] = CRGB::Black;
    FastLED.show();
    delay(timing);
  }
  resetPixels();
}
