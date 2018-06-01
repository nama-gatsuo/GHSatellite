#pragma once
#include "ofMain.h"

#define MAX_LIFE 500

using namespace glm;

struct Particle {

	Particle(float rx, float ry, float rz, float a) {

		this->a = a;

		mat4 m = mat4();
		m = rotate(rx, vec3(1., 0., 0.)) * rotate(ry, vec3(0., 1., 0.)) * m;

		xAxis = m * vec4(1, 0., 0., 0.) * 3000. / a;
		yAxis = m * vec4(0., 1, 0., 0.) * 300.;
	}

	bool update() {

		time++;
		if (time > MAX_LIFE) isDead = true;

		if (!isDead) {
			float x = (float)time / MAX_LIFE * 2. - 1.; // t
			float y = a * x * x - a / 8.;

			pos = x * xAxis + y * yAxis;
		}

		return isDead;
	}

	bool isDead = false;
	int time = 0;

	vec3 pos;

	vec3 xAxis;
	vec3 yAxis;
	float a;

	ofFloatColor col;
	string user;
	string repo;

};

class ParticleManager {
public:
	void update() {

		for (auto it = ps.begin(); it != ps.end();) {
			if (it->update()) it = ps.erase(it);
			else it++;
		}

	}

	void add(const string& event, const string& actor, const string& repo) {

		ofFloatColor c;
		if (event == "Push") c.set(.3, 1., 0.5);
		else if (event == "Create") c.set(0.3, 1., 0.5);
		else if (event == "IssueComment") c.set(1., 0.2, 0.5);
		else if (event == "PullRequest") c.set(0.9, 1., 0.1);
		else if (event == "Issues") c.set(1.0, 0.8, 0.5);
		else if (event == "Watch") c.set(0.9, 1., 0.1);
		else if (event == "Delete") c.set(0.9, 1., 0.1);
		else if (event == "Fork") c.set(0.9, 1., 0.1);
		else if (event == "PullRequestReviewComment") c.set(0.9, 1., 0.1);
		else c.set(0.4);

		Particle p(ofRandom(0, 30), ofRandom(0, 30), ofRandom(0, 360), ofRandom(2, 5));
		p.col = c;
		p.repo = repo;
		p.user = actor;

		ps.push_back(p);

	}

	vector<vec3> getPos() {
		vector<vec3> v;
		for (auto it = ps.begin(); it != ps.end(); it++) {
			v.push_back(it->pos);
		}
		return v;
	}
	vector<ofFloatColor> getCol() {
		vector<ofFloatColor> v;
		for (auto it = ps.begin(); it != ps.end(); it++) {
			v.push_back(it->col);
		}
		return v;
	}

	void draw() {
		ofSetColor(128);
		for (auto it = ps.begin(); it != ps.end(); it++) {
			ofDrawLine(it->pos, it->pos + vec3(10, 20, 10));
			ofDrawBitmapString(it->user, it->pos + vec3(10, 20, 10));
		}
	}

	int size() const { return ps.size(); }

private:
	vector<Particle> ps;
};

class SatelliteParticles {
public:
	SatelliteParticles() {
		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
		shader.load("shader/sprite");
	}

	void update() {

		pm.update();

		vbo.setVertexData(pm.getPos().data(), pm.size(), GL_DYNAMIC_DRAW);
		vbo.setColorData(pm.getCol().data(), pm.size(), GL_DYNAMIC_DRAW);
		
	}

	void add(const string& event, const string& actor, const string& repo) {

		pm.add(event, actor, repo);

	}

	void draw(bool bShow) {
		shader.begin();
		vbo.draw(GL_POINTS, 0, pm.size());
		shader.end();
		
		if (bShow) pm.draw();

	}

private:
	ParticleManager pm;

	ofShader shader;
	ofVbo vbo;


};