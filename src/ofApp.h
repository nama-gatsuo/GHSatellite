#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SatelliteParticles.h"
#include "GHSphere.h"
#include "StateCam.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	StateCam cam;
	shared_ptr<GHSphere> sphere;

	SatelliteParticles sp;
	ofxOscReceiver receiver;
	
	bool bShow = false;
};
