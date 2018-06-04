#pragma once
#include "ofMain.h"
#include "Events.h"

#define sphereRadius 30.
#define ARROW_LIFE 160

using namespace glm;

struct Arrow {
	void emmit(const vec3& particlePos) {
		isEmitted = true;
		isHit = false;
		time = 0;
		pos = particlePos;
	}

	void update(const vec3& particlePos) {

		if (isEmitted && !isHit) {
			time++;
			fTime = (float)time / ARROW_LIFE;

			pos = mix(particlePos, vec3(0), fTime);

			hitCheck();
		}

	}

	void hitCheck() {

		if (!isHit && length(pos) <= sphereRadius) {
			HitInfo h;
			h.col = col;
			h.pos = pos;
			ofNotifyEvent(hitEvent, h);
			isHit = true;
		}
		
	}

	bool isVisible() {
		return isEmitted && !isHit;
	}

	bool isEmitted = false;
	bool isHit = false;
	int time = 0;
	float fTime = 0.;
	vec3 pos;
	ofFloatColor col;
};
