#include "Shader.h"

Shader::Shader(const char* vertex_src, const char* fragment_src) {
	vertex_path = vertex_src;
	fragment_path = fragment_src;
}

GLchar* Shader::getShaderSrc(const char* shaderFilePath) {
	FILE* pFile = nullptr;
	char* output = nullptr;
	int count = 0;

	pFile = fopen(shaderFilePath, "rt");
	if (pFile == NULL) { return NULL; }
	/*else { printf("%d", 1); }*/

	fseek(pFile, 0, SEEK_END);
	count = ftell(pFile);
	rewind(pFile);

	if (count > 0) {
		// Dynamically allocate memory for output ( memory release happens in compileShader() )
		output = (char*)malloc(sizeof(char) * (count+1));
		if (output != NULL) {
			count = fread(output, sizeof(char), count, pFile);
			output[count] = '\0';
		}
	}

	fclose(pFile);
	return output;
}

void Shader::compileShader() {
	//For debugging
	int success;
	char infoLog[512];

	// For now only vertex and fragment shaders
	//GLuint vrtx_shader, frag_shader;
	vrtx_shader = glCreateShader(GL_VERTEX_SHADER);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	char* vrtx_src, * frag_src;
	vrtx_src = getShaderSrc(vertex_path);
	frag_src = getShaderSrc(fragment_path);
	glShaderSource(vrtx_shader, 1, &vrtx_src, NULL);
	glShaderSource(frag_shader, 1, &frag_src, NULL);

	// -------------Compile shaders--------------
	// 1. Compile vertex shader & check if it was successful
	glCompileShader(vrtx_shader);
	glGetShaderiv(vrtx_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vrtx_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}else std::cout << "SHADER_VERTEX_COMPILE_SUCCESSFUL" << std::endl;

	// 2. Compile fragment shader & check if it was successful
	glCompileShader(frag_shader);
	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}else std::cout << "SHADER_FRAGMENT_COMPILE_SUCCESSFUL" << std::endl;

	// Free allocated memory for shader source
	free(vrtx_src);
	free(frag_src);

}

void Shader::delShader() {
	glDeleteShader(vrtx_shader);
	glDeleteShader(frag_shader);
}

GLuint Shader::rtrnProgram() {
	//For debugging
	int success;
	char infoLog[512];

	compileShader();

	GLuint program = glCreateProgram();
	glAttachShader(program, vrtx_shader);
	glAttachShader(program, frag_shader);
	
	glLinkProgram(program);

	// Check if programing is successfuly linked
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}else std::cout << "PROGRAM_LINKING_SUCCESSFUL" << std::endl;

	return program;
}

void Shader::setTextureUnit(GLuint programID, const std::string& name, int uniformValue) {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), uniformValue);
}
