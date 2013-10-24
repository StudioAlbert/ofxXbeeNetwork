#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
    
    setupAnims();
    setupGui();
 	
    font.loadFont("DIN.otf", 64);
    
    //serial.setup("COM4", baud); // windows example
    //serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
    //serial.setup("/dev/ttyUSB0", baud); //linux example
    // USB
    //m_oXbees.setup("tty.usbmodem1411");
    // xBee Adapter
    m_oXbees.setup(m_pxConnection);
    
}

//--------------------------------------------------------------
void testApp::setupAnims(){
    
    for (int idxNode=1; idxNode<=2; idxNode++) {
        string nodeKey = ofToString(idxNode, 0, 1, '0');
        
        for(int idxAnim=2; idxAnim<=6; idxAnim++){
            string animKey = nodeKey + ":" + ofToString(idxAnim, 0, 2, '0') + ":Drop";
            
            ofLogVerbose() << "Creating Drop Animation : " << animKey;
            
            m_aAnims[animKey] = ofxAnimatableFloat();
            m_aAnims[animKey].setRepeatType(PLAY_ONCE);
            m_aAnims[animKey].setCurve(EASE_IN);
            
            m_oXbees.addNode(nodeKey);
            m_oXbees.registerNodePin(nodeKey, 2, out);
            m_oXbees.registerNodePin(nodeKey, 3, out);
            m_oXbees.registerNodePin(nodeKey, 4, out);
            m_oXbees.registerNodePin(nodeKey, 5, out);
            m_oXbees.registerNodePin(nodeKey, 6, out);
            
        }
    }
    
    
}

//--------------------------------------------------------------
void testApp::setupGui(){
    
    // CONNECTIONS ---------------------------------------------------------------------------
    m_pnlConnection.setup("Connection", "settings.xml");
    m_pnlConnection.add(    m_pxConnection.set("Connection", "tty.usbserial-A600KMNU"));
    
    m_pnlConnection.loadFromFile("settings.xml");
    
    // ANIMATIONS ---------------------------------------------------------------------------
    m_pnlAnimations.setup("Animations","settings.xml");
    
    m_pnlAnimations.add(   m_lblAnimButtons.setup("Commands", "Commands"));
    m_pnlAnimations.add(   m_btAnimDropPin2.setup("Drop Anim Pin2"));
    m_pnlAnimations.add(   m_btAnimDropPin3.setup("Drop Anim Pin3"));
    m_pnlAnimations.add(   m_btAnimDropPin4.setup("Drop Anim Pin4"));
    m_pnlAnimations.add(   m_btAnimDropPin5.setup("Drop Anim Pin5"));
    m_pnlAnimations.add(   m_btAnimDropPin6.setup("Drop Anim Pin6"));

    m_pnlAnimations.add(   m_lblAnimButtons.setup("Parameters", "Parameters"));
    m_pnlAnimations.add(   m_pxDropDuration.set("DropDuration", 0, 0, 10));
    m_pnlAnimations.add(   m_pxDropSmoothness.set("DropSmoothness", 0, 0, 10));
    
    m_pnlAnimations.loadFromFile("settings.xml");
    
    // GENERIC ---------------------------------------------------------------------------
    m_pnlGeneric.setup("Generic", "Generic.xml", 10, 200);
    
    m_pnlGeneric.add(   m_sliPinNumber.setup("Pin number", 2, 2, 6));
    m_pnlGeneric.add(   m_btAllOrDrop.setup("All or Drop", "All/Drop"));
    m_pnlGeneric.add(   m_btSend.setup("Sent"));
    
    m_pnlGeneric.add(   m_sliDropPin2.setup("Drop pin 2", 0, 0, 1));
    m_pnlGeneric.add(   m_sliDropPin3.setup("Drop pin 3", 0, 0, 1));
    m_pnlGeneric.add(   m_sliDropPin4.setup("Drop pin 4", 0, 0, 1));
    m_pnlGeneric.add(   m_sliDropPin5.setup("Drop pin 5", 0, 0, 1));
    m_pnlGeneric.add(   m_sliDropPin6.setup("Drop pin 6", 0, 0, 1));
    
    m_pnlGeneric.add(   m_sliAllPin2.setup("All pin 2", 0, 0, 1));
    m_pnlGeneric.add(   m_sliAllPin3.setup("All pin 3", 0, 0, 1));
    m_pnlGeneric.add(   m_sliAllPin4.setup("All pin 4", 0, 0, 1));
    m_pnlGeneric.add(   m_sliAllPin5.setup("All pin 5", 0, 0, 1));
    m_pnlGeneric.add(   m_sliAllPin6.setup("All pin 6", 0, 0, 1));
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    updateAnims();
    updateGui();

    if(m_aAnims["1:2:Drop"].isAnimating()){
        m_sliAllPin2 = 0;
        m_oXbees.setNodeDropPosition("1", 2, m_sliDropPin2);
    }else{
        m_oXbees.setNodeAllStrip("1", 2, m_sliAllPin2);
    }
    
    if(m_aAnims["1:3:Drop"].isAnimating()){
        m_sliAllPin3 = 0;
        m_oXbees.setNodeDropPosition("1", 3, m_sliDropPin3);
    }else{
        m_oXbees.setNodeAllStrip("1", 3, m_sliAllPin3);
    }
    
    if(m_aAnims["1:4:Drop"].isAnimating()){
        m_sliAllPin4 = 0;
        m_oXbees.setNodeDropPosition("1", 4, m_sliDropPin4);
    }else{
        m_oXbees.setNodeAllStrip("1", 4, m_sliAllPin4);
    }
    
    if(m_aAnims["1:5:Drop"].isAnimating()){
        m_sliAllPin5 = 0;
        m_oXbees.setNodeDropPosition("1", 5, m_sliDropPin5);
    }else{
        m_oXbees.setNodeAllStrip("1", 5, m_sliAllPin5);
    }
    
    if(m_aAnims["1:6:Drop"].isAnimating()){
        m_sliAllPin6 = 0;
        m_oXbees.setNodeDropPosition("1", 6, m_sliDropPin6);
    }else{
        m_oXbees.setNodeAllStrip("1", 6, m_sliAllPin6);
    }
    
    m_oXbees.update();
    
}


//--------------------------------------------------------------
void testApp::updateAnims(){
    
    float dt = 1.0f / ofGetFrameRate();
    
    map<string, ofxAnimatableFloat>::iterator   oneAnim;
    for(oneAnim = m_aAnims.begin(); oneAnim != m_aAnims.end(); oneAnim++){
        (*oneAnim).second.update(dt);
    }
    
}
    
//--------------------------------------------------------------
void testApp::updateGui(){
    
    if(m_btAnimDropPin2==true){
        m_aAnims["1:2:Drop"].setDuration(m_pxDropDuration);
        m_aAnims["1:2:Drop"].animateFromTo(0, 1);
    }
    if(m_btAnimDropPin3==true){
        m_aAnims["1:3:Drop"].setDuration(m_pxDropDuration);
        m_aAnims["1:3:Drop"].animateFromTo(0, 1);
    }
    if(m_btAnimDropPin4==true){
        m_aAnims["1:4:Drop"].setDuration(m_pxDropDuration);
        m_aAnims["1:4:Drop"].animateFromTo(0, 1);
    }
    if(m_btAnimDropPin5==true){
        m_aAnims["1:5:Drop"].setDuration(m_pxDropDuration);
        m_aAnims["1:5:Drop"].animateFromTo(0, 1);
    }
    if(m_btAnimDropPin6==true){
        m_aAnims["1:6:Drop"].setDuration(m_pxDropDuration);
        m_aAnims["1:6:Drop"].animateFromTo(0, 1);
    }
    
    m_sliDropPin2 = m_aAnims["1:2:Drop"].val();
    m_sliDropPin3 = m_aAnims["1:3:Drop"].val();
    m_sliDropPin4 = m_aAnims["1:4:Drop"].val();
    m_sliDropPin5 = m_aAnims["1:5:Drop"].val();
    m_sliDropPin6 = m_aAnims["1:6:Drop"].val();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    // FOR REAL ----------------------------------
    m_pnlAnimations.draw();
    m_pnlGeneric.draw();
    
    // Xbee State
    string xBeeFullState = m_oXbees.getSerialFullState();
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(ofGetWidth() - 400, 20);
    
    if(m_oXbees.getSerialStatus() == STATUS_Connected){
        ofSetColor(ofColor::green);
    }else if (m_oXbees.getSerialStatus() == ""){
        ofSetColor(ofColor::orange);
    }else if (m_oXbees.getSerialStatus() == STATUS_NotConnected){
        ofSetColor(ofColor::red);
    }else{
        ofSetColor(ofColor::black);
    }
    
    ofDrawBitmapString(xBeeFullState, 0, 0);
    
    ofPopStyle();
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    switch (key) {
        case 'x':
            m_aAnims["1:2:Drop"].setDuration(m_pxDropDuration);
            m_aAnims["1:2:Drop"].animateFromTo(0, 1);
            break;
        case 'c':
            m_aAnims["1:3:Drop"].setDuration(m_pxDropDuration);
            m_aAnims["1:3:Drop"].animateFromTo(0, 1);
            break;
        case 'v':
            m_aAnims["1:4:Drop"].setDuration(m_pxDropDuration);
            m_aAnims["1:4:Drop"].animateFromTo(0, 1);
            break;
        case 'b':
            m_aAnims["1:5:Drop"].setDuration(m_pxDropDuration);
            m_aAnims["1:5:Drop"].animateFromTo(0, 1);
            break;
        case 'n':
            m_aAnims["1:6:Drop"].setDuration(m_pxDropDuration);
            m_aAnims["1:6:Drop"].animateFromTo(0, 1);
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}

