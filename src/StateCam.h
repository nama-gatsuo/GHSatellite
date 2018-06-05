#pragma once
#include "ofMain.h"

using namespace glm;

#define stay_time 540
#define trans_time 90

class StateCam : public ofCamera {
public:

	void init() {
		current = DISTANT;
		next = TRANS;
		time = 0;
		stateRoll[1] = PI / 2.;
		statePan[1] = PI / 2.;
	}

	void update() {
		
		s = PI / 2. + sin(ofGetElapsedTimef()*0.1) * 0.1;
		pos = getPos(radius, s, t);
		
		time += 1.0f;

		switch (current) {
		case DISTANT: {

			radius = stateRadius[DISTANT];
			t += 0.005;
			ofNode::setGlobalPosition(pos);
			ofNode::lookAt(vec3(0, 0, 0), vec3(0, 1, 0));
			if (time > stay_time) changeState();

		} break;
		case MIDDLE: {

			radius = stateRadius[MIDDLE];
			t += 0.01;
			ofNode::setGlobalPosition(pos);
			ofNode::lookAt(vec3(0, 0, 0), vec3(0, 1, 0));
			if (time > stay_time) changeState();

		} break;
		case CLOSE: {

			radius = stateRadius[CLOSE];
			t += 0.01;
			ofNode::setGlobalPosition(pos);
			ofNode::lookAt(getPos(radius, s, t + .4), normalize(pos));
			
			if (time > stay_time) changeState();

		} break;
		case TRANS: {
			t += 0.02;

			float interpVal = sin((float)time / trans_time * HALF_PI);
			radius = mix(stateRadius[prev], stateRadius[next], interpVal);
			ofNode::setGlobalPosition(pos);
			
			if (next == CLOSE) {
				vec3 to = mix(vec3(0, 0, 0), getPos(radius, s, t + .4), interpVal);
				vec3 up = mix(vec3(0, 1, 0), normalize(pos), interpVal);
				ofNode::lookAt(to, up);
			} else if (prev == CLOSE) {
				vec3 to = mix(getPos(radius, s, t + .4), vec3(0, 0, 0), interpVal);
				vec3 up = mix(normalize(pos), vec3(0, 1, 0), interpVal);
				ofNode::lookAt(to, up);
			} else {
				ofNode::lookAt(vec3(0, 0, 0), vec3(0, 1, 0));
			}

			
			if (time > trans_time) changeState();

		} break;
		default:
			break;
		}

	}

	void changeState() {

		time = 0;
		prev = current;
		current = next;

		if (current != TRANS) {
			next = TRANS;
		} else {

			switch (prev) {
			case DISTANT: next = MIDDLE; break;
			case MIDDLE: next = CLOSE; break;
			case CLOSE: next = DISTANT; break;
			}

		}
		
	}

private:
	vec3 getPos(float r, float s, float t) {
		vec3 pos;
		pos.x = radius * cos(t) * sin(s);
		pos.y = radius * cos(s);
		pos.z = radius * sin(t) * sin(s);

		return pos;
	}

	enum State {
		DISTANT = 0, CLOSE, MIDDLE, TRANS
	};
	float stateRadius[3]{ 900, 36, 300 };
	float stateRoll[3]{ 0, 0, 0 };
	float statePan[3]{ 0, 0, 0 };

	float time = 0;
	State prev;
	State current;
	State next;

	float s; float t;
	float radius;

	vec3 pos;
	vec3 up;
	vec3 target;
};