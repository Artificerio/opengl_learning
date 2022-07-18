cmake_minimum_required(VERSION 3.19)
project(test)

#dont build docs ane examples for glfw
set(CMAKE_BUILD_TYPE "Debug")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#find opengl package
find_package(OpenGL REQUIRED)

#source code
add_executable(${PROJECT_NAME}
    C:/Libs/glad/src/glad.c
    C:/Libs/stb/src/stb.cpp
    
    src/main.cpp
    src/Shader.h
    src/Shader.cpp

    src/io/Joystick.cpp
    src/io/Joystick.h
    src/io/Keyboard.cpp
    src/io/Keyboard.h
    src/io/Mouse.cpp
    src/io/Mouse.h
)
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

#add glad to the build
add_subdirectory(C:/Libs/glad lib/glad)
#adding glfw to the build
add_subdirectory(C:/Libs/glfw lib/glfw)
#adding glm to the build
add_subdirectory(C:/Libs/glm/glm lib/glm)
#adding stb to the buld
add_subdirectory(C:/Libs/stb lib/stb)

#target_include_directories(${PROJECT_NAME}
    #PUBLIC  C:/Libs/glfw/include/GLFW
#)

#linking add the libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
   glad glfw OpenGL::GL glm stb
)
