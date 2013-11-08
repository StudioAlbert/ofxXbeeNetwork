
#include "ofxXbeeDummyProtocolDefine.h"
#include "FastSPI_LED2.h"

#define NUM_LEDS 32
#define PIN_MIN  2
#define PIN_MAX  6

const int   ctrlPin = 13; // the pin that the LED is attached to
const CRGB  white = CRGB(255,255,255);

CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];
CRGB leds_5[NUM_LEDS];
CRGB leds_6[NUM_LEDS];

#define nbLoopsForHeartBeat 5000
double nbLoops;

void setup() {
  nbLoops = 0;
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ctrlPin, OUTPUT);
  // Initialize LEDS
  setupLEDS();
}

void setupLEDS() {

  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  // For safety (to prevent too high of a power draw), the test case defaults to
  // setting brightness to 25% brightness

  LEDS.setBrightness(64);
  LEDS.addLeds<WS2811, 2>(leds_2, NUM_LEDS);
  LEDS.addLeds<WS2811, 3>(leds_3, NUM_LEDS);
  LEDS.addLeds<WS2811, 4>(leds_4, NUM_LEDS);
  LEDS.addLeds<WS2811, 5>(leds_5, NUM_LEDS);
  LEDS.addLeds<WS2811, 6>(leds_6, NUM_LEDS);

}

void loop() {

  String  sIdCard = "001";
  int     iIdCard = 1;
  
  String  receivedMsg;
  
  nbLoops++;
  if(nbLoops>nbLoopsForHeartBeat){
    nbLoops = 0;
    Serial.print(HEAD + sIdCard + HEARTBEAT + TAIL);
  }
  
  int nbCar = Serial.available();

  if (nbCar>0){

    bool idControl = false;
    int  idReceived;
    String bigMode = "";
    String fineMode = "";
    int    pinNum = 0;
    int    arg1 = 0;
    int    arg2 = 0;

    // Control of good datas received
    receivedMsg = Serial.readStringUntil(']');

    // On controle l'entete
    if(receivedMsg[0]== '[' && receivedMsg[1]== '[' && receivedMsg[2]== '['){
      // On controle l'ID
      idReceived = receivedMsg.substring(3,6).toInt();
      if(idReceived==iIdCard){
        idControl = true;
      }
      // On cherche le big Mode
      bigMode   = receivedMsg.substring(6,9);
      fineMode  = receivedMsg.substring(9,12);
      pinNum    = receivedMsg.substring(12,15).toInt();
      arg1      = receivedMsg.substring(15,18).toInt();
      arg2      = receivedMsg.substring(18,21).toInt();
    }

    if(idControl==true){
      // GOOD DATAS ----------------
      receivedMsg = "";


      if(bigMode==BigMode_Out){
        // We're driving outputs
        if(fineMode==FineMode_All){
          // The whole strip
          // all leds on among value received
          allLEDS(getArray(pinNum), arg1);
          // and now, show your led array! 
          //LEDS.setBrightness(arg1);
        }
        else if(fineMode==FineMode_Drop){
          // Drop mode
          // drop the LEDS
          drop(getArray(pinNum), arg1);
        }
        else{
          blinkDebugOK(10);
        }
      }

      LEDS.show();

    }
    else{
      blinkError(16);
    }

  }
}  

// Blink functions ------------------
void blinkError(int nbBlinks){

  for(int i=0; i<nbBlinks; i++){
    digitalWrite(ctrlPin, HIGH);
    delay(5);
    digitalWrite(ctrlPin, LOW);  
    delay(45);  
  }
}

void blinkDebugOK(int nbBlinks){
  for(int i=0; i<2; i++){
    digitalWrite(ctrlPin, HIGH);
    delay(90);
    digitalWrite(ctrlPin, LOW);  
    delay(10);  
  }
}

// LEDS Section -----------------------------------
CRGB* getArray(int _pinNum){

  switch(_pinNum){
  case 2:
    return leds_2;
    break;
  case 3:
    return leds_3;
    break;
  case 4:
    return leds_4;
    break;
  case 5:
    return leds_5;
    break;
  case 6:
    return leds_6;
    break;
  default:
    return leds_2;
  }

}

void drop(CRGB _leds[NUM_LEDS], int _position){

  int realPosition = ((float)_position/255.0f)*NUM_LEDS;

  memset(_leds, 0,  NUM_LEDS * sizeof(struct CRGB));
  _leds[realPosition] = white;

}

void allLEDS(CRGB _leds[NUM_LEDS], float _value){
  memset(_leds, _value,  NUM_LEDS * sizeof(struct CRGB));
}

