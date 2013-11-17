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
    
    m_sLastHeartBeat = _xbeeNode.m_sLastHeartBeat;
    m_sFirstHeartBeat = _xbeeNode.m_sFirstHeartBeat;
    
}

// -------------------------------------------------
void ofxXbeeNode::setup(string _id){
    m_sID = _id;
    m_bHeartBeat = false;
    m_sLastHeartBeat = "";
    m_sFirstHeartBeat = "";

}

// -------------------------------------------------
void ofxXbeeNode::registerPin(int _pinNum, pinMode _pinMode){
    ofxXbeeNodePin pinToRegister;
    pinToRegister.setup(_pinMode);
    
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
    setPin(_pin, pinModePwm, _value);
}

// -------------------------------------------------
void ofxXbeeNode::setDrop(int _pin, float _position){
    setPin(_pin, pinModeDrop, _position);
}

// -------------------------------------------------
void ofxXbeeNode::setPin(int _pinNum, pinMode _pinMode, float   _value){
    // First we check if the number was noticed first
    map<int, ofxXbeeNodePin>::iterator pinFound;
    
    pinFound = m_aPins.find(_pinNum);
    if(pinFound != m_aPins.end()){
        // pin is found into the existing pins
        m_aPins[_pinNum].set(_pinMode, _value);
    }else{
        ofLogError() << "This num for your pin is not available." << _pinNum;
    }
    
}

// -------------------------------------------------
void ofxXbeeNode::draw(ofPoint _pos, float _xSize, float _ySize){
    ofPushMatrix();
    ofTranslate(_pos);
    
    ofDrawBitmapString(m_sID, ofPoint(10,20));
    
    ofDrawBitmapString("First : " + m_sFirstHeartBeat, ofPoint(10,30));
    ofDrawBitmapString("Last : " + m_sLastHeartBeat, ofPoint(10,40));
    
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


// ----------------------------------------
void ofxXbeeNode::switchHeartBeat(){
    m_bHeartBeat = !m_bHeartBeat;
    
    if (m_sFirstHeartBeat=="") {
        m_sFirstHeartBeat=ofGetTimestampString();
    }
    
    m_sLastHeartBeat = ofGetTimestampString();
    
}