//
//  ofxXbeeNode.cpp
//  saman
//
//  Created by Dudley Smith on 15/10/13.
//
//

#include "ofxXbeeNode.h"

// -------------------------------------------------
void ofxXbeeNode::setup(string _id){
    m_sID = _id;
}

// -------------------------------------------------
void ofxXbeeNode::registerPin(int _pinNum, pinMode _pinMode){
    ofxXbeeNodePin pinToRegister;
    pinToRegister.registerPin(_pinMode);
    
    m_aPins[_pinNum] = pinToRegister;
    
}

// -------------------------------------------------
void ofxXbeeNode::pushMessage(string _message){
    // Some check before adding
    if(_message.size() > 0){
        m_aMessages.push(_message);
    }
}

// -------------------------------------------------
string ofxXbeeNode::popNextMessage(){
    
    string  message = EMPTY_MSGS;
    
    if (!m_aMessages.empty()) {
        message = m_aMessages.front();
        m_aMessages.pop();
    }
    
    return message;
}

// -------------------------------------------------
void ofxXbeeNode::setAllStrip(int _pin, float _value){
    
    vector<float> newValues;
    newValues.push_back(_value);
    
    if(m_aPins[_pin].changePin(out, newValues)){
        pushMessage(ofxXbeeDummyProtocol::wrPwm(ofToInt(m_sID), _pin, _value));
    }

}

// -------------------------------------------------
void ofxXbeeNode::setDropPosition(int _pin, float _position){
    
    vector<float> newValues;
    newValues.push_back(_position);
    
    if(m_aPins[_pin].changePin(out, newValues)){
        pushMessage(ofxXbeeDummyProtocol::wrDrop(ofToInt(m_sID), _pin, _position));
    }
    
    
}
