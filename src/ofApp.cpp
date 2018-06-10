#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
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

	int m = int(ofGetFrameNum() / 500) % 3;
	if (m == 0) isNameVisible = true;
	else isNameVisible = false;

	if (m == 1) isLabelVisible = true;
	else isLabelVisible = false;

	if (int(ofGetFrameNum() / 720) % 2 == 1) isUiVisible = true;
	else isUiVisible = false;

	cam.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofBackgroundGradient(Palette::instance().bg, Palette::instance().bg_end, OF_GRADIENT_CIRCULAR);

	compositeFbo.begin();
	ofClear(0, 0);
	cam.begin();

	// draw transparent trails
	ofEnableDepthTest();
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	sp->draw(cam, isNameVisible, isLabelVisible);
	
	// draw solid sphere
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	sphere->draw(cam);
	
	cam.end();
	compositeFbo.end();

	ofDisableDepthTest();
	compositeFbo.draw(0, 0);
	if (isUiVisible) ui->draw();
    
    //ofDrawBitmapString("fps" + ofToString(ofGetFrameRate()), 12, ofGetHeight()-16);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}
