//
//  ofxXbeeNetwork.cpp
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#include "ofxXbeeNetwork.h"

// -----------------------------------------
void ofxXbeeNetwork::setup(string _connectionString){
    serialSetup(_connectionString);
    
    curNodeToSend = m_aNodes.begin();
    
}

// -----------------------------------------
void ofxXbeeNetwork::serialSetup(string _connectionString){
        
    m_sSerialString = _connectionString;
    
    m_oSerial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = m_oSerial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    m_oSerial.setup(_connectionString, 9600);
    
    m_iTimesRead = 0;
    m_sReadTimeStamp = ofGetTimestampString();
    m_sReadLastMsg = "init.....";
    m_sCurrentMsg = "";
    
}

// -----------------------------------------------
void ofxXbeeNetwork::addNode(string _IDNode){
    // Setup the node
    ofxXbeeNode nodeToAdd;
    nodeToAdd.setup(_IDNode);
    // Add to array
    m_aNodes[_IDNode] = nodeToAdd;
}



// -----------------------------------------------
void ofxXbeeNetwork::registerNodePin(string _IDNode, int _pinNum, pinMode _pinMode){
    m_aNodes[_IDNode].registerPin(_pinNum, _pinMode);
}

// -----------------------------------------------
void ofxXbeeNetwork::update(){
    
    int nbMessage = 0;
    
    if(!m_aNodes.empty()){
        
    // We just send a node at a time
    curNodeToSend++;
    if(curNodeToSend == m_aNodes.end()){
        curNodeToSend = m_aNodes.begin();
    }
    
    
    // No we got the messages and send
    string message = EMPTY_MSGS;

    do{
        // ---
        message = (*curNodeToSend).second.popNextMessage();
        if(message != EMPTY_MSGS){
            //ofLogNotice() << "Message Num = " << ofToString(nbMessage) << " Content:" << message;
            serialSend(message);
        }else{
            //ofLogVerbose() << "All messages consumed";
            break;
        }
        
        // Counting to not send too much messages
        nbMessage++;
            
    } while (nbMessage<=MAX_MSGS_SENT);
    }
    
    // After Sending, we listen
    serialRead();
    
}

// -----------------------------------------------------------
void ofxXbeeNetwork::serialSend(string _msgToSend){
    
    if(m_oSerial.isInitialized()){
        
        // Envoi des caractères
        unsigned char *msgChar = (unsigned char *)_msgToSend.c_str();
        m_oSerial.writeBytes(msgChar, _msgToSend.length());
        
        // Log Message
        ofLogVerbose() << "Sending : " << _msgToSend;
        
        // Logging
        m_aSerialMessages.push(ofGetTimestampString() + " : " +_msgToSend);
        if (m_aSerialMessages.size()>10) {
            m_aSerialMessages.pop();
        }
        
        // Status
        m_sSerialStatus = STATUS_Connected;
        
    }else{
        ofLogError() << "Serial not ready : Message not send : " << _msgToSend;
        // Status
        m_sSerialStatus = STATUS_NotConnected;
    }

}

// -----------------------------------------------
void ofxXbeeNetwork::serialRead(){
    
    vector<string>   receivedMsg;
    
    string  oneMessage = "";
    string  sCardId = "";
    bool    heartBeat = false;
    
    bool    gotHead = false;
    
    if(m_oSerial.isInitialized()){

    if(m_oSerial.available()){
        
        while(m_oSerial.available()){
            
            m_sCurrentMsg += m_oSerial.readByte();
            
            if (m_sCurrentMsg.size()>=1 && m_sCurrentMsg[0] != '[') {
                m_sCurrentMsg = "";
            }else if (m_sCurrentMsg.size()>=2 && m_sCurrentMsg[1] != '['){
                m_sCurrentMsg = "";
            }else if (m_sCurrentMsg.size()>=3 && m_sCurrentMsg[2] != '['){
                m_sCurrentMsg = "";
            }
        
            // On parse les messages ------
            if (ofxXbeeDummyProtocol::isComplete(m_sCurrentMsg)) {
                receivedMsg.push_back(m_sCurrentMsg);
                m_sCurrentMsg = "";
            }
            
        };
        
        m_iTimesRead ++;
        
        
        while (!receivedMsg.empty())
        {
            oneMessage  = receivedMsg.back();
            receivedMsg.pop_back();
            
            m_sReadTimeStamp = ofGetTimestampString();
            m_sReadLastMsg = oneMessage;
            
            sCardId         = ofxXbeeDummyProtocol::reCardID(oneMessage);
            heartBeat       = ofxXbeeDummyProtocol::reHeartbeat(oneMessage);
            
            ofLogVerbose() << "Message Read : " << oneMessage << " ID Card: " << sCardId << " Heartbeat: " << ofToString(heartBeat);
            
            if(sCardId!="" && heartBeat==true){
                // in case of heartbeat
                map<string, ofxXbeeNode>::iterator oneNode = m_aNodes.find(sCardId);
                if(oneNode!=m_aNodes.end()){
                    (*oneNode).second.switchHeartBeat();
                }
            }
        }
    }
    }
    
    

}

// -------------------------------------------------
string ofxXbeeNetwork::getSerialStatus(){
    return m_sSerialStatus;
}

// -------------------------------------------------
string ofxXbeeNetwork::getSerialFullState(){
    
    string fullState;
    
    fullState.append("Connection string : " + m_sSerialString + "\n");
    fullState.append("Connection status : " + m_sSerialStatus + "\n");
    
    fullState.append("\n");
    fullState.append("Current reading :\n");
    fullState.append(m_sCurrentMsg + "\n");
    
    fullState.append("Nb Message read :\n");
    fullState.append(ofToString(m_iTimesRead) + "\n");
    
    fullState.append("Last Message read :\n");
    fullState.append(m_sReadTimeStamp + " : " + m_sReadLastMsg + "\n");
    
    fullState.append("\n");
    fullState.append("Messages written :\n");
    
    while (!m_aSerialMessages.empty()) {
        fullState.append(m_aSerialMessages.top() + "\n");
        m_aSerialMessages.pop();
    }
    
    
    return fullState;
    
}

// -------------------------------------------------
void ofxXbeeNetwork::setNodeAllStrip(string _IDNode, int _pin, float _value){
    
    // First we check if the id was noticed first
    map<string, ofxXbeeNode>::iterator nodeFound;
    
    nodeFound = m_aNodes.find(_IDNode);
    if(nodeFound != m_aNodes.end()){
        // ID is found into the existing nodes
        (*nodeFound).second.setAllStrip(_pin, _value);
    }else{
        ofLogError() << "This ID for your node is not available." << _IDNode;
    }

}

// -------------------------------------------------
void ofxXbeeNetwork::setNodeDropPosition(string _IDNode, int _pin, float _position){
    // First we check if the id was noticed first
    map<string, ofxXbeeNode>::iterator nodeFound;
    
    nodeFound = m_aNodes.find(_IDNode);
    if(nodeFound != m_aNodes.end()){
        // ID is found into the existing nodes
        (*nodeFound).second.setDropPosition(_pin, _position);
    }
    
}

// -------------------------------------------------
void ofxXbeeNetwork::draw(bool _drawNodes, bool _drawControl){
    if(_drawNodes)      drawNodes();
    if(_drawControl)    drawControl();
}

// -------------------------------------------------
void ofxXbeeNetwork::drawControl(){

    // Xbee State
    string xBeeFullState = getSerialFullState();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(20, 20);
    
    if(getSerialStatus() == STATUS_Connected){
        ofSetColor(ofColor::green);
    }else if (getSerialStatus() == ""){
        ofSetColor(ofColor::orange);
    }else if (getSerialStatus() == STATUS_NotConnected){
        ofSetColor(ofColor::red);
    }else{
        ofSetColor(ofColor::black);
    }
    
    ofDrawBitmapString(xBeeFullState, 0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    
    
    
}

// ------------------------------------------
void ofxXbeeNetwork::drawNodes(){
    
    map<string, ofxXbeeNode>::iterator oneNode;
    int idxNode = 0;
    int sizeOfANode = 50;
    
    // Draw the nodes -----------------
    for (oneNode=m_aNodes.begin(); oneNode!=m_aNodes.end(); oneNode++) {
        // ---------
        (*oneNode).second.draw(ofPoint((sizeOfANode+10)*++idxNode, 10), sizeOfANode, sizeOfANode);
    }
}
