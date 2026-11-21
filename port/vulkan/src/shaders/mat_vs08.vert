#version 450

// .kkrieger material vertex shader 8
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, o: outputs, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 8) in vec4 inTangent;

layout(set = 0, binding = 0) uniform VSConstants { vec4 c[16]; };
const vec4 k24 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k25 = vec4(2.0, -1.0, 1.0, 0.001);

out gl_PerVertex { vec4 gl_Position; };
layout(location = 2) out vec4 outTexCoord0;

void main()
{
  vec4 oPos = vec4(0.0), oD0 = vec4(0.0), oD1 = vec4(0.0), oT0 = vec4(0.0), oT1 = vec4(0.0), oT2 = vec4(0.0), oT3 = vec4(0.0), r0 = vec4(0.0), r1 = vec4(0.0), r2 = vec4(0.0);

  oPos = vec4(dot(inPosition, c[0]), dot(inPosition, c[1]), dot(inPosition, c[2]), dot(inPosition, c[3]));
  r0 = inTangent;
  r1 = mix(r1, inNormal.yzxx * r0.zxyy, bvec4(true, true, true, false));
  r1 = mix(r1, -inNormal.zxyy * r0.yzxx + r1, bvec4(true, true, true, false));
  r0 = mix(r0, vec4(dot(inPosition, c[12])), bvec4(true, false, false, false));
  r0 = mix(r0, vec4(dot(inPosition, c[13])), bvec4(false, true, false, false));
  r0 = mix(r0, vec4(dot(inPosition, c[14])), bvec4(false, false, true, false));
  r1 = mix(r1, vec4(dot(inNormal.xyz, c[12].xyz)), bvec4(true, false, false, false));
  r1 = mix(r1, vec4(dot(inNormal.xyz, c[13].xyz)), bvec4(false, true, false, false));
  r1 = mix(r1, vec4(dot(inNormal.xyz, c[14].xyz)), bvec4(false, false, true, false));
  r0 = mix(r0, vec4(dot(r0.xyz, r0.xyz)), bvec4(false, false, false, true));
  r0 = mix(r0, vec4(inversesqrt(abs(r0.w))), bvec4(false, false, false, true));
  r0 = r0 * r0.wwww;
  r1 = mix(r1, vec4(dot(r1.xyz, r1.xyz)), bvec4(false, false, false, true));
  r1 = mix(r1, vec4(1.0 / r1.w), bvec4(false, false, false, true));
  r1 = mix(r1, r1 + r1, bvec4(false, false, false, true));
  r2 = mix(r2, vec4(dot(r0.xyz, r1.xyz)), bvec4(false, false, false, true));
  r2 = mix(r2, r2 * r1, bvec4(false, false, false, true));
  r2 = mix(r2, r1 * r2.wwww + -r0, bvec4(true, true, true, false));
  r2 = mix(r2, r2 * k24 + k24.xxxx, bvec4(true, true, false, false));
  oT0 = mix(oT0, r2, bvec4(true, true, false, false));

  gl_Position = oPos;
  outTexCoord0 = oT0;
}
