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
#include <type_traits>
#include <typeinfo>
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include <stb_image.h>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float mixValue = 0.3f;

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

  //vertices array
  float first_triangle[] = {
    //positions3         //colors3        //textures2
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
  };

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  unsigned int texture1, texture2;
  glGenTextures(1, &texture1);
  glBindTexture(GL_TEXTURE_2D, texture1);
  // set the texture wrapping/filtering options (on currently bound texture)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //texture settings
  //load and generate the texture
  int width, height, nrChannels;
  unsigned char *data = stbi_load("assets/pixel_kaguya.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  glGenTextures(1, &texture2);
  glBindTexture(GL_TEXTURE_2D, texture2);
  
  data = stbi_load("assets/wallhaven-9m2mo1.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture\n";
  }
  stbi_image_free(data);

  // first triangle
  glBindVertexArray(VAO); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
  
  //triangle1 coordinates attribute
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

  //triangle1 color attributes
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

  //triangle1 texture attribute 
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

  glm::mat4 trans = glm::mat4(1.0f);

  interpolate_sh.activate();
  interpolate_sh.setInt("texture1", 0);
  interpolate_sh.setInt("texture2", 1);

  while (!glfwWindowShouldClose(window)) 
  {
    processInput(window);

    //Specify the color of the background
    glClearColor(0.071f, 0.071f, 0.07f, 1.0f);
    //Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);

    //float timeValue = glfwGetTime();
    //float greenValue = (std::tan(sin(timeValue) / 2.0f) + 0.5f);
    //float redValue  = (cos(timeValue) / 1.5f) + 0.3f;
    //float blueValue  = ((sin(timeValue) / 2.0f) + 1.5f);
    //int vertexColorLocation = glGetUniformLocation(interpolate_sh.id, "time_color");
    //glUniform4f(vertexColorLocation, greenValue, redValue, brreValue, 1.0f);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    interpolate_sh.activate();

    //change opactity
    interpolate_sh.setFloat("mixColor", mixValue);

    glBindVertexArray(VAO);
    trans = glm::rotate(trans, glm::radians((float)glfwGetTime() / 100.0f ), glm::vec3(0.0f, 1.0f, 1.0f));
    interpolate_sh.setMat4("transform", trans);
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
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  return 0;
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
   //set opactity
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)  {
    mixValue += 0.05f;
    if (mixValue >= 1.0f) {
      mixValue = 1.0f;
    } 
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    mixValue -= 0.05f;
    if (mixValue <= 0.0f) {
      mixValue = 0.0f;
    }
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and 
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
