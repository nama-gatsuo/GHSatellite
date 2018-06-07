#version 400

in vec4 position;

uniform vec3 posv[50];
uniform vec3 colv[50];
uniform float tv[50];
uniform int num;
uniform float time;

out vec3 vColor;
out vec4 vPos;
out int vHit;
out vec3 vForce;

const float maxRadius = 12.;
const float PI = 3.14159265359;

void main() {

    float t = -time * 0.2;
    mat3 rot = mat3(
            cos(t),0,sin(t),
            0,1,0,
            -sin(t),0,cos(t)
        );

    vec3 p = rot * position.xyz;

    vColor = vec3(0.4);
    vHit = 0;

    for (int i = 0; i < 50; i++) {
        if (i > num) break;

        float d = distance(posv[i], p);
        float range = maxRadius * (sin(tv[i] * PI) + 0.001);

        if (d < range) {
            float s = 1. - (clamp(d, 2., range) / range);
            vec3 nd = normalize(p);
            vec3 force = nd * s * 6.;

            p += force;
            vColor = colv[i];
            vHit = 1;
            break;
        }
    }

    vPos = vec4(p, 1.);

}
