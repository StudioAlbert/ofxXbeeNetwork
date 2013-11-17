//
//  ofxXbeeDummyProtocol.cpp
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#include "ofxXbeeDummyProtocol.h"

string ofxXbeeDummyProtocol::wrPwm(string _cardId, int _pin, float _value){
    vector<float> args;
    args.push_back(_value);
    
    return wrGeneric(_cardId, BigMode_Out, FineMode_All, _pin, args);
}

string ofxXbeeDummyProtocol::wrDrop(string _cardId, int _pin, float _position){
    vector<float> args;
    args.push_back(_position);
    
    return wrGeneric(_cardId, BigMode_Out, FineMode_Drop, _pin, args);
}

string ofxXbeeDummyProtocol::wrGeneric(string _cardId, string _bigMode, string _fineMode, int _pwmPin, vector<float> _args){
    
    string return_wrPwm = "";
    vector<float>::iterator   itValue;
    
    return_wrPwm.append(HEAD);
    return_wrPwm.append(_cardId);
    return_wrPwm.append(_bigMode);
    return_wrPwm.append(_fineMode);
    return_wrPwm.append(ofToString(_pwmPin, 0, 3, '0'));
    
    for(itValue = _args.begin(); itValue!=_args.end(); itValue++){
        return_wrPwm.append(ofToString((int)ofMap((*itValue), 0, 1, 0, 255), 0, 3, '0'));
    }
    
    
    return_wrPwm.append(TAIL);
    
    return return_wrPwm;
    
}

string ofxXbeeDummyProtocol::reCardID(string msg){
    
    string sCardId = "";
    
    if(isComplete(msg) && msg.size()>=5){
        
        sCardId += msg[1];
        sCardId += msg[2];
        sCardId += msg[3];
        sCardId += msg[4];

    }

    return sCardId;
    
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
    
        sHead = msg[0];
        sTail = msg[msg.length() - 1];
        
        if (sHead==HEAD && sTail==TAIL) {
            return true;
        }
    }
    
    return false;
    
}


