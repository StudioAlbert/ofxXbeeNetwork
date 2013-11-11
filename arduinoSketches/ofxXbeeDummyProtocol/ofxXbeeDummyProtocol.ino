
#include "ofxXbeeDummyProtocolDefine.h"
#include "FastSPI_LED2.h"

#define NUM_LEDS 32

const int   ctrlPin = 13; // the pin that the LED is attached to
const CRGB  white = CRGB(255,255,255);

CRGB leds_2[NUM_LEDS];
CRGB leds_3[NUM_LEDS];
CRGB leds_4[NUM_LEDS];
CRGB leds_5[NUM_LEDS];
CRGB leds_6[NUM_LEDS];
CRGB leds_7[NUM_LEDS];
CRGB leds_8[NUM_LEDS];
CRGB leds_9[NUM_LEDS];
CRGB leds_10[NUM_LEDS];
CRGB leds_11[NUM_LEDS];

#define nbLoopsForHeartBeat 5000
double nbLoops;

String  sXbeeID;
boolean bSetupLeds;

void setup() {
  nbLoops = 0;
  // initialize serial communication:
  Serial.begin(9600);
  Serial.println();
  Serial.println("-------------------");
  Serial.println("Init");
  
  sXbeeID = XBEEID_NONE;
  // initialize the LED pin as an output:
  pinMode(ctrlPin, OUTPUT);
  // Initialize LEDS
  bSetupLeds = false;
  setupLEDS();
}

void setupLEDS() {
  Serial.println("---------------- Setup Leds -----------------");
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
  delay(2000);

  // For safety (to prevent too high of a power draw), the test case defaults to
  // setting brightness to 25% brightness
  LEDS.addLeds<WS2811, 2>(leds_2, NUM_LEDS);
  LEDS.addLeds<WS2811, 3>(leds_3, NUM_LEDS);
  LEDS.addLeds<WS2811, 4>(leds_4, NUM_LEDS);
  /*
  LEDS.addLeds<WS2811, 5>(leds_5, NUM_LEDS);
  LEDS.addLeds<WS2811, 6>(leds_6, NUM_LEDS);
  LEDS.addLeds<WS2811, 7>(leds_7, NUM_LEDS);
  LEDS.addLeds<WS2811, 8>(leds_8, NUM_LEDS);
  LEDS.addLeds<WS2811, 9>(leds_9, NUM_LEDS);
  LEDS.addLeds<WS2811, 10>(leds_10, NUM_LEDS);
  */
  LEDS.addLeds<WS2811, 11>(leds_11, NUM_LEDS);

  
  allLEDS(getArray(2), 0);
  allLEDS(getArray(3), 0);
  allLEDS(getArray(4), 0);
  allLEDS(getArray(5), 0);
  allLEDS(getArray(6), 0);
  allLEDS(getArray(7), 0);
  allLEDS(getArray(8), 0);
  allLEDS(getArray(9), 0);
  allLEDS(getArray(10), 0);
  allLEDS(getArray(11), 0);
  
  LEDS.setBrightness(255);    
  LEDS.show();
}

void loop() {

  String  receivedMsg;

  nbLoops++;
  if(nbLoops>nbLoopsForHeartBeat){

    nbLoops = 0;
    String trimmedID = sXbeeID;
    trimmedID.trim();
    
    if(trimmedID=="" || sXbeeID==XBEEID_NONE){
      sXbeeID = getXbeeId();
      digitalWrite(ctrlPin, HIGH);
      Serial.println(HEAD + sXbeeID + ID_ASKING + TAIL);
    }else{
      digitalWrite(ctrlPin, LOW);
      Serial.println(HEAD + sXbeeID +  HEARTBEAT + TAIL);
    }
  }
  
  int nbCar = Serial.available();
  if (nbCar>0){

    bool idControl = false;
    String sIDReceived;
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
      sIDReceived = receivedMsg.substring(3,7);
      if(sIDReceived == sXbeeID){
        idControl = true;
      }
      
      // On cherche le big Mode
      bigMode   = receivedMsg.substring(7,10);
      fineMode  = receivedMsg.substring(10,13);
      pinNum    = receivedMsg.substring(13,16).toInt();
      arg1      = receivedMsg.substring(16,19).toInt();
      arg2      = receivedMsg.substring(19,22).toInt();
      
    }

    if(idControl==true){
      digitalWrite(ctrlPin, LOW);

      // GOOD DATAS ----------------
      receivedMsg = "";

      if(bigMode==BigMode_Out){
        // We're driving outputs
        if(fineMode==FineMode_All){
          // The whole strip
          // all leds on among value received
          allLEDS(getArray(pinNum), arg1);
        }
        else if(fineMode==FineMode_Drop){
          // Drop mode
          // drop the LEDS
          drop(getArray(pinNum), arg1);
        }else{
          
          digitalWrite(ctrlPin, HIGH);
        }
      }
      LEDS.show();
    }
    else{
      digitalWrite(ctrlPin, HIGH);
    }
  }
}  


// XBEE ID Sequence -----------------
String getXbeeId(){
  
  int nbCar;
  String answers = "";
  String xShortBeeId = XBEEID_NONE;
  
  Serial.println();
  Serial.println("-- Xbee ID asking ----------------");
  delay(3500);
  // Print the message to give an order to Xbee
  Serial.print("+++");
  delay(1200);
  while (Serial.available() > 0) {
    answers += Serial.readString();
  }
  
  Serial.println("AT");
  delay(200);
  while (Serial.available() > 0) {
      answers += Serial.readString();
  }
  
  Serial.println("ATID");
  delay(200);
  answers += "ID network : ";
  while (Serial.available() > 0) {
      answers += Serial.readString();
  }
  
  Serial.println("ATSL");
  delay(200);
  if(Serial.available() > 0){
    xShortBeeId = "";
    while (Serial.available() > 0) {
        xShortBeeId += Serial.readString();
    }
    xShortBeeId = xShortBeeId.substring(4,8);
  }
  
  Serial.println("ATCN");
  delay(200);
  while (Serial.available() > 0) {
      answers += Serial.readString();
  }

  Serial.println("xBee ID : ");
  Serial.println(xShortBeeId);
  Serial.println("-- Xbee ID asking : END ----------------");
  
  return xShortBeeId;
  
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
  case 7:
    return leds_7;
    break;
  case 8:
    return leds_8;
    break;
  case 9:
    return leds_9;
    break;
  case 10:
    return leds_10;
    break;
  case 11:
    return leds_11;
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

