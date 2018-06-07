#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SatelliteParticles.h"
#include "GHSphere.h"
#include "StateCam.h"
#include "Palette.h"
#include "UILayer.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	StateCam cam;

	shared_ptr<GHSphere> sphere;
	shared_ptr<UILayer> ui;
	shared_ptr<SatelliteParticles> sp;
	
	ofFbo compositeFbo;

	ofxOscReceiver receiver;
	
	bool isNameVisible = false;
	bool isUiVisible = false;
	bool isLabelVisible = false;
};
