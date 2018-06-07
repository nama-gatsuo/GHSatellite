#pragma once
#include "ofMain.h"
#include  "Events.h"

#define HIT_TIME 40;

using namespace glm;

class GHSphere {
public:
	GHSphere(float radius=30.) {
		mesh = ofMesh::icosphere(radius, 2);
		shader.load("shader/GHSphere.vert", "shader/GHSphere.frag", "shader/GHSphere.geom");
		shader.setGeometryInputType(GL_TRIANGLE_STRIP);
		shader.setGeometryOutputType(GL_TRIANGLE_STRIP);
		shader.setGeometryOutputCount(12);

		ofAddListener(hitEvent, this, &GHSphere::handleHit);
	}

	void handleHit(HitInfo& hit) {

		hitList.emplace_back(hit.pos, hit.col);

	}

	void update() {

		for (auto it = hitList.begin(); it != hitList.end();) {
			if (it->update()) it = hitList.erase(it);
			else it++;
		}

	}

	void draw(const ofCamera& cam) const {

		vector<float> t;
		vector<float> c;
		vector<float> p;

		for (auto& h : hitList) {
			t.push_back(h.time);
			c.push_back(h.col.r); c.push_back(h.col.g); c.push_back(h.col.b);
			p.push_back(h.pos.x); p.push_back(h.pos.y); p.push_back(h.pos.z);
		}
		

		shader.begin();
		shader.setUniform3fv("colv", c.data(), hitList.size());
		shader.setUniform3fv("posv", p.data(), hitList.size());
		shader.setUniform1fv("tv", t.data(), hitList.size());
		shader.setUniform1i("num", hitList.size());
		shader.setUniform1f("time", ofGetElapsedTimef());

		shader.setUniform1f("farClip", cam.getFarClip());
		shader.setUniform1f("nearClip", cam.getNearClip());
		
		mesh.draw();
		shader.end();
		
	}

private:
	ofVboMesh mesh;
	ofShader shader;

	struct Hit {
		
		Hit(const vec3& pos, const ofFloatColor col) {
			this->pos = pos;
			this->col = col;
			time = 0.;
			isDead = false;
		}

		bool update() {
			
			if (time > 1.) isDead = true;
			else time += 1. / HIT_TIME;
			
			return isDead;
		}

		vec3 pos;
		ofFloatColor col;
		float time;
		bool isDead;
	};
	
	vector<Hit> hitList;

};