#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 color;
out vec4 yellow_color;

void main() {
    gl_Position = vec4(aPos, 1.0);
    //yellow_color= vec4(1.0f, 1.0f, 0.0f, 1.0f);
    if (aPos.x < 0) {
        color = vec4(1.0, vec3(0.5));
    } else if (aPos.x == 0){
        color = vec4(0.3, 1.0, 0.0, 1.0);
    } else {
        color = vec4(vec2(0), 1.0, 1.0);
    }
}
