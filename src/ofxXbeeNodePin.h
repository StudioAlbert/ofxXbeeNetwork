//
//  ofxXbeeNodePin.h
//  ofxXbeeNetwork
//
//  Created by Dudley Smith on 21/10/13.
//
//

#pragma once

#include "ofMain.h"

enum pinMode{
    pinModeIn       = 1
    ,pinModePwm     = 2
    ,pinModeDrop    = 3
};

class ofxXbeeNodePin {
public:
    ofxXbeeNodePin();
    ofxXbeeNodePin(ofxXbeeNodePin const &_pin);
private:
    friend bool operator== (ofxXbeeNodePin &_pin1, ofxXbeeNodePin &_pin2);
    
private:
    pinMode         m_eMode;
public:
    pinMode         getMode(){return m_eMode;};
    
private:
    vector<float>   m_aValues;
public:
    float   getAValue(int _orderValue);
    
public:
    bool changePin(pinMode _newMode, vector<float>   m_aValues);
    void registerPin(pinMode _newMode, vector<float>   m_aValues);
    void registerPin(pinMode _newMode);
    
    
};
