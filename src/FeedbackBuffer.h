#pragma once
#include "ofMain.h"

class FeedbackBuffer {
public:
	FeedbackBuffer() {
		buffer[0].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
		buffer[1].allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
		composite.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	}

	void begin() {

		buffer[1].begin();
		ofClear(0,0);

	}
	void end() {
		buffer[1].end();
		
		buffer[0].begin();
		ofClear(0,0);
		composite.draw(0, 0);
		buffer[0].end();

		composite.begin();
		ofClear(0,0);
		ofDisableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		
		ofSetColor(255, 255);
		buffer[1].draw(0, 0);
		ofSetColor(255, 250);
		buffer[0].draw(0, 0);

		ofDisableBlendMode();
		ofEnableDepthTest();
		composite.end();
	}
	void draw() {
		
		//buffer[1].draw(0, 0);
		composite.draw(0, 0);
	}

private:
	ofFbo buffer[2];
	ofFbo composite;
};
