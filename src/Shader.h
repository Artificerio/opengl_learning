#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <streambuf>   
#include <string>
#include <typeinfo>
#include <iostream>


class Shader {
  public:
    unsigned int id;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    void activate();

    //utils
    std::string loadShaderSrc(const char* filename);
    GLuint compileShader(const char* filepath, GLenum type);

    //uniform function
    void setMat4(const std::string& name, glm::mat4 val);
};

#endif
