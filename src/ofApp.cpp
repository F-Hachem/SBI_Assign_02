#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    AssetManager::getInstance()->setup();
    
	shoot = false;

	//load in assets and LEAP
	m_device.connectEventHandler(&ofApp::onLeapFrame, this);
	m_player = AssetManager::IMAGE_SPACECAT;
	m_laser = AssetManager::IMAGE_LASERBEAM;

	//grab controller 
	Leap::Controller * controller = m_device.getController();
	controller->enableGesture(Leap::Gesture::Type::TYPE_SCREEN_TAP, true);
	controller->enableGesture(Leap::Gesture::Type::TYPE_KEY_TAP, true);
	//OIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII CLEAN UP OVER HERE LOVELY! YA HEAR?!
	// controller->enableGesture(Leap::Gesture::Type::TYPE_CIRCLE, true);

}

// function for setting the frame
void ofApp::onLeapFrame(Leap::Frame frame) {
	m_frame = frame;
}

//--------------------------------------------------------------
void ofApp::update(){
	m_device.update();

	const Leap::HandList& hands = m_frame.hands();

	// ofLogNotice( "OF_APP", "hand count" + ofToString( ahnds.count() ) );

	for (int i = 0; i < hands.count(); ++i) {
		// detect hand and tell program we detected a hand
		const Leap::Hand& hand						= hands[i];
		// getting the position of the hand in 3D space
		const Leap::Vector palmPos					= hand.palmPosition();
		// translating the 3D coordinates to openframeworks vector coords
		const ofVec3f ofPalmPos						= ofxLeapMotion::toVec3(hand.palmPosition());
		// stabilizing / reducing noise in position
		const ofVec3f ofStabilizedPalmPos			= ofxLeapMotion::toVec3(hand.stabilizedPalmPosition());

		//get value of grab and pinch strength (number between 0.0f nd 1.0f)
		m_grabStrength = hand.grabStrength();
		m_pinchStrength = hand.pinchStrength();

		//get rotation from Leap data. Note that angels come in radiatns so we must convert
		m_palmRot = ofVec3f(
			ofRadToDeg(hand.direction().pitch()),
			ofRadToDeg(hand.direction().yaw()),
			ofRadToDeg(hand.direction().roll())
		);

		//need to scale values. We do not use mapping as depending on the height of the hand teh boundaries change ( a frustum/come shape is visible to sensor so the lower the hand the less space to move in
		m_palmPos.x = ofPalmPos.x * 7.0f;
		m_palmPos.z = ofPalmPos.z * 5.0f;

		//now we need to set limits to screen so ship can't disappear
		m_palmPos.x = ofClamp(m_palmPos.x, -m_windowWidth/2.0f, m_windowWidth/2.0f);
		m_palmPos.z = ofClamp(m_palmPos.z, -m_windowHeight / 2.0f, m_windowHeight / 2.0f);

		//now change coordinates to middle of screen
		//note how up and down is the Y-axis on Leap and in and out of screen is z-axis ... transposing from a 3D space to a 2D screen
		m_palmPos += ofVec3f(m_windowWidth / 2.0f, 0.0f, m_windowHeight / 2.0f);

		break; //only want one hand position so take the first detected as default ... perhaps a bit hacky. What is a better way?
	}

	const Leap::GestureList& gestures = m_frame.gestures();
	for (int i = 0; i < gestures.count(); ++i)
	{
		const Leap::Gesture& gesture = gestures[i];
		Leap::Gesture::Type type = gesture.type();

		if (type == Leap::Gesture::Type::TYPE_KEY_TAP)
		{
			ofLogNotice("GESTURE!", "Key Tap");
			shoot = true;
			ofLogNotice("shoot = ", ofToString(shoot));
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0); //clear bg to black

    ofImage * playerImageRef = AssetManager::getInstance()->getImage(m_player);
    ofPushMatrix();
        ofTranslate(m_palmPos.x, m_palmPos.z);
		ofRotateZ(m_palmRot.y);
		ofScale(m_pinchStrength + 0.5f, m_pinchStrength + 0.5f, m_pinchStrength + 0.5f);
        
		//draw to screen
        playerImageRef->draw(0,0);
    ofPopMatrix();

	if (shoot)
	{
		ofImage * laserBeamImageRef = AssetManager::getInstance()->getImage(m_laser);
		ofPushMatrix();
			ofTranslate(m_palmPos.x, m_palmPos.z);
			laserBeamImageRef->draw(0, 0);
		ofPopMatrix();
		shoot = false;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}
