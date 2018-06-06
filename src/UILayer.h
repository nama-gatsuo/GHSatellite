#pragma once
#include "Palette.h"
#include "ofMain.h"

class UILayer {
public:
	UILayer() {
		ofFbo::Settings s;
		s.width = 1920;
		s.height = 1080;
		s.internalformat = GL_RGBA;
		s.useDepth = true;
		s.useStencil = true;
		s.depthStencilAsTexture = true;
		fbo.allocate(s);

		string m;
		switch(ofGetMonth()) {
		case 1: m = "January"; break;
		case 2: m = "February"; break;
		case 3: m = "March"; break;
		case 4: m = "April"; break;
		case 5: m = "May"; break;
		case 6: m = "June"; break;
		case 7: m = "July"; break;
		case 8: m = "August"; break;
		case 9: m = "September"; break;
		case 10: m = "October"; break;
		case 11: m = "November"; break;
		case 12: m = "December"; break;
		}

		date = ofToString(ofGetDay()) + ", " + m + " " + ofToString(ofGetYear());

	}

	void add(const string& event, const string& actor, const string& repo, const ofFloatColor& c) {
		rows.emplace_back(event, actor, repo, c);
		if (rows.size() > maxNunRows) rows.erase(rows.begin());
	}

	void update() {
		
		fbo.begin();
		ofClear(0, 0);

		auto& font1 = Palette::instance().noto_sans_light;
		auto& font2 = Palette::instance().track_regular;
		auto& font3 = Palette::instance().track_regular_large;

		ofSetColor(255);

		float h = startY;
		font2.drawString("USER", actorStartX, h);
		font2.drawString("EVENT", eventStartX, h);
		font2.drawString("REPOSITORY", repoStartX, h - 3);

		ofDrawLine(actorStartX, h, ofGetWidth()/2, h);

		for (auto& row : rows) {

			h += lineHeightY;

			ofSetColor(255);
			font1.drawString(row.actor, actorStartX, h);
			ofSetColor(row.c);
			font1.drawString(row.event, eventStartX, h);

			ofSetColor(255);
			font1.drawString(row.repoOwner + " / " + row.repoName, repoStartX, h);

		}
		
		string hms = makeDigit(ofGetHours()) + " : " + makeDigit(ofGetMinutes()) + " : " + makeDigit(ofGetSeconds());
		
		font3.drawString(hms + "\n" + date, ofGetWidth() - 512, ofGetHeight() - 128);

		fbo.end();
	}

	void draw() const {
		fbo.draw(0, 0);
	}
	
private:
	ofFbo fbo;
	string date;
	
	struct Row {
		Row(const string& event, const string& actor, const string& repo, const ofFloatColor& c) {
			this->actor = "@" + actor;

			vector<string> rs = ofSplitString(repo, "/");
			this->repoOwner = rs[0];
			this->repoName = rs[1];

			this->event = event;
			this->c = c;
		};
		string actor;
		ofFloatColor c;
		string event;
		string repoName;
		string repoOwner;
	};
	vector<Row> rows;

	string makeDigit(int digit) {
		
		string sd;

		if (digit < 10) {
			sd = ofToString("0") + ofToString(digit);
		} else {
			sd = ofToString(digit);
		}

		return sd;
	}


	float lineHeightY = 24;
	float startY = 40;
	float actorStartX = 16;
	float eventStartX = 256;
	float repoStartX = 512;

	int maxNunRows = 42;
};