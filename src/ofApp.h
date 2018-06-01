#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "SatelliteParticles.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

private:
	ofEasyCam cam;
	ofVboMesh sphere;

	SatelliteParticles sp;
	ofxOscReceiver receiver;
};
