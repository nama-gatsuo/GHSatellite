#version 400

in vec2 vTexcoord;
in float vDepth;
in float vLife;

out vec4 outputColor;

const float PI = 3.14159265359;

void main() {
    vec4 col = vec4(vec3(1.), sin(vLife * PI) * (1. - vDepth) * cos(vTexcoord.x * PI));
    outputColor = col;
}
