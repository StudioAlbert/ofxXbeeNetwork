//
//  ofxXbeeDummyProtocol.cpp
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#include "ofxXbeeDummyProtocol.h"

string ofxXbeeDummyProtocol::wrPwm(int _cardId, int _pin, float _value){
    return wrGeneric(_cardId, BigMode_Out, FineMode_All, _pin, _value);
}

string ofxXbeeDummyProtocol::wrDrop(int _cardId, int _pin, float _position){
    return wrGeneric(_cardId, BigMode_Out, FineMode_Drop, _pin, _position);
}

string ofxXbeeDummyProtocol::wrGeneric(int _cardId, string _bigMode, string _fineMode, int _pwmPin, float _arg1){
    
    string return_wrPwm = "";
    
    return_wrPwm.append(HEAD);
    return_wrPwm.append(ofToString(_cardId, 0, 3, '0'));
    return_wrPwm.append(_bigMode);
    return_wrPwm.append(_fineMode);
    return_wrPwm.append(ofToString(_pwmPin, 0, 3, '0'));
    return_wrPwm.append(ofToString((int)ofMap(_arg1, 0, 1, 0, 255), 0, 3, '0'));
    
    return_wrPwm.append(TAIL);
    
    return return_wrPwm;
    
}

double ofxXbeeDummyProtocol::reCardID(string msg){
    
    string sCardId = "";
    double iCardID = 0;
    
    if(ofIsStringInString(msg, HEAD) && ofIsStringInString(msg, TAIL) && msg.size()>=6){
        
        sCardId += msg[3];
        sCardId += msg[4];
        sCardId += msg[5];

        iCardID = ofToDouble(sCardId);
    }

    return iCardID;
    
}

bool ofxXbeeDummyProtocol::reHeartbeat(string msg){
    
    if(ofIsStringInString(msg, HEARTBEAT)){
        return true;
    }else{
        return false;
    }

}

bool ofxXbeeDummyProtocol::isComplete(string msg){
    
    string sHead = "";
    string sTail = "";

    if(ofIsStringInString(msg, HEAD) && ofIsStringInString(msg, TAIL) && msg.length()>=4){
    
        sHead += msg[0];
        sHead += msg[1];
        sHead += msg[2];
        
        sTail = msg[msg.length() - 1];
        
        if (sHead==HEAD && sTail==TAIL) {
            return true;
        }
    }
    
    return false;
    
}


