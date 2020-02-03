#include "pch.h"
#include "Model.h"
#include "Mesh.h"
#include "TextureUtil.h"
#include <string>
#include <StringUtil.h>

bool Model::LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext,const wstring pPath)
{
	//Read Model
	Assimp::Importer	importer;

	auto flag = aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes |
		aiProcess_FlipUVs | aiProcess_FlipWindingOrder | aiProcess_MakeLeftHanded;// | aiProcess_JoinIdenticalVertices;
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	const aiScene*		pScene = importer.ReadFile(converter.to_bytes(pPath), flag);

	if (!pScene) return false;

	mDevice = device;
	mDeviceContext = deviceContext;

	wstring directoryPath = (*(StringUtil::GetInst()))->GetDirectoryPath(pPath.c_str()).GetString();

	processNode(pScene->mRootNode, pScene, directoryPath);
	return true;

	//정보를 담을 공간
	//Vertex					vertices;
	//vector<unsigned long>	indices;
	//SkinModel*				model = new SkinModel;

	////모델 이름 정의
	//wstring modelName = MYUTIL::getFileName(path);
	//model->SetName(modelName);

	////메쉬 정보 구성
	//for (UINT i = 0; i < pScene->mNumMeshes; i++)
	//	ProcessMesh(pScene->mMeshes[i], vertices, indices, model->GetMeshList());

	////재질 정보 생성
	//ProcessMaterial(pScene, model->GetMaterialList(), MYUTIL::GetDirectoryPath(path));

	////계층구조(본) 정보 구성
	//ProcessNode(pScene->mRootNode, model);
	////순차적 tm 업데이트를 위해 깊이 값에 맞춰 정렬
	//sort(model->GetNodeList().begin(), model->GetNodeList().end(),
	//	[](const NodeInfo* a, const NodeInfo* b)->bool {	return a->depth < b->depth; });


	////스키닝 정보
	//for (UINT i = 0; i < pScene->mNumMeshes; i++) {
	//	aiMesh* aiMesh = pScene->mMeshes[i];

	//	if (!aiMesh->HasBones())
	//		continue;

	//	HierarchyMesh* mesh = (HierarchyMesh*)model->GetMeshList()[i];
	//	ProcessSkin(aiMesh, mesh, vertices, indices, model);
	//}

	////애니메이션 정보 구성
	//if (pScene->HasAnimations())
	//	ProcessAnimation(pScene, model);

	////정점 및 인덱스 정보 생성 실패시 생성한 모델 객체 삭제 후 반환
	//if (!model->CreateModel(DEVICEMANAGER.GetDevice(), vertices, indices)) {
	//	SAFE_RELEASE(model);
	//	return NULL;
	//}

	////마테리얼 단위로 메쉬 정보 업데이트
	//model->UpdateMeshByMaterial();
}

void Model::processNode(aiNode* node, const aiScene* scene, wstring directoryPath)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene, directoryPath));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, directoryPath);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene, wstring directoryPath)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	vertices.reserve(mesh->mNumVertices);
	//indices.reserve(mesh->mNumFaces * 3);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		aiVector3D v = mesh->mVertices[i];
		aiVector3D n = mesh->mNormals[i];

		vertex.position = XMFLOAT3(v.x, v.y, v.z);

		if (mesh->mTextureCoords[0])
		{
			aiVector3D t = mesh->mTextureCoords[0][i];
			vertex.uv = XMFLOAT2(t.x, t.y);

		}
		else
		{
			vertex.uv = XMFLOAT2(0.f, 0.f);
		}

		if (mesh->mNormals)
		{
			vertex.normal = XMFLOAT3(n.x, n.y, n.z);
		}

		vertices.emplace_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.emplace_back(face.mIndices[j]);
	}
	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, L"texture_diffuse", directoryPath);
	//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	//// 2. specular maps
	//vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	//// 3. normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	//// 4. height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	Mesh newMesh;
	newMesh.InitializeMesh(mDevice, vertices, indices, diffuseMaps);
	newMesh.SetupMesh(mDevice);
	return newMesh;
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, wstring typeName, wstring directoryPath)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			const char* texturePath = CT2CA(textures_loaded[j].path.data());

			if (std::strcmp(texturePath, str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}

		if (!skip)
		{   
			Texture texture;
			texture.type = typeName;
			texture.path = CA2T(str.C_Str());
			wstring filePath = directoryPath + (*(StringUtil::GetInst()))->GetFileName(texture.path.c_str()).GetString();

			texture.textureRV = (*TextureUtil::GetInst())->LoadTextureUtil(mDevice, mDeviceContext, filePath);
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

void Model::RenderModel(ID3D11DeviceContext* deviceContext)
{
	if (meshes.empty()) 	
		return;

	UINT offset = 0;

	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	for (auto mesh : meshes)
	{
		mesh.DrawMesh(deviceContext);
	}
	//for (int i = 0; i < meshes.size(); i++)
	//{
	//	//Update Constant buffer with WVP Matrix
	//	//this->cb_vs_vertexshader->data.wvpMatrix = meshes[i].GetTransformMatrix() * worldMatrix * viewProjectionMatrix; //Calculate World-View-Projection Matrix
	//	//this->cb_vs_vertexshader->data.worldMatrix = meshes[i].GetTransformMatrix() * worldMatrix; //Calculate World
	//	//this->cb_vs_vertexshader->ApplyChanges();
	//	meshes[i].Draw(deviceContext);
	//}

	//UpdateModelMatrix();

	////Node Update
	//UpdateNodeTM();

	//for (UINT i = 0; i < _meshByMaterial.size(); i++) {
	//	if (_meshByMaterial[i].empty())
	//		continue;

	//	//마테리얼 셋팅
	//	auto texData = _materialList[i].diffuseMap;

	//	if (texData)
	//		dc->PSSetShaderResources(0, 1, &texData->data);

	//	//Mesh Render
	//	for (auto mesh : _meshByMaterial[i]) {

	//		//본 정보 셋팅
	//		if (!mesh->boneList.empty()) {
	//			SetShader(_skinShader, false);
	//			vector<XMMATRIX> calcBoneList;
	//			for (auto boneInfo : mesh->boneList)
	//				calcBoneList.emplace_back(XMMatrixTranspose(boneInfo.matOffset * boneInfo.linkNode->worldTM));

	//			RM_SHADER.SetShaderParameters(dc, calcBoneList);
	//		}
	//		//본 정보가 없는 경우
	//		else {
	//			SetShader(_texShader, false);

	//			if (mesh->linkNode)
	//				_tmModel = mesh->linkNode->worldTM * _tmModel;
	//		}
	//		RM_SHADER.SetShaderParameters(dc, _tmModel);

	//		//렌더
	//		GetShader()->IndexRender(dc, mesh->count, mesh->start);
	//	}
	//}

	////Unbind Texture
	//ID3D11ShaderResourceView* nullViews[] = { nullptr };
	//dc->PSSetShaderResources(0, 1, nullViews);
}

void Model::ReleaseModel()
{
	for (auto mesh : meshes)
	{
		mesh.ReleaseMesh();
	}
}

