#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofBackground(Palette::instance().bg);
	receiver.setup(7402);
	ofSetFrameRate(60);
	ofTrueTypeFont::setGlobalDpi(72);
	ofEnableAntiAliasing();

	sphere = make_shared<GHSphere>();
	ui = make_shared<UILayer>();
	sp = make_shared<SatelliteParticles>();

	compositeFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	
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
		
		ofFloatColor c = Palette::instance().colorMapping(event);

		sp->add(event, actor, repo, c);
		ui->add(event, actor, repo, c);
	}

	sp->update();
	sphere->update();
	ui->update();

	int m = int(ofGetFrameNum() / 300) % 3;
	if (int(ofGetFrameNum() / 500) % 4 == 0) isNameVisible = true;
	else isNameVisible = false;

	if (int(ofGetFrameNum() / 600) % 3 == 1) isUiVisible = true;
	else isUiVisible = false;

	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	compositeFbo.begin();
	ofClear(0, 0);
	cam.begin();

	// draw transparent trails
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	sp->draw(cam, isNameVisible);
	
	// draw solid sphere
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	sphere->draw(cam);
	
	cam.end();
	compositeFbo.end();

	ofDisableDepthTest();
	compositeFbo.draw(0, 0);
	if (isUiVisible) ui->draw();

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}
