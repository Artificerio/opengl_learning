#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec4 vPosColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 time_color; 

void main() {
  //FragColor = texture(texture1, TexCoord) * time_color;
  FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.3f) * time_color;
}
