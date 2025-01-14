#version 330
in vec3 position;
in vec3 normal;
#ifdef S_VERTEX_COLOR
in vec4 color;
out vec4 vColor;
#endif
in vec4 uv;
out vec2 vUV;

#include "uniforms_incl.glsl"

void main() {
    gl_Position = g_model * vec4(position,1.0);
    vUV = uv.xy;
}