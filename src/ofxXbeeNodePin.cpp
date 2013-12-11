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
    m_iValue  = _pin.m_iValue;
}

bool ofxXbeeNodePin::change(pinMode _newMode, int _newValue){

    if(m_eMode != _newMode){
        // if mode is different
        return true;
    }else if(m_iValue != _newValue){
        ofLogVerbose() << "Compared: " << m_iValue << "!=" << _newValue;
        // If values are not in same quantity
        return true;
    }

    // Nothing is different
    ofLogVerbose() << "Nothing is different";
    return false;
    

}

void ofxXbeeNodePin::set(pinMode _mode, int _value){
    m_eMode     = _mode;
    m_iValue    = _value;
}

void ofxXbeeNodePin::setup(pinMode _mode){
    m_eMode     = _mode;
    m_iValue    = 0;
}


pinMode ofxXbeeNodePin::getMode(){
    return m_eMode;
}

int ofxXbeeNodePin::getValue(){
    return m_iValue;
}
