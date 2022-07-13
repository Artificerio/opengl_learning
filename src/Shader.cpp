//TODO: implement more functions for the shader class[]

#include "Shader.h"
#include "glm/gtc/type_ptr.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath ) {
  int succes;
  char infoLog[512];

  GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
  GLuint fragShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
  id = glCreateProgram();
  glAttachShader(id, vertexShader);
  glAttachShader(id, fragShader);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &succes);
  if (!succes) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

};

void Shader::activate() {
  glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char *filename) {
  std::ifstream file;
  std::stringstream buf;
  std::string ret = "";
  file.open(filename);
  if (file.is_open()) {
    std::cout << "opened file " << filename << std::endl;
    buf << file.rdbuf();
    ret = buf.str();
  } else {
    std::cout << "could not open file " << filename << std::endl;
  }
  file.close();
  return ret;
}

GLuint Shader::compileShader(const char *filepath, GLenum type) {
  int succes;
  char infoLog[512];
  
  GLuint ret = glCreateShader(type);
  std::string shaderSrc = loadShaderSrc(filepath);
  const GLchar* shaderPtr = shaderSrc.c_str();
  glShaderSource(ret, 1, &shaderPtr, NULL);
  glCompileShader(ret);

  glGetShaderiv(ret, GL_COMPILE_STATUS, &succes); 
  if (!succes) {
    glGetShaderInfoLog(ret, 512, NULL, infoLog);
    std::cout << infoLog << std::endl;
  }

  return ret;
}


void Shader::setMat4(const std::string &name, glm::mat4 val) {
  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

