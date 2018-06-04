#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SatelliteParticles.h"
#include "GHSphere.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam cam;
	shared_ptr<GHSphere> sphere;

	SatelliteParticles sp;
	ofxOscReceiver receiver;
	
	bool bShow = false;
};
