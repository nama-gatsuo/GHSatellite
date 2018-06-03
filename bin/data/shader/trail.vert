#version 400

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
in vec4 position;
in vec4 color;

uniform float farClip;
uniform float nearClip;
uniform float life;

out float vDepth;
out vec2 vTexcoord;
out float vLife;

void main() {
    vLife = life;
    vTexcoord = vec2(floor(gl_VertexID / 2) / 20., gl_VertexID % 2);
    vec4 p = modelViewMatrix * position;
    vDepth = - p.z / (farClip - nearClip);
    gl_Position = modelViewProjectionMatrix * position;
}
