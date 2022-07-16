#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec4 vPosColor;
out vec2 TexCoord;

uniform mat4 transform;
//uniform float h_offset;

void main() {
  gl_Position = transform * vec4(aPos.x,-aPos.y,aPos.z, 1.0f);
  vPosColor = vec4(aPos, 1.0f);
  ourColor = aColor;
  TexCoord = aTexCoord;
}
