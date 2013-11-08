//
//  ofxXbeeNetwork.h
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#pragma once

#define MAX_MSGS_SENT   50

#include "ofxXbeeDummyProtocol.h"
#include "ofxXbeeNode.h"

class ofxXbeeNetwork {
    
    // Array of all nodes of your network
protected:
    map<string, ofxXbeeNode> m_aNodes;
public:
    map<string, ofxXbeeNode> getNodes(){return m_aNodes;};
    // No setter
    
private:
    ofSerial            m_oSerial;
    string              m_sSerialString;
    string              m_sSerialStatus;
    stack<string>      m_aSerialMessages;

    // All stufff required to read
    double  m_iTimesRead;       // how many message did we read?
    string  m_sReadTimeStamp;	// when did we last read?
    string  m_sReadLastMsg;         // What did we read ?
    string  m_sCurrentMsg;



public:
    string getSerialStatus();
    string getSerialFullState();
    
public:
    void setup(string _connectionString);
    void update();
    
    void addNode(string _IDNode);
    void registerNodePin(string _IDNode, int _pinNum, pinMode _pinMode);
    
    // ReDrive orders trough the network to the nodes
    void    setNodeAllStrip(string _IDNode, int _pin, float _value);
    void    setNodeDropPosition(string _IDNode, int _pin, float _position);
    
private:
    void serialSetup(string _connectionString);
    void serialRead();
public:
    void serialSend(string _msgToSend);
    
    // Draw :/
public:
    void draw(bool _drawNodes, bool _drawControl);
    void drawNodes();
    void drawControl();
};
