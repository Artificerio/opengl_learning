#version 330 core
//in vec4 yellow_color;

out vec4 FragColor;

//uniforms are global vairables which are accessible from everywhere
in vec3 ourColor;

void main() {
  FragColor = vec4(ourColor, 1.0f);
}
