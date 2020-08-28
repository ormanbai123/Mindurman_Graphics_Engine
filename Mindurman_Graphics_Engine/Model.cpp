#include "Model.h"

Model::Model(const char* model_path) {
	std::string s = model_path;
	size_t t = s.find_last_of("/");
	dir = s.substr(0, t);

	load(model_path);
}

void Model::Draw(Shader& shader, GLuint shaderID) {
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].drawMesh(shader, shaderID);
	}
}

void Model::load(const char* model_path)
{
	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_POINT | aiPrimitiveType_LINE);
	const aiScene* scene = importer.ReadFile(model_path, aiProcess_JoinIdenticalVertices | 
		                                                 aiProcess_Triangulate |
		                                                 aiProcess_SortByPType | 
		                                                 aiProcess_GenNormals  |
	                                                     aiProcess_GenUVCoords |
		                                                 aiProcess_TransformUVCoords/*| aiProcess_FlipUVs*/);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ASSIMP_MODEL_LOADING_FAILED" << importer.GetErrorString() << "\n";
		return;
	}else std::cout << "Assimp_Loading_Completed" << std::endl;
	
	//----------For Debugging------------------
	//std::cout << scene->mRootNode->mNumMeshes<<std::endl; 
	/*std::cout << scene->mNumMeshes<<std::endl;
	std::cout << scene->mMeshes[0]->mVertices[0].x;*/
	if (scene->HasLights() == true) {
		std::cout << "Scene has lights" << std::endl;
	}else std::cout << "Scene has NO lights" << std::endl;

	//std::cout << "Number of children " << scene->mRootNode->mNumChildren << std::endl;
	//std::cout << "Number of meshes in root Node " << scene->mRootNode->mNumMeshes << std::endl;
	//std::cout << "Number of meshed of first children " << scene->mRootNode->mChildren[0]->mNumMeshes << std::endl;
	std::cout << "Number of materials " << scene->mNumMaterials << std::endl;

	//------------For complex models--------------------
	pMesh(scene->mRootNode, scene);

	//pushMesh(scene);

}

void Model::pushMesh(const aiScene* scene)
{
	for (GLuint i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		meshes.push_back(getMesh(mesh, scene));

		// For Debugging
		//std::cout << "Number of meshes "<< mesh->mNumVertices << std::endl;
		/*if (mesh->HasTextureCoords(0) == true) {
			std::cout << "Mesh number " << i << " has texture coordinates" << std::endl;
		}*/
		/*if (mesh->HasVertexColors(0) == true) {
			std::cout << "Mesh number " << i << " has vertex color" << std::endl;
		}*/

	}

}

void Model::pMesh(aiNode* node, const aiScene* scene) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(getMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		pMesh(node->mChildren[i], scene);
	}
}

Mesh Model::getMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<vertex> verts;
	std::vector<unsigned int> indices;
	std::vector<material> lmaterials;
	std::vector<texture> ltextures;

	// Get mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		vertex vrtx;
		// Copy vertex position
		vrtx.vPos.x = mesh->mVertices[i].x;
		vrtx.vPos.y = mesh->mVertices[i].y;
		vrtx.vPos.z = mesh->mVertices[i].z;

		// Copy vertex normal
		if (mesh->HasNormals()) {
			vrtx.vNormal.x = mesh->mNormals[i].x;
			vrtx.vNormal.y = mesh->mNormals[i].y;
			vrtx.vNormal.z = mesh->mNormals[i].z;
		}
		else std::cout << "no normal";

		// Copy texture coordinates
		if (mesh->mTextureCoords[0]/*mesh->HasTextureCoords(0) == true*/) {
			vrtx.texPos.u = mesh->mTextureCoords[0][i].x;
			vrtx.texPos.v = mesh->mTextureCoords[0][i].y;
		}else {
			vrtx.texPos.u = 0.0f;
			vrtx.texPos.v = 0.0f;
		}

		verts.push_back(vrtx);
	}

	// Get mesh's indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {

		aiFace face = mesh->mFaces[i];

		for (unsigned int f = 0; f < face.mNumIndices; f++) {
			indices.push_back(face.mIndices[f]);
		}

	}

 
	// Get mesh's material
	if (mesh->mMaterialIndex >= 0) {
		aiString path;
		//aiTextureType_BASE_COLOR
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		//mat->GetTexture(aiTextureType_AMBIENT, 0, &path1);
		//std::cout << mat->GetTextureCount(aiTextureType_BASE_COLOR) << "--";

		material mesh_mat;
		aiColor3D vecColor;
		float shine;

		if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			for (GLuint i = 0; i < mat->GetTextureCount(aiTextureType_DIFFUSE); i++)
			{
				texture temp_tex;
				std::string tempS = dir + "/";
				Textures temp(tempS + path.C_Str());
				temp_tex.ID = temp.getTextureID();
				temp_tex.type = "texture_diffuse";
				ltextures.push_back(temp_tex);
			}
			mesh_mat.exists = 0;
		}
		else {
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, vecColor);
			mesh_mat.diffuse.x = vecColor.r;
			mesh_mat.diffuse.y = vecColor.g;
			mesh_mat.diffuse.z = vecColor.b;
			mesh_mat.exists = 1;
		} 

		mat->GetTexture(aiTextureType_SPECULAR, 0, &path);
		if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0) {
			for (GLuint i = 0; i < mat->GetTextureCount(aiTextureType_SPECULAR); i++) {
				texture temp_tex;
				std::string tempS = dir + "/";
				Textures temp(tempS + path.C_Str());
				temp_tex.ID = temp.getTextureID();
				temp_tex.type = "texture_specular";
				ltextures.push_back(temp_tex);
			}
		}

		mat->GetTexture(aiTextureType_AMBIENT, 0, &path);
		if (mat->GetTextureCount(aiTextureType_AMBIENT) > 0) {
			for (GLuint i = 0; i < mat->GetTextureCount(aiTextureType_AMBIENT); i++) {
				texture temp_tex;
				std::string tempS = dir + "/";
				Textures temp(tempS + path.C_Str());
				temp_tex.ID = temp.getTextureID();
				temp_tex.type = "texture_ambient";
				ltextures.push_back(temp_tex);
			}
		}

		mat->Get(AI_MATKEY_COLOR_AMBIENT, vecColor);
		mesh_mat.ambient.x = vecColor.r;
		mesh_mat.ambient.y = vecColor.g;
		mesh_mat.ambient.z = vecColor.b;

		mat->Get(AI_MATKEY_COLOR_SPECULAR, vecColor);
		mesh_mat.specular.x = vecColor.r;
		mesh_mat.specular.y = vecColor.g;
		mesh_mat.specular.z = vecColor.b;

		mat->Get(AI_MATKEY_SHININESS, shine);
		mesh_mat.shininess = shine;

		lmaterials.push_back(mesh_mat);
	}
	
	return Mesh(verts, indices,ltextures, lmaterials);
}
