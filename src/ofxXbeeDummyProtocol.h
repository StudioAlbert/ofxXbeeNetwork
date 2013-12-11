//
//  ofxXbeeDummyProtocol.h
//  dummy_serial
//
//  Created by Dudley Smith on 26/09/13.
//
//

#pragma once

#include "ofMain.h"

#include "ofxXbeeDummyProtocolDefine.h"

class ofxXbeeDummyProtocol {
    
public:
    static string wrPwm(string _cardId, int _pwmPin, int _value);
    static string wrDrop(string _cardId, int _pwmPin, int _position);
    static string wrGeneric(string _cardId, string _fineMode, int _pwmPin, int _value);
    
    static string   reCardID(string msg);
    static bool     reHeartbeat(string msg);
    
    static bool     isComplete(string msg);
    
    static string   getCardIdString(int _CardId);
    static int      getValueClamped(float _fValue);
    
};
