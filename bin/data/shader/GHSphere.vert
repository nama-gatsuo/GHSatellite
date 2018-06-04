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
out vec4 vPos;

void main() {


    vColor = color;
    vPos = modelViewMatrix * position;
    vDepth = - vPos.z / (farClip - nearClip);
    gl_Position = modelViewProjectionMatrix * position;


}
