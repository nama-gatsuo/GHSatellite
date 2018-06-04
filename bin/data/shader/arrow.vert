#version 400

in vec4 position;
in vec4 color;

out vec3 vPos;
out vec3 vCol;

void main() {

    vPos = position.xyz;
    vCol = color.rgb;

}
