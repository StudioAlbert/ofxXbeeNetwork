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
    static string wrPwm(int _cardId, int _pwmPin, float _value);
    static string wrDrop(int _cardId, int _pwmPin, float _speed);
    static string wrGeneric(int _cardId, string _bigMode, string _fineMode, int _pwmPin, float _value);
    
    static double   reCardID(string msg);
    static bool     reHeartbeat(string msg);
    
    static bool     isComplete(string msg);
    
};
