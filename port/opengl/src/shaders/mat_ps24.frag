#version 450

// .kkrieger material pixel shader 24
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, t: texture samples, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 0) in vec4 inColor0;

layout(binding = 1) uniform PSConstants { vec4 c[8]; };
const vec4 k5 = vec4(2.0, -1.0, 0.0, 0.0);
const vec4 k6 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k7 = vec4(1.0, 0.0, 0.0, 0.5);

layout(location = 0) out vec4 outColor;

void main()
{
  vec4 r0 = vec4(0.0);

  {
    vec4 a = c[0] + inColor0;   // add
    vec4 b = k6.zzzz;   // + mov
    r0 = mix(r0, a, bvec4(true, true, true, false));
    r0 = mix(r0, b, bvec4(false, false, false, true));
  }

  outColor = r0;
}
