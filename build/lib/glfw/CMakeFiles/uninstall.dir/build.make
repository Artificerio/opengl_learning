# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mosek\code\cpp\opengl_template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mosek\code\cpp\opengl_template\build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include lib/glfw/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/glfw/CMakeFiles/uninstall.dir/progress.make

lib/glfw/CMakeFiles/uninstall:
	cd /d C:\Users\mosek\code\cpp\opengl_template\build\lib\glfw && "C:\Program Files\CMake\bin\cmake.exe" -P C:/Users/mosek/code/cpp/opengl_template/build/lib/glfw/cmake_uninstall.cmake

uninstall: lib/glfw/CMakeFiles/uninstall
uninstall: lib/glfw/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
lib/glfw/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : lib/glfw/CMakeFiles/uninstall.dir/build

lib/glfw/CMakeFiles/uninstall.dir/clean:
	cd /d C:\Users\mosek\code\cpp\opengl_template\build\lib\glfw && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : lib/glfw/CMakeFiles/uninstall.dir/clean

lib/glfw/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mosek\code\cpp\opengl_template C:\Libs\glfw C:\Users\mosek\code\cpp\opengl_template\build C:\Users\mosek\code\cpp\opengl_template\build\lib\glfw C:\Users\mosek\code\cpp\opengl_template\build\lib\glfw\CMakeFiles\uninstall.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : lib/glfw/CMakeFiles/uninstall.dir/depend

