//
//  ofxXbeeNode.h
//  saman
//
//  Created by Dudley Smith on 15/10/13.
//
//

#pragma once

#define PIN_MIN 2
#define PIN_MAX 13

#define START_VALUE 0.5f

#define EMPTY_MSGS  "empty"

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxXbeeDummyProtocol.h"
#include "ofxXbeeNodePin.h"

class ofxXbeeNode {
    
private:
    // Parameter ID for the Xbee card ----------------
private:
    string      m_sID;
public:
    string      getID(){return m_sID;};
    
    // Array of messages to send ----------------
private:
    queue<string>      m_aMessages;
    void               pushMessage(string _message);
public:
    string             popNextMessage();
    
    // Drive a node is only about adding and adding message --
public:
    void    setAllStrip(int _pin, float _value);
    void    setDropPosition(int _pin, float _position);
    
public:
    void setup(string _id);
    
    // Array of outputs
protected:
    map<int, ofxXbeeNodePin> m_aPins;
public:
    void registerPin(int _pinNum, pinMode _pinMode);
    
};