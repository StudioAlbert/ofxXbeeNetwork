//
//  ofxXbeeDummyProtocol.cpp
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#include "ofxXbeeDummyProtocol.h"

string ofxXbeeDummyProtocol::wrPwm(string _cardId, int _pin, int _position){
    return wrGeneric(_cardId, Mode_All, _pin, _position);
}

string ofxXbeeDummyProtocol::wrDrop(string _cardId, int _pin, int _position){
    return wrGeneric(_cardId, Mode_Drop, _pin, _position);
}

string ofxXbeeDummyProtocol::wrGeneric(string _cardId, string _fineMode, int _pwmPin, int _value){
    
    string return_wrPwm = "";
    
    return_wrPwm.append(HEAD);
    return_wrPwm.append(_cardId);
    return_wrPwm.append(_fineMode);
    return_wrPwm.append(ofToString(_pwmPin, 0, PIN_LEN, '0'));
    return_wrPwm.append(ofToString(_value, 0, VAL_LEN, '0'));
    
    return_wrPwm.append(TAIL);
    
    return return_wrPwm;
    
}

string ofxXbeeDummyProtocol::reCardID(string msg){
    
    string sCardId = "";
    
    if(isComplete(msg) && msg.size()>=CARDID_LEN+1){
        for(int idxMsgChar=1; idxMsgChar<=CARDID_LEN; idxMsgChar++){
            sCardId += msg[idxMsgChar];
        }
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

string ofxXbeeDummyProtocol::getCardIdString(int _CardId){
    return ofToString(_CardId, 0, CARDID_LEN, '0');
}


int ofxXbeeDummyProtocol::getValueClamped(float _fValue){
    return ofMap(_fValue, 0, 1, 0, VAL_MAX, true);
}

