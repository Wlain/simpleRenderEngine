#version 330
in vec3 position;
in vec4 uv;
out vec4 vUV;

#include "uniforms_incl.glsl"

void main() {
    gl_Position = g_projection * g_view * g_model * vec4(position,1.0);
    vUV = uv;
}