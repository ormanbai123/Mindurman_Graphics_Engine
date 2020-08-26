#pragma once

#include <string>
#include <vector>
#include "GL/glew.h"
#include "Matrix.h"
#include "Shader.h"

struct texture {
	GLuint ID = 0;
	std::string type;
};

struct material {
	vec3 diffuse;
    vec3 specular;
	vec3 ambient;
	float shininess;
	int exists;
};

struct vertex {
	vec3 vPos;
	vec3 vNormal;
	vec2 texPos;
};

class Mesh {

public:
	Mesh(const std::vector<vertex>& Vertices,
		 const std::vector<unsigned int>& Indices, 
		 const std::vector<texture>& Textures, 
		 const std::vector<material>& Materials);

	std::vector<unsigned int> indices;
	std::vector<vertex> vertices;
	std::vector<material> materials;
	std::vector<texture> textures;

	void drawMesh(Shader& shader, GLuint programID);
private:
	GLuint VBO = 0; GLuint EBO = 0; GLuint VAO = 0;

	void allocate();
};
