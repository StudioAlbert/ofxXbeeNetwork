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

