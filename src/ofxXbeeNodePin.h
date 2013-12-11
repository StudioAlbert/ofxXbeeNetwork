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
    int m_iValue;
public:
    int getValue();
    
public:
    bool change(pinMode _newMode, int _newValue);
    void set(pinMode _mode, int _value);
    void setup(pinMode _newMode);
    
};
