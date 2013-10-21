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
    out     = 1
    ,in     = 2
    ,pwm    = 3
};

class ofxXbeeNodePin {
    
private:
    pinMode         m_eMode;
    vector<float>   m_aValues;
    
    friend bool operator== (ofxXbeeNodePin &_pin1, ofxXbeeNodePin &_pin2);
    
public:
    bool changePin(pinMode _newMode, vector<float>   m_aValues);
    void registerPin(pinMode _newMode, vector<float>   m_aValues);
    void registerPin(pinMode _newMode);
    
};
