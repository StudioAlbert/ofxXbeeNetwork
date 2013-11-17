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
    pinMode         m_eMode;
public:
    pinMode         getMode();
    
private:
    float           m_fValue;
public:
    float   getValue();
    
public:
    bool change(pinMode _newMode, float _newValue);
    void set(pinMode _mode, float _value);
    void setup(pinMode _newMode);
    
};
