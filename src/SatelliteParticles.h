#pragma once
#include "ofMain.h"

#define MAX_LIFE 500

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
			
			vec3 t1 = (x + 0.001) * xAxis + y * yAxis;
			vec3 t2 = (x - 0.001) * xAxis + y * yAxis;

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
			float x = (float)time / MAX_LIFE * 2. - 1.; // t
			float y = a * x * x - a / 8.;

			pos = x * xAxis + y * yAxis;

			trail.update(x);

		} else { 
			isDead = true;
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
	Trail trail;
};

class ParticleManager {
public:

	ParticleManager() {
		trailShader.load("shader/trail");
	}

	void update() {

		for (auto it = ps.begin(); it != ps.end();) {
			if (it->get()->update()) it = ps.erase(it);
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

		auto p = std::make_shared<Particle>(ofRandom(0, 30), ofRandom(0, 30), ofRandom(0, 360), ofRandom(2, 5));
		p->col = c;
		p->repo = repo;
		p->user = actor;

		ps.push_back(p);

	}

	vector<vec3> getPos() const {
		vector<vec3> v;
		for (auto it = ps.begin(); it != ps.end(); it++) {
			v.push_back(it->get()->pos);
		}
		return v;
	}
	vector<ofFloatColor> getCol() const {
		vector<ofFloatColor> v;
		for (auto it = ps.begin(); it != ps.end(); it++) {
			v.push_back(it->get()->col);
		}
		return v;
	}

	void drawTrails() const {
		//trailShader.begin();
		for (auto it = ps.begin(); it != ps.end(); it++) {
			it->get()->trail.draw();
		}
		//trailShader.end();
	}

	void drawNames() const {
		ofSetColor(128);
		for (auto it = ps.begin(); it != ps.end(); it++) {
			ofDrawLine(it->get()->pos, it->get()->pos + vec3(10, 20, 10));
			ofDrawBitmapString(it->get()->user, it->get()->pos + vec3(10, 20, 10));
			/*string s = ofToString(it->get()->pos.x) + ",";
			s += ofToString(it->get()->pos.y) + ",";
			s += ofToString(it->get()->pos.z);
			ofDrawBitmapString(s, it->get()->pos + vec3(10, 20, 10));*/
		}
	}

	int size() const { return ps.size(); }

private:
	vector<Particle::Ptr> ps;
	ofShader trailShader;
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
		
		pm.drawTrails();

		if (bShow) pm.drawNames();

	}

private:
	ParticleManager pm;

	ofShader shader;
	ofVbo vbo;
};