#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

EXTERN class RESOURCE_DLL Model
{
	DECLARE_SINGLE(Model);

private :
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;

public :
	bool LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext,const wstring pPath);
	void processNode(aiNode* node, const aiScene* scene, wstring directoryPath);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene, wstring directoryPath);
	//bool createSRVFromAssimpMat(aiMaterial* mat, aiTextureType type, ID3D11ShaderResourceView** srv);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, wstring typeName, wstring directoryPath);
	void Render(ID3D11DeviceContext* deviceContext);
	void ReleaseModel();

public :

};

