//
//  ofxXbeeNodePin.cpp
//  ofxXbeeNetwork
//
//  Created by Dudley Smith on 21/10/13.
//
//

#include "ofxXbeeNodePin.h"

ofxXbeeNodePin::ofxXbeeNodePin(){
    
}

ofxXbeeNodePin::ofxXbeeNodePin(ofxXbeeNodePin const &_pin){
    m_aValues = _pin.m_aValues;
    m_eMode   = _pin.m_eMode;
}

bool operator== (ofxXbeeNodePin &_pin1, ofxXbeeNodePin &_pin2){
    
    if(_pin1.m_eMode!=_pin2.m_eMode){
        // if mode is different
        return false;
    }else if(_pin1.m_aValues.size()!=_pin2.m_aValues.size()){
        // If values are not in same quantity
        return false;
    }else{
        // Comparison of each value : first difference give objects different
        for (int idxValue=0; idxValue<_pin1.m_aValues.size(); idxValue++) {
            if(_pin1.m_aValues[idxValue] != _pin2.m_aValues[idxValue]){
                return false;
            }
        }
    }
    
    // Nothing is different
    return true;
    
}

bool ofxXbeeNodePin::changePin(pinMode _newMode, vector<float>   _newValues){
    
    ofxXbeeNodePin newPin;
    newPin.registerPin(_newMode, _newValues);
    
    bool changeResult = !(*this==newPin);
    
    registerPin(_newMode, _newValues);
    
    return changeResult;
    
}

void ofxXbeeNodePin::registerPin(pinMode _mode, vector<float>   _values){
    m_eMode = _mode;
    m_aValues = _values;
}

void ofxXbeeNodePin::registerPin(pinMode _mode){
    m_eMode = _mode;
}

float ofxXbeeNodePin::getAValue(int _orderValue){
    
    if(_orderValue>=0 && _orderValue<m_aValues.size()){
        return m_aValues[_orderValue];
    }else{
        return 0;
    }
    
}