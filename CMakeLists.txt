cmake_minimum_required(VERSION 3.10)

# set the project name
project(C-OpenGl-BoilerPlate)

# add the executable
add_executable(C-OpenGl-BoilerPlate main.c)

target_link_libraries(C-OpenGl-BoilerPlate PUBLIC GL GLU glfw GLEW)