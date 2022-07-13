#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec4 vPosColor;

uniform mat4 transform;
//uniform float h_offset;

void main() {
    vPosColor = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    //ourColor = aColor;
    //yellow_color= vec4(1.0f, 1.0f, 0.0f, 1.0f);
    //if (aPos.x < 0) {
        //color = vec4(1.0, vec3(0.5));
    //} else if (aPos.x == 0){
        //color = vec4(0.3, 1.0, 0.0, 1.0);
    //} else {
        //color = vec4(vec2(0), 1.0, 1.0);
    //}
}
