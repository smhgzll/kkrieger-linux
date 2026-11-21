#version 450

// .kkrieger material vertex shader 9
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, o: outputs, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 0) in vec4 inPosition;
layout(location = 1) in vec4 inNormal;
layout(location = 8) in vec4 inTangent;

layout(binding = 0) uniform VSConstants { vec4 c[16]; };
const vec4 k24 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k25 = vec4(2.0, -1.0, 1.0, 0.001);

out gl_PerVertex { vec4 gl_Position; };
layout(location = 2) out vec4 outTexCoord0;
layout(location = 3) out vec4 outTexCoord1;
layout(location = 4) out vec4 outTexCoord2;

void main()
{
  vec4 oPos = vec4(0.0), oD0 = vec4(0.0), oD1 = vec4(0.0), oT0 = vec4(0.0), oT1 = vec4(0.0), oT2 = vec4(0.0), oT3 = vec4(0.0), r0 = vec4(0.0), r1 = vec4(0.0), r2 = vec4(0.0), r3 = vec4(0.0);

  oPos = vec4(dot(inPosition, c[0]), dot(inPosition, c[1]), dot(inPosition, c[2]), dot(inPosition, c[3]));
  r0 = inTangent;
  r1 = mix(r1, inNormal.yzxx * r0.zxyy, bvec4(true, true, true, false));
  r1 = mix(r1, -inNormal.zxyy * r0.yzxx + r1, bvec4(true, true, true, false));
  r2 = mix(r2, c[4] + -inPosition, bvec4(true, true, true, false));
  oT0 = mix(oT0, vec4(dot(r2.xyz, inNormal.xyz)), bvec4(true, false, false, false));
  oT0 = mix(oT0, vec4(dot(r2.xyz, r1.xyz)), bvec4(false, true, false, false));
  oT0 = mix(oT0, vec4(dot(r2.xyz, r0.xyz)), bvec4(false, false, true, false));
  r2 = mix(r2, vec4(dot(r2.xyz, r2.xyz)), bvec4(false, false, false, true));
  r2 = mix(r2, vec4(inversesqrt(abs(r2.w))), bvec4(false, false, false, true));
  r2 = mix(r2, r2 * r2.wwww, bvec4(true, true, true, false));
  r3 = mix(r3, c[6] + -inPosition, bvec4(true, true, true, false));
  r3 = mix(r3, vec4(dot(r3.xyz, r3.xyz)), bvec4(false, false, false, true));
  r3 = mix(r3, vec4(inversesqrt(abs(r3.w))), bvec4(false, false, false, true));
  r3 = mix(r3, r3 * r3.wwww, bvec4(true, true, true, false));
  r2 = mix(r2, r2 + r3, bvec4(true, true, true, false));
  oT1 = mix(oT1, vec4(dot(r2.xyz, inNormal.xyz)), bvec4(true, false, false, false));
  oT1 = mix(oT1, vec4(dot(r2.xyz, r1.xyz)), bvec4(false, true, false, false));
  oT1 = mix(oT1, vec4(dot(r2.xyz, r0.xyz)), bvec4(false, false, true, false));
  oT2 = mix(oT2, inPosition * c[5].wwww + c[5], bvec4(true, true, true, false));

  gl_Position = oPos;
  outTexCoord0 = oT0;
  outTexCoord1 = oT1;
  outTexCoord2 = oT2;
}
