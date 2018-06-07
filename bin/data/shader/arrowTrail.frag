#version 400

in vec3 vCol;
in float vId;

uniform float time;

out vec4 outputColor;
void main() {

    float a = pow(vId / 16., 0.5) * pow(1. - time, 0.1);
    if (a < 0.1) discard;
    outputColor = vec4(vCol, a);
}
