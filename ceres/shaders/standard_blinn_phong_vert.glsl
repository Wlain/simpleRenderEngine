#version 330
in vec3 position;
in vec3 normal;
in vec4 uv;
out vec2 vUV;
#if defined(S_TANGENTS) && defined(S_NORMALMAP)
in vec4 tangent;
out mat3 vTBN;
#else
out vec3 vNormal;
#endif
out vec3 vWsPos;
#ifdef S_VERTEX_COLOR
in vec4 color;
out vec4 vColor;
#endif


#include "normalmap_incl.glsl"
#include "uniforms_incl.glsl"
#include "shadow_incl.glsl"


void main() {
    vec4 wsPos = g_model * vec4(position, 1.0);
    gl_Position = g_projection * g_view * wsPos;
#if defined(S_TANGENTS) && defined(S_NORMALMAP)
    vTBN = computeTBN(g_model_it, normal, tangent);
#else
    vNormal = normalize(g_model_it * normal);
#endif
    vUV = uv.xy;
    vWsPos = wsPos.xyz;
#ifdef S_VERTEX_COLOR
    vColor = color;
#endif

#ifdef S_SHADOW
    vShadowmapCoord = shadowViewProjOffset * wsPos;
#endif
}