#pragma once
#include "ofMain.h"
#include "Arrow.h"
#include "Trail.h"

#define MAX_LIFE 500

using namespace glm;

struct Particle {
	using Ptr = shared_ptr<Particle>;
	Particle(float rx, float ry, float rz, float a) {

		this->a = a;

		mat4 m = mat4();
		m = rotate(rx, vec3(1., 0., 0.)) * rotate(ry, vec3(0., 1., 0.)) * m;

		xAxis = m * vec4(1, 0., 0., 0.) * 3000. / a;
		yAxis = m * vec4(0., 1, 0., 0.) * 300.;

		trail = Trail(xAxis, yAxis, a);
		
	}

	bool update() {

		time++;
		if (time < MAX_LIFE) {
			fTime = (float)time / MAX_LIFE;
			float x = fTime * 2. - 1.;
			float y = a * x * x - a / 8.;

			pos = x * xAxis + y * yAxis;

			trail.update(x);
			col.a = sin(fTime * PI);

			if (time == (int)MAX_LIFE / 2) {
				arrow.emmit(pos);
				arrow.col = col;
			}
			arrow.update(pos);

		} else {
			isDead = true;
		}

		return isDead;
	}

	bool isDead = false;
	int time = 0;
	float fTime = 0.;

	vec3 pos;

	vec3 xAxis; vec3 yAxis;
	float a;

	ofFloatColor col;
	string user;
	string repo;

	Trail trail;
	Arrow arrow;
};
