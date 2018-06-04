#pragma once
#include "ofMain.h"

struct HitInfo {
	glm::vec3 pos;
	ofFloatColor col;
};

static ofEvent<HitInfo> hitEvent;
