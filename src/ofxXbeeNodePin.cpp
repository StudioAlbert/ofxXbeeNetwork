//
//  ofxXbeeNodePin.cpp
//  ofxXbeeNetwork
//
//  Created by Dudley Smith on 21/10/13.
//
//

#include "ofxXbeeNodePin.h"

ofxXbeeNodePin::ofxXbeeNodePin(){
    
    //m_aValues.clear();
}

ofxXbeeNodePin::ofxXbeeNodePin(ofxXbeeNodePin const &_pin){
    m_eMode   = _pin.m_eMode;
    m_fValue  = _pin.m_fValue;
}

bool ofxXbeeNodePin::change(pinMode _newMode, float _newValue){

    if(m_eMode != _newMode){
        // if mode is different
        return true;
    }else if(m_fValue != _newValue){
        ofLogVerbose() << "Compared: " << m_fValue << "!=" << _newValue;
        // If values are not in same quantity
        return true;
    }

    // Nothing is different
    ofLogVerbose() << "Nothing is different";
    return false;
    

}

void ofxXbeeNodePin::set(pinMode _mode, float _value){
    m_eMode     = _mode;
    m_fValue    = _value;
}

void ofxXbeeNodePin::setup(pinMode _mode){
    m_eMode     = _mode;
    m_fValue    = 0;
}


pinMode ofxXbeeNodePin::getMode(){
    return m_eMode;
}

float ofxXbeeNodePin::getValue(){
    return m_fValue;
}
