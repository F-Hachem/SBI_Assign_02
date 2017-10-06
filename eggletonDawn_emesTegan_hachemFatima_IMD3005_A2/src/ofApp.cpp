#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    AssetManager::getInstance()->setup();
    m_player = AssetManager::IMAGE_SPACECAT;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0); //clear bg to black

    ofImage * playerImageRef = AssetManager::getInstance()->getImage(m_player);
    ofPushMatrix();
        ofTranslate(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

        //draw to screen
        playerImageRef->draw(0,0);
    ofPopMatrix();
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
