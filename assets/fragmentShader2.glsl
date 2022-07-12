#version 330 core
//in vec4 yellow_color;

out vec4 FragColor;

uniform vec4 ourColor;

void main() {
  FragColor = ourColor;
}
