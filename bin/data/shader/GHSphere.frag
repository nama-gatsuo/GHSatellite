#version 400

in vec4 vColor;
in float vDepth;
in vec4 vPos;

out vec4 outputColor;

vec3 calcFlatNormal(vec3 posInViewSpace){
    vec3 dx = dFdx(posInViewSpace);
    vec3 dy = dFdy(posInViewSpace);
    vec3 n = normalize(cross(normalize(dx), normalize(dy)));

    return n;
}

void main() {

    vec3 n = calcFlatNormal(vPos.xyz);
    vec3 l = normalize(vec3(0.5, 1.0, 0.5));
    vec3 c = vec3(1.) * clamp(dot(n, l), 0., 1.0);

    outputColor = vec4(c, 1.);
}
