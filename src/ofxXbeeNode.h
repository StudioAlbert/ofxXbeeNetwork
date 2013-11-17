//
//  ofxXbeeNode.h
//  saman
//
//  Created by Dudley Smith on 15/10/13.
//
//

#pragma once

#define PIN_MIN 2
#define PIN_MAX 13

#define START_VALUE 0.5f

#define EMPTY_MSGS  "empty"

#include "ofMain.h"
#include "ofxGui.h"

#include "ofxXbeeDummyProtocol.h"
#include "ofxXbeeNodePin.h"

class ofxXbeeNode {

public:
    ofxXbeeNode();
    ofxXbeeNode(const ofxXbeeNode &_xbeeNode);
    
private:
    // Parameter ID for the Xbee card ----------------
protected:
    string      m_sID;
public:
    string      getID(){return m_sID;};
    
    // Array of messages to send ----------------
protected:
    queue<string>      m_aMessages;
    void               pushMessage(string _message);
public:
    queue<string>      getMessages(){return m_aMessages;};
    string             popNextMessage();
    
    // Drive a node is only about adding and adding message --
public:
    void    setAllStrip(int _pin, float _value);
    void    setDrop(int _pin, float _position, float _smoothness);
    
public:
    void setup(string _id);
    
    // Array of outputs
protected:
    map<int, ofxXbeeNodePin> m_aPins;
public:
    map<int, ofxXbeeNodePin> getPins(){return m_aPins;};
    void registerPin(int _pinNum, pinMode _pinMode);
    void setPin(int _pinNum, pinMode _pinMode, vector<float> _values);
    
    // HeartBeat -- We wanna know if this node is already on
protected:
    bool    m_bHeartBeat;
    string  m_sLastHeartBeat;
    string  m_sFirstHeartBeat;
    
public:
    bool    getHeartBeat(){return m_bHeartBeat;}
    void    switchHeartBeat();
    
    // Draw it :/
public:
    void draw(ofPoint _pos, float _xSize, float _ySize);
    
    
};