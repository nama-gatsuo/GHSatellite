#version 400
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

uniform vec4 col;

out vec3 vCol;
out float vId;

void main() {
    vCol = col.rgb;
    vId = gl_VertexID;
    gl_Position = modelViewProjectionMatrix * position;
}
