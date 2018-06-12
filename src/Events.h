#pragma once
#include "ofMain.h"

struct HitInfo {
	HitInfo(const glm::vec3& pos, const ofFloatColor& col) : pos(pos), col(col) {};
	glm::vec3 pos;
	ofFloatColor col;
};

static ofEvent<HitInfo> hitEvent;
