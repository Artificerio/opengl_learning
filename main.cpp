#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include <streambuf>   
#include <string>
#include <typeinfo>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string loadShaderSrc(const char*  filename);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
  //initialize and configure glfw
  //library for the windows managment
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // create glfw window
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Repeating OpenGL", NULL, NULL);

  //check if window was createad successfully
  if (window == NULL) {
    std::cout << "Failed to create window" << std::endl;
    glfwTerminate();
    return -1;
  }

  // introduce the window into the current context (make window current)
  glfwMakeContextCurrent(window);

  //register callback to resize window automatically
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // compile vertex shader
  GLuint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  std::string vertexShaderSrc = loadShaderSrc("assets/vertexShader.glsl");
  const GLchar* vertShader = vertexShaderSrc.c_str();
  glShaderSource(vertexShader, 1, &vertShader, NULL);
  glCompileShader(vertexShader);

  //catch error
  int succes;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &succes);
  if (!succes) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << infoLog << std::endl;
  }

  //compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragmentShaderSrc = loadShaderSrc("assets/fragmentShader.glsl");
  const GLchar* fragShader = fragmentShaderSrc.c_str();
  glShaderSource(fragmentShader, 1, &fragShader, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &succes); 
  if (!succes) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << infoLog << std::endl;
  }

  //create shaderprogramm
  GLuint shaderProgramm = glCreateProgram();
  glAttachShader(shaderProgramm, vertexShader);
  glAttachShader(shaderProgramm, fragmentShader);
  glLinkProgram(shaderProgramm);

  glGetProgramiv(shaderProgramm, GL_LINK_STATUS, &succes);
  if (!succes) {
    glGetProgramInfoLog(shaderProgramm, 512, NULL, infoLog);
  }


  GLuint frag_sh_yellow = glCreateShader(GL_FRAGMENT_SHADER);
  std::string frag_sh_yellow_src = loadShaderSrc("assets/fragmentShader2.glsl");
  const GLchar* frag_sh_yellow_ptr = frag_sh_yellow_src.c_str();
  glShaderSource(frag_sh_yellow, 1, &frag_sh_yellow_ptr, NULL);
  glCompileShader(frag_sh_yellow);

  glGetShaderiv(frag_sh_yellow,GL_COMPILE_STATUS, &succes);
  if (!succes) {
    glGetShaderInfoLog(frag_sh_yellow, 512, NULL, infoLog);
    std::cout << infoLog << std::endl;
  }

  GLuint sh_prog_yellow = glCreateProgram();
  glAttachShader(sh_prog_yellow, vertexShader);
  glAttachShader(sh_prog_yellow, frag_sh_yellow);
  glLinkProgram(sh_prog_yellow);

  glGetProgramiv(sh_prog_yellow, GL_LINK_STATUS, &succes);
  if (!succes) {
    glGetProgramInfoLog(sh_prog_yellow, 512, NULL, infoLog);
  }

  //clean-up
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(frag_sh_yellow);

  //vertices array
  float first_triangle[] = {
    //first triangle
    0.0f, 0.0f, 0.0f,//0
    0.5f, 0.5f, 0.0f,// 1
    -0.5f, 0.5f, 0.0f,//2
    //second triangle
    //0.0f, 0.0f, 0.0f,
    //0.5f, -0.5f, 0.0f,
    //-0.5f, -0.5f, 0.0f
  };

  float second_triangle[] = {
    //second triangle
    0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
  };
  //GLuint indices[] = {
  //0, 1, 3, // first triangle
  //3, 2, 0 // second triangle
  //};

  //VAO, VBO
  //GLuint VAO, VBO, EBO;
  //glGenVertexArrays(1, &VAO);
  //glGenBuffers(1, &VBO);
  //glGenBuffers(1, &EBO);
  // bind VBO
  //glBindBuffer(GL_ARRAY_BUFFER, VBO);
  //glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);

  //just array of fucking values, generate them!
  GLuint VAO[2], VBO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  // first triangle
  // bind vbo1 for the first triangle data and vao1 to store vertex attributes
  glBindVertexArray(VAO[0]); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);

  //vertex attribute configuration since aPos is location = 0
  glEnableVertexAttribArray(0);
  //vertex buffer for first triangle associated with vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  //second triangle
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);

  // vertex attribute configuration since (in aPos  is location = 0)
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  //set up EBO
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


  while (!glfwWindowShouldClose(window)) 
  {
    //Specify the color of the background
    glClearColor(0.15f, 0.46f, 0.35f, 1.0f);

    //Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    //draw first triangle
    glUseProgram(shaderProgramm);
    glBindVertexArray(VAO[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //draw second triangle

    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(sh_prog_yellow, "ourColor");

    glUseProgram(sh_prog_yellow);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glBindVertexArray(VAO[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);

    //Swap the back with the front buffer
    glfwSwapBuffers(window);
    glfwSwapInterval(1);
    //Handle Events
    glfwPollEvents();
  }

  //Clean-up
  glfwDestroyWindow(window);
  glfwTerminate();
  glDeleteVertexArrays(2, VAO);
  glDeleteBuffers(2, VBO);
  glDeleteProgram(shaderProgramm);
  glDeleteProgram(sh_prog_yellow);
  return 0;
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

std::string loadShaderSrc(const char* filename) {
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
