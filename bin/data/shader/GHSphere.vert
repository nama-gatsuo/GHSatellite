#version 400

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
in vec4 position;
in vec4 color;

uniform float farClip;
uniform float nearClip;

uniform vec3 posv[50];
uniform vec3 colv[50];
uniform float tv[50];
uniform int num;
uniform float time;

flat out vec3 vColor;
out float vDepth;
out vec4 vPos;

const float maxRadius = 12.;
const float PI = 3.14159265359;

void main() {

    float t = time;
    mat3 rot = mat3(
            cos(t),0,sin(t),
            0,1,0,
            -sin(t),0,cos(t)
        );

    vec3 p = rot * position.xyz;
    vColor = vec3(0.2);
    for (int i = 0; i < 50; i++) {
        if (i > num) break;

        float d = distance(posv[i], p);
        float range = maxRadius * (sin(tv[i] * PI) + 0.001);

        if (d < range) {
            float s = 1. - (clamp(d, 2., range) / range);
            vec3 nd = normalize(p);
            vec3 force = nd * s * 10.;

            p += force;
            vColor = colv[i];
            break;
        }
    }


    vPos = modelViewMatrix * vec4(p, 1.);
    vDepth = - vPos.z / (farClip - nearClip);
    vPos = position;
    gl_Position = modelViewProjectionMatrix * vec4(p, 1.);


}
