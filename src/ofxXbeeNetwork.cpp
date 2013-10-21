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
}

// -----------------------------------------
void ofxXbeeNetwork::serialSetup(string _connectionString){
        
    connectString = _connectionString;
    
    m_oSerial.listDevices();
    vector <ofSerialDeviceInfo> deviceList = m_oSerial.getDeviceList();
    
    // this should be set to whatever com port your serial device is connected to.
    // (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
    // arduino users check in arduino app....
    m_oSerial.setup(_connectionString, 9600);
    
    nTimesRead = 0;
    nBytesRead = 0;
    readTime = 0;
    memset(bytesReadString, 0, 4);
    
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
    
    map<string, ofxXbeeNode>::iterator oneXbee;
    
    /*
    for (oneXbee = m_aNodes.begin(); oneXbee != m_aNodes.end(); oneXbee++){
        // Here we update (creating messages)
        (*oneXbee).second.update();
    }
    */
    
    for (oneXbee = m_aNodes.begin(); oneXbee != m_aNodes.end(); oneXbee++){
        // No we got the messages and send
        string message = EMPTY_MSGS;
        int nbMessage = 0;

        do{
            // ---
            message = (*oneXbee).second.popNextMessage();
            if(message != EMPTY_MSGS){
                ofLogNotice() << "Message Num = " << ofToString(nbMessage) << " Content:" << message;
                serialSend(message);
            }else{
                ofLogVerbose() << "All messages consumed";
                break;
            }
            
            // Counting to not send too much messages
            nbMessage++;
            
        } while (nbMessage<=MAX_MSGS_SENT);
        
        
        ofLogVerbose() << "End of sending : nb Messages sent = " << nbMessage;
        
    }
    
    // After Sending, we listen
    serialRead();

}

// -----------------------------------------------------------
// (1) write the letter "a" to serial:
void ofxXbeeNetwork::serialSend(string _msgToSend){
    
    if(m_oSerial.isInitialized()){
        // Envoi des caractères
        for(int idxChar = 0; idxChar< _msgToSend.length(); idxChar++){
            m_oSerial.writeByte(_msgToSend[idxChar]);
        }
        // Log Message
        ofLogVerbose() << "Sending : " << _msgToSend;
        
    }else{
        ofLogError() << "Serial not ready : Message not send : " << _msgToSend;
    }

}

// -----------------------------------------------
void ofxXbeeNetwork::serialRead(){
    // (2) read
    // now we try to read 3 bytes
    // since we might not get them all the time 3 - but sometimes 0, 6, or something else,
    // we will try to read three bytes, as much as we can
    // otherwise, we may have a "lag" if we don't read fast enough
    // or just read three every time. now, we will be sure to
    // read as much as we can in groups of three...

    nTimesRead = 0;
    nBytesRead = 0;
    int nRead  = 0;  // a temp variable to keep count per read

    unsigned char bytesReturned[3];

    memset(bytesReadString, 0, 4);
    memset(bytesReturned, 0, 3);

    while( (nRead = m_oSerial.readBytes( bytesReturned, 3)) > 0){
        nTimesRead++;
        nBytesRead = nRead;
    };

    memcpy(bytesReadString, bytesReturned, 3);
    readTime = ofGetElapsedTimef();

}

// -------------------------------------------------
void ofxXbeeNetwork::setNodeAllStrip(string _IDNode, int _pin, float _value){
    // First we check if the id was noticed first
    map<string, ofxXbeeNode>::iterator nodeFound;
    
    nodeFound = m_aNodes.find(_IDNode);
    if(nodeFound != m_aNodes.end()){
        // ID is found into the existing nodes
        (*nodeFound).second.setAllStrip(_pin, _value);
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