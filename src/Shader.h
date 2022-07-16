#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <streambuf>   
#include <string>
#include <type_traits>
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
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;

    //uniform function
    void setMat4(const std::string& name, glm::mat4 val);

  private:
    void checkCompileErrors(unsigned int shader, std::string type) {
      int success;
      char infoLog[1024];
      if (type != "PROGRAM")
      {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
          glGetShaderInfoLog(shader, 1024, NULL, infoLog);
          std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
      }
      else
      {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
          glGetProgramInfoLog(shader, 1024, NULL, infoLog);
          std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
      }
    }
};
#endif
