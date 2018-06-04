#pragma once
#include "ofMain.h"

using namespace glm;

struct Trail {
	Trail() {}
	Trail(const vec3& xAxis, const vec3& yAxis, float a) {
		this->xAxis = xAxis;
		this->yAxis = yAxis;
		this->a = a;
		count = 0;
	}

	void update(float t) {

		vertexArray.clear();

		for (int i = 0; i < 20; i++) {
			float x = t - i * 0.02;
			float y = a * x * x - a / 8.;

			vec3 t1 = (x + 0.003) * xAxis + y * yAxis;
			vec3 t2 = (x - 0.003) * xAxis + y * yAxis;

			vertexArray.push_back(t1);
			vertexArray.push_back(t2);
		}
		vbo.setVertexData(vertexArray.data(), vertexArray.size(), GL_DYNAMIC_DRAW);

	}
	void draw() const {

		vbo.draw(GL_TRIANGLE_STRIP, 0, vertexArray.size());

	}

	vec3 xAxis; vec3 yAxis;
	float a;
	ofVbo vbo;
	vector<vec3> vertexArray;
	int count;
};