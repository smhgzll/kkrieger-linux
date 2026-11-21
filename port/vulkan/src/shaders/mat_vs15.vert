#version 450

// .kkrieger material vertex shader 15
//
// Converted once from the shader the 2004 engine generated for this
// material of the game data (port/src/shaders/materials.txt).
// r: temporaries, o: outputs, c: material constants;
// a masked write is mix(old, new, bvec4(mask)).

layout(location = 0) in vec4 inPosition;
layout(location = 2) in vec4 inColor0;
layout(location = 4) in vec4 inTexCoord0;

layout(set = 0, binding = 0) uniform VSConstants { vec4 c[16]; };
const vec4 k24 = vec4(0.5, -0.5, 0.0, 1.0);
const vec4 k25 = vec4(2.0, -1.0, 1.0, 0.001);

out gl_PerVertex { vec4 gl_Position; };
layout(location = 0) out vec4 outColor0;
layout(location = 2) out vec4 outTexCoord0;

void main()
{
  vec4 oPos = vec4(0.0), oD0 = vec4(0.0), oD1 = vec4(0.0), oT0 = vec4(0.0), oT1 = vec4(0.0), oT2 = vec4(0.0), oT3 = vec4(0.0);

  oD0 = inColor0;
  oPos = vec4(dot(inPosition, c[0]), dot(inPosition, c[1]), dot(inPosition, c[2]), dot(inPosition, c[3]));
  oT0 = mix(oT0, inTexCoord0, bvec4(true, true, false, false));

  gl_Position = oPos;
  outColor0 = clamp(oD0, 0.0, 1.0);
  outTexCoord0 = oT0;
}
