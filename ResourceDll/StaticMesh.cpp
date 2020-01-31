#include "pch.h"
#include "StaticMesh.h"


//StaticMesh::StaticMesh()
//{
//
//}
//
//StaticMesh::~StaticMesh()
//{
//
//}
//
//bool StaticMesh::AddMesh(const wstring pPath, const wstring pFileName)
//{
//	//Read Model
//	Assimp::Importer	importer;
//
//	return true;
//	auto flag = aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace;
//	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//	const aiScene*		pScene = importer.ReadFile(converter.to_bytes(pPath), flag);
//
//	if (!pScene) return NULL;
//
//	processNode(pScene->mRootNode, pScene);
//	//정보를 담을 공간
//	//Vertex					vertices;
//	//vector<unsigned long>	indices;
//	//SkinModel*				model = new SkinModel;
//
//	////모델 이름 정의
//	//wstring modelName = MYUTIL::getFileName(path);
//	//model->SetName(modelName);
//
//	////메쉬 정보 구성
//	//for (UINT i = 0; i < pScene->mNumMeshes; i++)
//	//	ProcessMesh(pScene->mMeshes[i], vertices, indices, model->GetMeshList());
//
//	////재질 정보 생성
//	//ProcessMaterial(pScene, model->GetMaterialList(), MYUTIL::GetDirectoryPath(path));
//
//	////계층구조(본) 정보 구성
//	//ProcessNode(pScene->mRootNode, model);
//	////순차적 tm 업데이트를 위해 깊이 값에 맞춰 정렬
//	//sort(model->GetNodeList().begin(), model->GetNodeList().end(),
//	//	[](const NodeInfo* a, const NodeInfo* b)->bool {	return a->depth < b->depth; });
//
//
//	////스키닝 정보
//	//for (UINT i = 0; i < pScene->mNumMeshes; i++) {
//	//	aiMesh* aiMesh = pScene->mMeshes[i];
//
//	//	if (!aiMesh->HasBones())
//	//		continue;
//
//	//	HierarchyMesh* mesh = (HierarchyMesh*)model->GetMeshList()[i];
//	//	ProcessSkin(aiMesh, mesh, vertices, indices, model);
//	//}
//
//	////애니메이션 정보 구성
//	//if (pScene->HasAnimations())
//	//	ProcessAnimation(pScene, model);
//
//	////정점 및 인덱스 정보 생성 실패시 생성한 모델 객체 삭제 후 반환
//	//if (!model->CreateModel(DEVICEMANAGER.GetDevice(), vertices, indices)) {
//	//	SAFE_RELEASE(model);
//	//	return NULL;
//	//}
//
//	////마테리얼 단위로 메쉬 정보 업데이트
//	//model->UpdateMeshByMaterial();
//}
//
//void StaticMesh::processNode(aiNode* node, const aiScene* scene)
//{
//	for (unsigned int i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
//		processMesh(mesh, scene);
//	}
//
//	for (unsigned int i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], scene);
//	}
//}
//
//void StaticMesh::processMesh(aiMesh* mesh, const aiScene* scene)
//{
//	std::vector<MeshVertex> vertices;
//	std::vector<int> indices;
//	vector<Texture> textures;
//
//	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//	{
//		MeshVertex meshVertex;
//		aiVector3D v = mesh->mVertices[i];
//		aiVector3D n = mesh->mNormals[i];
//
//		meshVertex.position = XMFLOAT3(v.x, v.y, v.z);
//		meshVertex.normal = XMFLOAT3(n.x, n.y, n.z);
//
//		if (mesh->mTextureCoords[0])
//		{
//			aiVector3D t = mesh->mTextureCoords[0][i];
//			meshVertex.uv = XMFLOAT2(t.x, t.y);
//			
//		}
//		else
//		{
//			meshVertex.uv = XMFLOAT2(0.f, 0.f);
//		}
//		vertices.emplace_back(meshVertex);
//	}
//
//	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//		for (unsigned int j = 0; j < face.mNumIndices; j++) 
//			indices.emplace_back(face.mIndices[j]);
//	}
//
//	aiMaterial * material = scene->mMaterials[mesh->mMaterialIndex];
//
//	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//	//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//	//// 2. specular maps
//	//vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//	//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//	//// 3. normal maps
//	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//	//// 4. height maps
//	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
//
//
//}
//
//vector<Texture> StaticMesh::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
//{
//	vector<Texture> textures;
//	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//	{
//		aiString str;
//		mat->GetTexture(type, i, &str);
//		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//		bool skip = false;
//		for (unsigned int j = 0; j < textures_loaded.size(); j++)
//		{
//			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
//			{
//				textures.push_back(textures_loaded[j]);
//				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//				break;
//			}
//		}
//		if (!skip)
//		{   // if texture hasn't been loaded already, load it
//			Texture texture;
//			texture.id = TextureFromFile(str.C_Str(), this->directory);
//			texture.type = typeName;
//			texture.path = str.C_Str();
//			textures.push_back(texture);
//			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
//		}
//	}
//	return textures;
//}
