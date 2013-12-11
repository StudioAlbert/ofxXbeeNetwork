#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAnimatableFloat.h"
#include "ofxXbeeNetwork.h"

class testApp : public ofBaseApp{
	
public:
    void setup();
    void setupGui();
    void setupAnims();
    
    void update();
    void updateGui();
    void updateAnims();
    
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont		font;
    
    ofxPanel    m_pnlConnection;
    ofParameter<string> m_pxConnection;
    
    ofxPanel   m_pnlAnimations;
    ofxLabel   m_lblAnimButtons;
    
    ofxButton  m_btAnimDropOnPin2;
    ofxButton  m_btAnimDropOffPin2;
    ofxButton  m_btAnimPwmOnPin2;
    ofxButton  m_btAnimPwmOffPin2;
    
    ofxButton  m_btAnimDropPin2;
    ofxButton  m_btAnimDropPin3;
    ofxButton  m_btAnimDropPin4;
    ofxButton  m_btAnimDropPin5;
    ofxButton  m_btAnimDropPin6;
    ofxButton  m_btAnimDropPin7;
    ofxButton  m_btAnimDropPin8;
    ofxButton  m_btAnimDropPin9;
    
    ofxButton  m_btAnimFadePin2;
    ofxButton  m_btAnimFadePin3;
    ofxButton  m_btAnimFadePin4;
    ofxButton  m_btAnimFadePin5;
    ofxButton  m_btAnimFadePin6;
    ofxButton  m_btAnimFadePin7;
    ofxButton  m_btAnimFadePin8;
    ofxButton  m_btAnimFadePin9;
    
    ofxLabel   m_lblAnimParams;
    ofParameter<float>  m_pxDropDuration;
    ofParameter<float>  m_pxFadeDuration;
    ofParameter<float>  m_pxDropSmoothness;
    
    map<string, ofxAnimatableFloat> m_aAnims;
    
    ofxPanel        m_pnlGeneric;
    ofxIntSlider    m_sliCardId;
    ofxIntSlider    m_sliPinNumber;
    
    ofxToggle       m_btAllOrDrop;
    ofxButton       m_btSend;
    
    ofxFloatSlider  m_sliDropPin2;
    ofxFloatSlider  m_sliDropPin3;
    ofxFloatSlider  m_sliDropPin4;
    ofxFloatSlider  m_sliDropPin5;
    ofxFloatSlider  m_sliDropPin6;
    ofxFloatSlider  m_sliDropPin7;
    ofxFloatSlider  m_sliDropPin8;
    ofxFloatSlider  m_sliDropPin9;
    ofxFloatSlider  m_sliDropPin10;
    ofxFloatSlider  m_sliDropPin11;
    
    ofxFloatSlider  m_sliAllPin2;
    ofxFloatSlider  m_sliAllPin3;
    ofxFloatSlider  m_sliAllPin4;
    ofxFloatSlider  m_sliAllPin5;
    ofxFloatSlider  m_sliAllPin6;
    ofxFloatSlider  m_sliAllPin7;
    ofxFloatSlider  m_sliAllPin8;
    ofxFloatSlider  m_sliAllPin9;
    ofxFloatSlider  m_sliAllPin10;
    ofxFloatSlider  m_sliAllPin11;

    ofxXbeeNetwork      m_oXbees;
    
    ofxPanel        m_pnlSetupXbeeEmitter;
    ofxButton       m_btStartConfig;
    ofxButton       m_btAskConfig;
    ofxButton       m_btAskNumber;
    ofxButton       m_btEndConfig;
    
    string          nodeKey;
    
    
};

