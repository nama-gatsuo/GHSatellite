#pragma once
#include "ofMain.h"

class GHSphere {
public:
	GHSphere(float radius=30.) {
		mesh = ofMesh::icosphere(radius, 2);
		shader.load("shader/GHSphere");
	}

	void update() {

	}

	void draw(const ofCamera& cam) const {
		shader.begin();
		shader.setUniform1f("farClip", cam.getFarClip());
		shader.setUniform1f("nearClip", cam.getNearClip());
		mesh.draw();
		shader.end();
	}

private:
	ofVboMesh mesh;
	ofShader shader;


};