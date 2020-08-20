#pragma once

#define _CRT_SECURE_NO_DEPRECATE 

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

class Shader {
	GLuint vrtx_shader = 0;
	GLuint frag_shader = 0;
public:
	//TODO Shader(char* vertex_src, char* fragment_src, char* geometry_src);
	Shader(const char* vertex_src, const char* fragment_src);

	GLuint rtrnProgram(); // Function returns program ID

	void delShader(); // Function deletes all shaders

	void setTextureUnit(GLuint programID, const std::string& name, int uniformValue);

private:
	GLchar* getShaderSrc(const char* shaderFilePath); // Function takes shader's root(const char*) and returns shader's source 
	void compileShader(); // Function creates and compiles all shaders
	const char* vertex_path = nullptr;
	const char* fragment_path = nullptr;
	// TODO void bindShader();
};