#version 400

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 12) out;

uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform float farClip;
uniform float nearClip;

struct Vert {
    vec3 color;
    float depth;
    vec3 pos;
};

in vec3 vCol[];
in vec3 vPos[];

out Vert vert;

const float PI = 3.14159265359;

void createVertex(in vec3 v){

    vec4 p = modelViewMatrix * vec4(v, 1.);
    vert.depth = - p.z / (farClip - nearClip);
    vert.color = vCol[0];
    vert.pos = (modelViewProjectionMatrix * vec4(v, 1.)).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(v, 1.);

    EmitVertex();
}


void createFace(in vec3 v1, in vec3 v2, in vec3 v3) {
    createVertex(v1);
    createVertex(v2);
    createVertex(v3);
    EndPrimitive();
}

void main() {

    vec3 t = normalize(-vPos[0]);
    vec3 b = normalize(cross(vPos[0], vec3(0,1,0))) * 2.;
    vec3 n = normalize(cross(t, b)) * 2.;

    vec3 v[3];
    for (int i = 0; i < 3; i++) {
        v[i] = vPos[0] + b * sin(PI*2. * i / 3.) + n * cos(PI*2. * i / 3.);
    }

    vec3 c = vPos[0] + t * 6.;

    createFace(c, v[0], v[1]);
    createFace(c, v[1], v[2]);
    createFace(c, v[2], v[0]);
    createFace(v[0], v[1], v[2]);
}
