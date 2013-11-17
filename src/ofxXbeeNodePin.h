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
    vector<float>   m_aValues;
public:
    vector<float>   getValues(){return m_aValues;};
    float   getAValue(int _orderValue);
    
public:
    bool changePin(pinMode _newMode, vector<float> _newValues);
    void setPin(pinMode _newMode, vector<float>   m_aValues);
    void registerPin(pinMode _newMode);
    
};
