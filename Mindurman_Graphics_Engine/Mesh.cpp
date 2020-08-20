#include "Mesh.h"

Mesh::Mesh(const std::vector<vertex>& Vertices, const std::vector<unsigned int>& Indices, const std::vector<texture>& Textures, 
	const std::vector<material>& Materials)
{
	vertices = Vertices;
	indices = Indices;
	textures = Textures;
	materials = Materials;

	//std::cout << textures.size() << "--";
	allocate();
}

void Mesh::drawMesh(Shader& shader, GLuint programID)
{
	//------Textures----------
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		shader.setTextureUnit(programID, "myTex", i);

		glBindTexture(GL_TEXTURE_2D, textures[i].ID);
	}
	glUniform1i(glGetUniformLocation(programID, "hasTex"), 1);


	//------Materials----------
	if (!materials.empty()) {
		for (unsigned int i = 0; i < materials.size(); i++) {
			//glUniform1i(glGetUniformLocation(programID, "frag_material.hasTexture"), 0);
			glUniform1i(glGetUniformLocation(programID, "hasTex"), 0);
			glUniform3f(glGetUniformLocation(programID, "frag_material.color_diffuse"), materials[i].diffuse.x, materials[i].diffuse.y, materials[i].diffuse.z);
		}
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::allocate()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vNormal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, texPos));

	glBindVertexArray(0);
}

