#version 400

in vec3 vColor;
in float vDepth;
out vec4 outputColor;

void main() {
    outputColor = vec4(vColor, 0.5);
}
