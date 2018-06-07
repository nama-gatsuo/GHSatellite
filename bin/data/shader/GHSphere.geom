#version 400

layout (triangles) in;
layout (triangle_strip) out;
layout (max_vertices = 12) out;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;

uniform float farClip;
uniform float nearClip;

in vec3 vColor[];
in vec4 vPos[];
in int vHit[];

out struct Vert {
    vec3 color;
    float depth;
    vec4 pos;
    vec3 bc;
} vert;

flat out int isHit;

void createVertex(in vec4 v, int i) {

    vert.pos = modelViewMatrix * v;
    vert.depth = - vert.pos.z / (farClip - nearClip);
    gl_Position = modelViewProjectionMatrix * v;

    if (i == 0) vert.bc = vec3(1,0,0);
    else if (i == 1) vert.bc = vec3(0,1,0);
    else if (i == 2) vert.bc = vec3(0,0,1);

    EmitVertex();
}

void createFace(in vec4 v0, in vec4 v1, in vec4 v2) {
    createVertex(v0, 0);
    createVertex(v1, 1);
    createVertex(v2, 2);
    EndPrimitive();
}

void main() {

    isHit = 0;
    if (vHit[0] + vHit[1] + vHit[2] > 0) {
        isHit = 1;
    }

    vec3 col = vec3(0);
    for (int i = 0; i < 3; i++) {
        col += vColor[i];
    }
    col /= 3.;
    vert.color = col;

    if (isHit == 1) {
        for (int i = 0; i < 3; i++) {
            createVertex(vPos[i], i);
        }
        EndPrimitive();
    } else {
        float r = length(vPos[0]);

        vec4 m01 = normalize((vPos[0] + vPos[1]) * 0.5) * r;
        vec4 m12 = normalize((vPos[1] + vPos[2]) * 0.5) * r;
        vec4 m20 = normalize((vPos[2] + vPos[0]) * 0.5) * r;
        m01.w = 1.;
        m12.w = 1.;
        m20.w = 1.;

        createFace(vPos[0], m01, m20);
        createFace(vPos[1], m12, m01);
        createFace(vPos[2], m20, m12);
        createFace(m01, m12, m20);
    }


}
