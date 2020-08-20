#pragma once


#include "Textures.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {

public:
	Model(const char* model_path);

	void Draw(Shader& shader, GLuint shaderID);
private:
	std::string dir;

	std::vector<Mesh> meshes;

	/*const char dir[];*/
	void load(const char* model_path);

	void pushMesh(const aiScene* scene);
	void pMesh(aiNode* node, const aiScene* scene);

	Mesh getMesh(aiMesh* mesh, const aiScene* scene);
};