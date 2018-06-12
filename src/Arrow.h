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

		vec3 b = normalize(cross(normalize(pos), vec3(0, 1, 0)));
		trailRoll = normalize(cross(normalize(pos), b));
	}

	void update(const vec3& particlePos) {
		time++;
		fTime = (float)time / ARROW_LIFE;

		if (isEmitted) {
			
			pos = mix(particlePos, vec3(0), fTime);
			
			trail.push_back(pos + trailRoll * 0.5);
			trail.push_back(pos - trailRoll * 0.5);

			if (trail.size() > 24) {
				trail.erase(trail.begin());
				trail.erase(trail.begin());
			}
			vbo.setVertexData(trail.data(), trail.size(), GL_DYNAMIC_DRAW);

			if (!isHit) hitCheck();
		}

	}

	void hitCheck() {

		if (!isHit && length(pos) <= sphereRadius) {
			HitInfo h(pos, col);
			ofNotifyEvent(hitEvent, h);
			isHit = true;
		}
		
	}

	bool isVisible() {
		return isEmitted && !isHit;
	}
	
	void drawTrail(const ofShader& shader) {
		shader.begin();
		shader.setUniform1f("time", fTime);
		shader.setUniform4f("col", col);
		vbo.draw(GL_TRIANGLE_STRIP, 0, trail.size());
		shader.end();
	}

	bool isEmitted = false;
	bool isHit = false;
	int time = 0;
	float fTime = 0.;
	vec3 pos;
	ofFloatColor col;

	vector<vec3> trail;
	vec3 trailRoll;
	ofVbo vbo;
};
