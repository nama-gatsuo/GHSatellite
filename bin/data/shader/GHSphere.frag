#version 400

in struct Vert {
    vec3 color;
    float depth;
    vec4 pos;
    vec3 bc;
} vert;

flat in int isHit;
out vec4 outputColor;

vec3 calcFlatNormal(vec3 posInViewSpace){
    vec3 dx = dFdx(posInViewSpace);
    vec3 dy = dFdy(posInViewSpace);
    vec3 n = normalize(cross(normalize(dx), normalize(dy)));

    return n;
}

void main() {

    vec3 n = calcFlatNormal(vert.pos.xyz);
    vec3 l = normalize(vec3(1.0, 0.2, -0.5));
    float lamb = clamp(dot(n, l), 0.3, 1.0);

    vec3 c;
    if (any(lessThan(vert.bc, vec3(0.08)))) {
        if (isHit == 1) c = vert.color * lamb;
        else c = vec3(0.5) * lamb;
    } else {
        if (isHit == 1) c = vec3(0.8) * lamb;
        else c = vec3(0.6) * lamb;
    }

    outputColor = vec4(c, 1.);
}
