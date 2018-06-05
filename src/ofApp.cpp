#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	receiver.setup(7402);
	ofSetFrameRate(60);
	ofEnableDepthTest();

	sphere = make_shared<GHSphere>();
	cam.init();
}

//--------------------------------------------------------------
void ofApp::update() {

	while (receiver.hasWaitingMessages()) {
		ofxOscMessage msg;
		receiver.getNextMessage(msg);

		string address = msg.getAddress();
		string event = msg.getArgAsString(0);
		string actor = msg.getArgAsString(1);
		string repo = msg.getArgAsString(2);
		//ofLogNotice() << event;
		sp.add(event, actor, repo);
	}

	sp.update();
	sphere->update();
	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

	cam.begin();
	sphere->draw(cam);
	sp.draw(cam, bShow);
	cam.end();

	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 's') bShow = !bShow;
}
