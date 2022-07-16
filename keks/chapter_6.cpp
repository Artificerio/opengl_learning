#include <cmath>
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
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

#include "../src/Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

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


  Shader interpolate_sh("assets/vertexShader.glsl", "assets/fragmentShader.glsl");
  Shader other_sh("assets/vertexShader.glsl", "assets/fragmentShader2.glsl");

  //vertices array
  float first_triangle[] = {
    //positions          //colors
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  //0
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 1
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f //2
    //second triangle
    //0.0f, 0.0f, 0.0f,
    //0.5f, -0.5f, 0.0f,
    //-0.5f, -0.5f, 0.0f
  };

  float second_triangle[] = {
    //positions      //colors
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f
  };
  //GLuint indices[] = {
  //0, 1, 3, // first triangle
  //3, 2, 0 // second triangle
  //};

  GLuint VAO[2], VBO[2];
  glGenVertexArrays(2, VAO);
  glGenBuffers(2, VBO);

  // first triangle
  // bind vbo1 for the first triangle data and vao1 to store vertex attributes
  glBindVertexArray(VAO[0]); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);

  //triangle1 coordinates attribute
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

  //triangle1 color attributes
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  
 //second triangle
  glBindVertexArray(VAO[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);

  //position attribute 2nd triangle
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

  //color attribute 2nd triangle
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

  glm::mat4 trans = glm::mat4(1.0f);

  //float change = 0.5f;
  //interpolate_sh.activate();
  //interpolate_sh.setFloat("h_offset", change);

  while (!glfwWindowShouldClose(window)) 
  {
    //Specify the color of the background
    glClearColor(0.15f, 0.46f, 0.35f, 1.0f);
    //Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO[0]);
    interpolate_sh.activate();
    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f ), glm::vec3(0.0f, 1.0f, 0.0f));
    interpolate_sh.setMat4("transform", trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(VAO[1]);
    other_sh.activate();
    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 0.0f, 0.1f));
    other_sh.setMat4("transform", trans);
    glDrawArrays(GL_TRIANGLES, 0, 3);

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
