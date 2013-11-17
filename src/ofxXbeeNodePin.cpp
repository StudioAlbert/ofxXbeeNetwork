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
    int idxCopy = 0;
    
    for(idxCopy=0; idxCopy<_pin.m_aValues.size(); idxCopy++){
        m_aValues.push_back(_pin.m_aValues[idxCopy]);
    }
    
    m_eMode   = _pin.m_eMode;
    
}

bool ofxXbeeNodePin::changePin(pinMode _newMode, vector<float> _newValues){

    if(m_eMode != _newMode){
        // if mode is different
        return true;
    }else if(m_aValues.empty() != _newValues.empty()){
        // If values are not in same quantity
        return true;
    }else if(m_aValues.size() != _newValues.size()){
        // If values are not in same quantity
        return true;
    }else{
        
        // Comparison of each value : first difference give objects different
        for (int idxValue=0; idxValue<m_aValues.size(); idxValue++) {
            /*
            ofLogVerbose() << values[idxValue];
            
            string msg = "Comparison : ";
            msg.append("Value : ");
            msg.append(ofToString(idxValue));
            msg.append(" 1: ");
            msg.append(ofToString(_newValues[idxValue]));
            msg.append(" 2: ");
            msg.append(ofToString(m_aValues[idxValue]));
            
            ofLogVerbose() << msg;
            */
            if(m_aValues[idxValue] != _newValues[idxValue]){
                return true;
            }
        }
    }

    // Nothing is different
    ofLogVerbose() << "Nothing is different";
    return false;
    

}

void ofxXbeeNodePin::setPin(pinMode _mode, vector<float> _values){
    m_eMode = _mode;
    
    m_aValues.clear();
    if (_values.size()>0) {
        for(int idxValue=0; idxValue<_values.size(); idxValue++){
            m_aValues.push_back(_values[idxValue]);
        }
    }
    
}

void ofxXbeeNodePin::registerPin(pinMode _mode){
    m_eMode = _mode;
    m_aValues.clear();
    m_aValues.push_back(0);
}


pinMode ofxXbeeNodePin::getMode(){
    return m_eMode;
}

float ofxXbeeNodePin::getAValue(int _orderValue){
    
    if(m_aValues.size()>0){
        if(_orderValue>=0 && _orderValue<m_aValues.size()){
            return m_aValues[_orderValue];
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    
}
