#version 450

// .kkrieger material pixel shader 28
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, t: texture samples, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 2) in vec4 inTexCoord0;
layout(location = 3) in vec4 inTexCoord1;
layout(location = 4) in vec4 inTexCoord2;

layout(set = 0, binding = 2) uniform samplerCube tex0;
layout(set = 0, binding = 3) uniform samplerCube tex1;
layout(set = 0, binding = 4) uniform sampler3D tex2;
layout(set = 0, binding = 1) uniform PSConstants { vec4 c[8]; };
const vec4 k5 = vec4(2.0, -1.0, 0.0, 0.0);
const vec4 k6 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k7 = vec4(1.0, 0.0, 0.0, 0.5);

layout(location = 0) out vec4 outColor;

void main()
{
  vec4 t0 = vec4(0.0), t1 = vec4(0.0), t2 = vec4(0.0), r0 = vec4(0.0), r1 = vec4(0.0);

  t0 = texture(tex0, inTexCoord0.xyz);
  t1 = texture(tex1, inTexCoord1.xyz);
  t2 = texture(tex2, inTexCoord2.xyz);
  {
    vec4 a = clamp(vec4(dot(((t1 * 2.0 - 1.0)).xyz, k7.xyz)), 0.0, 1.0);   // dp3
    vec4 b = c[0] * t2;   // + mul
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r0 = mix(r0, b, bvec4(false, false, false, true));
  }
  {
    vec4 a = clamp(vec4(dot(((t0 * 2.0 - 1.0)).xyz, k7.xyz)), 0.0, 1.0);   // dp3
    vec4 b = clamp((r0.zzzz * c[1].zzzz + c[1].wwww) * 4.0, 0.0, 1.0);   // + mad
    r1 = mix(r1, a, bvec4(true, true, true, false));
    r1 = mix(r1, b, bvec4(false, false, false, true));
  }
  {
    vec4 a = c[0] * t2;   // mul
    vec4 b = (r1 * r1) * 2.0;   // + mul
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r1 = mix(r1, b, bvec4(false, false, false, true));
  }
  t0 = mix(t0, (r1.wwww * r1.wwww) * 2.0, bvec4(true, true, true, false));
  t0 = mix(t0, clamp((t0 * t0) * 2.0, 0.0, 1.0), bvec4(true, true, true, false));
  {
    vec4 a = r0 * r1;   // mul
    vec4 b = t0.zzzz * r0.wwww;   // + mul
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r0 = mix(r0, b, bvec4(false, false, false, true));
  }

  outColor = r0;
}
