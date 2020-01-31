#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Mesh.h"

class Mesh;
EXTERN class RESOURCE_DLL MeshMgr
{
	DECLARE_SINGLE(MeshMgr);
private:
	unordered_map<wstring, Mesh*> mMeshMap;

public :
	MeshMgr();
	~MeshMgr();

	bool AddMesh(MESHTYPE type, const wstring meshKey, const wstring filePath, const wstring fileName);


};

