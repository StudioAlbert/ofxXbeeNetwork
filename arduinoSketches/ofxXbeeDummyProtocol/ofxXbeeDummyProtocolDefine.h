//
//  ofxXbeeDummyProtocolDefine.h
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//  Basic Protocol :
//  The principle is simple : We broadcast messages to All Arduino
//  The message is made with 7 groups of 3 digits each (21 characters)
//  Group_A : Head : Always the same [[[
//  Group B : Card number (The arduino has to know his number, if arduino has the same number they have the behavior)
//  Group C : Big Mode
//      _IN -> Mode to receive from arduino inputs (not implemented yet)
//      OUT -> Mode to send to arduino outputs
//  Group D : Fine Mode
//      PWM -> analog outputs
//      DIG -> digital outputs
//      BLK -> Blink the output
//      DRP -> Able to do some drop falling (with digital led strips)
//      RND -> Random blink
//  Group E : Pin number (For drops, it will block 2 pins)
//  Group F : Value
//      With D = Mode PWM (Analog 000 ... 255)
//      With D = Mode DIG (Analog 000 / 255)
//      With D = Mode BLK (Speed of blink : 000 ... 255)
//      With D = Mode DRP (Speed of falling drop  : 000 ... 255)
//      With D = Mode RND (Speed of random blink : 000 ... 255)
//  Group_G : Tail : Always the same ]]]
//
// Example
//  Write a simple PWM on arduino 01 / Pin 13 / 255
//      [[[001OUTPWM013255]]]
//
//  Send a random Blink on arduino 02 / Pin 06 / 120ms of blinking
//      [[[001OUTPWM006120]]]
//
//

#pragma once

#define HEAD "[[["
#define TAIL "]"
#define HEARTBEAT "HeartBeat"
#define ID_ASKING "ID_Asking"

#define BigMode_Out    "OUT"
#define BigMode_In    "_IN"   // Waiting for implementation

#define FineMode_All   "ALL"   // -> analog outputs
#define FineMode_Drop   "DRP"   // -> Able to do some drop falling (with digital led strips)

#define STATUS_Connected "Connected"
#define STATUS_NotConnected "Not Connected"

#define XBEEID_NONE  "NONE"

#define XBEE_StartConfig  "+++"
#define XBEE_AskConfig    "AT"
#define XBEE_AskXbeeId    "ATID"
#define XBEE_EndConfig    "ATCN"



