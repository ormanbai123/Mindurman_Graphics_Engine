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
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_LINE);
	const aiScene* scene = importer.ReadFile(model_path, aiProcess_JoinIdenticalVertices | 
		                                                 aiProcess_Triangulate |
		                                                 aiProcess_SortByPType | 
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
		/*aiFace* face1;
		std::cout<<face1->mNumIndices << "--";*/

		aiFace face = mesh->mFaces[i];
		//std::cout << face.mNumIndices << "--";

		for (unsigned int f = 0; f < face.mNumIndices; f++) {
			indices.push_back(face.mIndices[f]);
		}

	}

 
	// Get mesh's material
	if (mesh->mMaterialIndex >= 0) {
		//std::string str;
		aiString path;
		//aiTextureType_BASE_COLOR
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
		//mat->GetTexture(aiTextureType_AMBIENT, 0, &path1);
		//std::cout << path.C_Str() << " " /*<< path1.C_Str()*/ << std::endl;
		

		/*std::cout<< mat->GetTextureCount(aiTextureType_DIFFUSE) << "--";*/
		//std::cout << mat->GetTextureCount(aiTextureType_AMBIENT) << "-";
		//std::cout << mat->GetTextureCount(aiTextureType_SPECULAR) << std::endl;
		//std::cout << path.C_Str() << "---";

		/*mat->GetTexture(aiTextureType_AMBIENT, 0, &path1);
		std::cout << path1.C_Str() << std::endl;*/
		/*mat->GetTexture(aiTextureType_SPECULAR, 0, &path1);
		std::cout << path1.C_Str() << "--";*/

		//std::cout << mat->GetTextureCount(aiTextureType_BASE_COLOR) << "--";

		// NEW NEW NEW ----------Added for loop
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
		}
		else {
			material mesh_mat;
			aiColor3D vecColor;
			mat->Get(AI_MATKEY_COLOR_DIFFUSE, vecColor);
			mesh_mat.diffuse.x = vecColor.r;
			mesh_mat.diffuse.y = vecColor.g;
			mesh_mat.diffuse.z = vecColor.b;
			lmaterials.push_back(mesh_mat);
		}
	}
	
	return Mesh(verts, indices,ltextures, lmaterials);
}
