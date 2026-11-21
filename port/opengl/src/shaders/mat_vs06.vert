#version 450

// .kkrieger material vertex shader 6
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, o: outputs, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 0) in vec4 inPosition;

layout(binding = 0) uniform VSConstants { vec4 c[16]; };
const vec4 k24 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k25 = vec4(2.0, -1.0, 1.0, 0.001);

out gl_PerVertex { vec4 gl_Position; };

void main()
{
  vec4 oPos = vec4(0.0), oD0 = vec4(0.0), oD1 = vec4(0.0), oT0 = vec4(0.0), oT1 = vec4(0.0), oT2 = vec4(0.0), oT3 = vec4(0.0), r0 = vec4(0.0);

  r0 = inPosition.wwww + -k24.wwww;
  r0 = c[4] * r0 + inPosition;
  oPos = vec4(dot(r0, c[0]), dot(r0, c[1]), dot(r0, c[2]), dot(r0, c[3]));

  gl_Position = oPos;
}
