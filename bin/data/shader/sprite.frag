#version 400

in vec4 vColor;
in float vDepth;
out vec4 outputColor;

void main() {

    vec3 n;
    n.xy = gl_PointCoord.xy * 2.0 - 1.0;
    float r2 = dot(n.xy, n.xy);
    if (r2 > 1.) discard;
    outputColor = vec4(vColor.rgb, vColor.a * (1. - vDepth));
}
