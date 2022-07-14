#pragma once
#include <GL/gl.h>

GLuint loadShader(GLenum shaderType, const char* path);

GLuint loadVertFragComboProgram(const char* vertexPath,const char* fragmentPath);