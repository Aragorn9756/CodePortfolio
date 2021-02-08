//Created by Scott Schmader and Corbett Larsen
//Modified by Stephen Richardson

void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
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

//Startup sequence
