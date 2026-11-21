#version 450

// .kkrieger material pixel shader 30
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, t: texture samples, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 2) in vec4 inTexCoord0;
layout(location = 3) in vec4 inTexCoord1;
layout(location = 4) in vec4 inTexCoord2;

layout(binding = 2) uniform sampler2D tex0;
layout(binding = 3) uniform samplerCube tex1;
layout(binding = 4) uniform sampler3D tex2;
layout(binding = 1) uniform PSConstants { vec4 c[8]; };
const vec4 k5 = vec4(2.0, -1.0, 0.0, 0.0);
const vec4 k6 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k7 = vec4(1.0, 0.0, 0.0, 0.5);

layout(location = 0) out vec4 outColor;

void main()
{
  vec4 t0 = vec4(0.0), t1 = vec4(0.0), t2 = vec4(0.0), r0 = vec4(0.0), r1 = vec4(0.0);

  t0 = texture(tex0, inTexCoord0.xy);
  t1 = texture(tex1, inTexCoord1.xyz);
  t2 = texture(tex2, inTexCoord2.xyz);
  {
    vec4 a = clamp(vec4(dot(((t1 * 2.0 - 1.0)).xyz, t0.xyz)), 0.0, 1.0);   // dp3
    vec4 b = k5;   // + mov
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r0 = mix(r0, b, bvec4(false, false, false, true));
  }
  r1 = mix(r1, t2 * c[0], bvec4(true, true, true, false));
  r0 = mix(r0, r0 * r1, bvec4(true, true, true, false));

  outColor = r0;
}
