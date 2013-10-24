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
    char		bytesRead[3];				// data from serial, we will be trying to read 3
    char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?

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
    void serialSend(string _msgToSend);
    void serialRead();
    
    // Draw :/
public:
    void draw();
    void drawNodes();
    void drawControl();
};
