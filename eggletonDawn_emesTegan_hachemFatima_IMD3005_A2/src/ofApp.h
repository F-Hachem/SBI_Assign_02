#pragma once

#include "ofMain.h"
#include "AssetManager.h"
#include "ofxLeap.h"

class ofApp : public ofBaseApp{

	public:
        AssetManager::ASSET_IMAGE m_player;

		void setup();
		void update();
		void draw();

        //testing functions
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );

        //Leap Motion function set ups

        ofxLeapMotion::Device m_device;
        Leap::Frame           m_frame;

        ofVec3f m_palmPos;
        ofVec3f m_palmRot;

        float m_pinchStrength;
        float m_grabStrength;
        

		
};
