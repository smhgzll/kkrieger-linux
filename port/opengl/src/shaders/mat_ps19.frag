#version 450

// .kkrieger material pixel shader 19
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, t: texture samples, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 2) in vec4 inTexCoord0;
layout(location = 3) in vec4 inTexCoord1;

layout(binding = 2) uniform sampler2D tex0;
layout(binding = 3) uniform sampler2D tex1;
layout(binding = 1) uniform PSConstants { vec4 c[8]; };
const vec4 k5 = vec4(2.0, -1.0, 0.0, 0.0);
const vec4 k6 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k7 = vec4(1.0, 0.0, 0.0, 0.5);

layout(location = 0) out vec4 outColor;

void main()
{
  vec4 t0 = vec4(0.0), t1 = vec4(0.0), r0 = vec4(0.0);

  t0 = texture(tex0, inTexCoord0.xy);
  t1 = texture(tex1, inTexCoord1.xy);
  r0 = mix(r0, vec4(dot(t0.xyz, t1.xyz)), bvec4(true, true, true, false));
  {
    vec4 a = (r0 * c[2]) * 4.0;   // mul
    vec4 b = k6.wwww;   // + mov
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r0 = mix(r0, b, bvec4(false, false, false, true));
  }

  outColor = r0;
}
