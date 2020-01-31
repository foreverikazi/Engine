#include "pch.h"
#include "MeshMgr.h"
#include "StaticMesh.h"

MeshMgr::MeshMgr()
{

}

MeshMgr::~MeshMgr()
{

}

bool MeshMgr::AddMesh(MESHTYPE type, const wstring pMeshKey, const wstring pPath, const wstring pFileName)
{
	Mesh* pMesh = nullptr;

	if (type == MESHTYPE::MESHTYPE_STATIC)
	{
		pMesh = new StaticMesh();
	}

	//if (pMesh->AddMesh(pPath, pFileName) == false)
		//return false;

	//mMeshMap.insert(make_pair(pMeshKey, pMesh));

	return true;
}
