#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "../header/shader.h"


GLuint loadShader(GLenum shaderType, const char* path) {
  FILE *file = fopen(path,"rb");

  fseek(file, 0L, SEEK_END);
  unsigned long fileSize = ftell(file);
  rewind(file);

  char* code = malloc(fileSize+1);
  fread(code,fileSize,1,file);

  fclose(file);

  code[fileSize] = 0;

  unsigned int shader = glCreateShader(shaderType);

  glShaderSource(shader, 1, (const char**)&code, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      printf("Error compiling shader %s", infoLog);
      abort();
  }

  free(code);

  return shader;
}

GLuint loadVertFragComboProgram(const char* vertexPath,const char* fragmentPath) {
  GLuint prog = glCreateProgram();
  
  GLuint vert = loadShader(GL_VERTEX_SHADER,vertexPath);
  GLuint frag = loadShader(GL_FRAGMENT_SHADER,fragmentPath);

  int success;
  char infoLog[512];

  glAttachShader(prog, vert);
  glAttachShader(prog, frag);
  glLinkProgram(prog);
  glGetProgramiv(prog, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(prog, 512, NULL, infoLog);
      printf("Error linking shader %s", infoLog);
      abort();
  }

  glDeleteShader(vert);
  glDeleteShader(frag);

  return prog;
}