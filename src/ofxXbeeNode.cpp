//
//  ofxXbeeNode.cpp
//  saman
//
//  Created by Dudley Smith on 15/10/13.
//
//

#include "ofxXbeeNode.h"

ofxXbeeNode::ofxXbeeNode(){
    
}

ofxXbeeNode::ofxXbeeNode(const ofxXbeeNode &_xbeeNode){

    m_aPins         = _xbeeNode.m_aPins;
    m_aMessages     = _xbeeNode.m_aMessages;
    m_bHeartBeat    = _xbeeNode.m_bHeartBeat;
    m_sID           = _xbeeNode.m_sID;
    
}

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
    
    if(m_aPins[_pin].changePin(pinModePwm, newValues)){
        pushMessage(ofxXbeeDummyProtocol::wrPwm(ofToInt(m_sID), _pin, _value));
    }

}

// -------------------------------------------------
void ofxXbeeNode::setDropPosition(int _pin, float _position){
    
    vector<float> newValues;
    newValues.push_back(_position);
    
    if(m_aPins[_pin].changePin(pinModeDrop, newValues)){
        pushMessage(ofxXbeeDummyProtocol::wrDrop(ofToInt(m_sID), _pin, _position));
    }
    
    
}

// -------------------------------------------------
void ofxXbeeNode::draw(ofPoint _pos, float _xSize, float _ySize){
    ofPushMatrix();
    ofTranslate(_pos);
    
    ofDrawBitmapString(m_sID, ofPoint(10,20));
    
    // HeartBeat --
    ofPushStyle();
    if (m_bHeartBeat==true) {
        ofFill();
        ofSetColor(ofColor::green);
    }else{
        ofNoFill();
        ofSetColor(ofColor::red);
    }
    ofRect(0,0,5,5);
    ofPopStyle();
    
    // Cadre --
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::white);
    
    ofRect(0,0,_xSize,_ySize);
    
    ofPopStyle();
    
    
    
    ofPopMatrix();
}