#version 400

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
in vec4 position;
in vec4 color;

out vec3 vColor;
out float vDepth;

void main() {

    float size = 10.0;

    vColor = color.rgb;
    vec4 p = modelViewMatrix * position;
    vDepth = - p.z / 200.;
    gl_Position = modelViewProjectionMatrix * position;
    gl_PointSize = size * 1000.0 / gl_Position.w;

}
