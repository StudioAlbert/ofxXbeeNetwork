//
//  ofxXbeeNetwork.h
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#pragma once

#include "ofxXbeeDummyProtocol.h"
#include "ofxXbeeNode.h"

#define  MaxMessagesTrace   64

class ofxXbeeNetwork {
    
    // Array of all nodes of your network
protected:
    map<string, ofxXbeeNode> m_aNodes;
protected:
    map<string, ofxXbeeNode>::iterator curNodeToSend;
    
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
    string  m_sReadLastMsg;     // What did we read ?
    string  m_sCurrentMsg;



public:
    string getSerialStatus();
    string getSerialFullState();
    
public:
    void setup(string _connectionString);
    void update(bool _read, bool _write, int _nbMaxMessagesWrite = 1000);
    
    void addNode(string _IDNode);
    void registerNodePin(string _IDNode, int _pinNum, pinMode _pinMode);
    void setNodePin(string _IDNode, int _pinNum, pinMode _pinMode, float _newValue);
    
    // ReDrive orders trough the network to the nodes
    void    setNodeAllStrip(string _IDNode, int _pin, float _value);
    void    setNodeDrop(string _IDNode, int _pin, float _position);

private:
    void    sendNodePin(string _IDNode, int _pin, pinMode _mode, float _value);
public:
    void    sendNodePwm(string _IDNode, int _pin, float _brightness);
    void    sendNodeDrop(string _IDNode, int _pin, float _position);
    
private:
    void serialSetup(string _connectionString);
    void serialRead();
    void serialWrite(int _nbMaxMessages);
public:
    void serialSendMsg(string _msgToSend);
    
    // Draw :/
public:
    void draw(bool _drawNodes, bool _drawControl);
    void drawNodes();
    void drawControl();
};
