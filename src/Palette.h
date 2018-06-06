#pragma once
#include "ofColor.h"
#include "ofTrueTypeFont.h"

using namespace glm;

class Palette {
public:
	static Palette& instance() {
		static Palette * p = new Palette();
		return *p;
	}

	ofFloatColor& colorMapping(const string& event) {
		
		ofFloatColor* c;
		
		if (event == "Push") c = &accent_yellow;
		else if (event == "Create") c = &accent_second_blue;
		else if (event == "IssueComment") c = &accent_second_orange;
		else if (event == "PullRequest") c = &white;
		else if (event == "Issues") c = &accent_env_magenta;
		else if (event == "Watch") c = &accent_env_magenta;
		else if (event == "Delete") c = &accent_env_magenta;
		else if (event == "Fork") c = &grey_2;
		else if (event == "PullRequestReviewComment") c = &grey_2;
		else c = &grey_3;
	
		return *c;
	}

	ofFloatColor bg;
	ofFloatColor accent_yellow;
	ofFloatColor accent_second_orange;
	ofFloatColor accent_second_blue;
	ofFloatColor accent_env_magenta;

	ofFloatColor white;
	ofFloatColor grey_1;
	ofFloatColor grey_2;
	ofFloatColor grey_3;

	ofTrueTypeFont noto_sans_light;  
	ofTrueTypeFont track_regular_large;
	ofTrueTypeFont track_regular;

private:
	Palette() {
		bg.setHex(0x252839);
		accent_yellow.setHex(0xF1B631);
		accent_second_orange.setHex(0xF67321);
		accent_second_blue.setHex(0x577590);
		accent_env_magenta.setHex(0xC01F33);
		
		white.setHex(0xffffff);
		grey_1.setHex(0xB5B5B7);
		grey_2.setHex(0x677077);
		grey_3.setHex(0x414250);

		noto_sans_light.load("font/NotoSans-Light.ttf", 12, false);
		noto_sans_light.setLetterSpacing(1.037);
		
		track_regular.load("font/Track.ttf", 12, true);
		track_regular.setLetterSpacing(1.037);

		track_regular_large.load("font/Track.ttf", 48, true);
		track_regular_large.setLetterSpacing(1.037);
		track_regular_large.setLineHeight(72);
	}

};