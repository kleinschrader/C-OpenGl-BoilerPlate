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