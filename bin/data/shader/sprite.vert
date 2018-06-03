#version 400

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
in vec4 position;
in vec4 color;

uniform float farClip;
uniform float nearClip;

out vec4 vColor;
out float vDepth;

void main() {

    float size = 6.0;

    vColor = color;
    vec4 p = modelViewMatrix * position;
    vDepth = - p.z / (farClip - nearClip);
    gl_Position = modelViewProjectionMatrix * position;
    gl_PointSize = size * 1000.0 / gl_Position.w;

}
