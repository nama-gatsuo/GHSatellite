#pragma once
#include "ofMain.h"
#include "Particle.h"

class ParticleManager {
public:

	ParticleManager() {
		trailShader.load("shader/trail");

		arrowShader.load("shader/arrow.vert", "shader/arrow.frag", "shader/arrow.geom");
		arrowShader.setGeometryInputType(GL_POINTS);
		arrowShader.setGeometryOutputCount(12);
		arrowShader.setGeometryOutputType(GL_TRIANGLE_STRIP);
	}

	void update() {

		vector<vec3> arrowPosArray;
		vector<ofFloatColor> arrowColArray;

		for (auto it = ps.begin(); it != ps.end();) {
			if (it->get()->update()) {
				it = ps.erase(it);
			} else {

				auto& a = it->get()->arrow;
				if (a.isVisible()) {
					arrowPosArray.push_back(a.pos);
					arrowColArray.push_back(a.col);
				}

				it++;
			}
		}

		arrowPoints.setVertexData(arrowPosArray.data(), arrowPosArray.size(), GL_DYNAMIC_DRAW);
		arrowPoints.setColorData(arrowColArray.data(), arrowColArray.size(), GL_DYNAMIC_DRAW);

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

	void drawTrails(const ofCamera& cam) const {
		//ofDisableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		trailShader.begin();
		trailShader.setUniform1f("farClip", cam.getFarClip());
		trailShader.setUniform1f("nearClip", cam.getNearClip());

		for (auto it = ps.begin(); it != ps.end(); it++) {
			trailShader.setUniform1f("life", it->get()->fTime);
			it->get()->trail.draw();
		}
		trailShader.end();
		ofDisableBlendMode();
		//ofEnableDepthTest();
	}

	void drawNames() const {
		for (auto it = ps.begin(); it != ps.end(); it++) {
			float l = it->get()->fTime;
			if (l > 0.3 && l < 0.6) {
				ofDrawLine(it->get()->pos, it->get()->pos + vec3(10, 20, 10));
				ofDrawBitmapString(it->get()->user, it->get()->pos + vec3(10, 20, 10));
			}
		}
	}

	void drawArrows(const ofCamera& cam) const {
		
		arrowShader.begin();
		arrowShader.setUniform1f("farClip", cam.getFarClip());
		arrowShader.setUniform1f("nearClip", cam.getNearClip());

		arrowPoints.draw(GL_POINTS, 0, arrowPoints.getNumVertices());
		arrowShader.end();
	}

	int size() const { return ps.size(); }

private:
	vector<Particle::Ptr> ps;
	ofShader arrowShader;
	ofShader trailShader;
	ofVbo arrowPoints;
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

	void draw(const ofCamera& cam, bool bShow) {
		ofEnableAlphaBlending();
		shader.begin();
		shader.setUniform1f("farClip", cam.getFarClip());
		shader.setUniform1f("nearClip", cam.getNearClip());

		vbo.draw(GL_POINTS, 0, pm.size());
		shader.end();
		
		pm.drawTrails(cam);
		pm.drawArrows(cam);

		if (bShow) pm.drawNames();
		ofDisableAlphaBlending();
	}

private:
	ParticleManager pm;

	ofShader shader;
	ofVbo vbo;
};