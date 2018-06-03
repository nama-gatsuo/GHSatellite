#version 400

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
in vec4 position;
in vec4 color;

out vec3 vColor;

void main() {

    vColor = vec3(1.);
    gl_Position = modelViewProjectionMatrix * position;


}
