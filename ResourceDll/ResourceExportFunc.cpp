#include "pch.h"
#include "ResourceExportFunc.h"
#include "BufferMgr.h"
#include "Model.h"
#include "StringUtil.h"
#include "TextureUtil.h"

EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device, BUFFERTYPE type)
{
	return (*(BufferMgr::GetInst()))->AddBuffer(device, type);
}

EXTERN RESOURCE_DLL void RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	(*(BufferMgr::GetInst()))->RenderBuffers(deviceContext);
}

EXTERN RESOURCE_DLL void ReleaseBuffers(void)
{
	(*(BufferMgr::GetInst()))->ReleaseBuffers();
}

EXTERN RESOURCE_DLL int GetIndexCount()
{
	return (*(BufferMgr::GetInst()))->GetIndexCount();
}

// ¸ðµ¨ ÀÓ½Ã
EXTERN RESOURCE_DLL bool LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring pPath)
{
	return (*(Model::GetInst()))->LoadModel(device, deviceContext, pPath);
}

EXTERN RESOURCE_DLL void RenderModel(ID3D11DeviceContext* deviceContext)
{
	(*(Model::GetInst()))->RenderModel(deviceContext);
}

EXTERN RESOURCE_DLL void ReleaseModel()
{
	(*(Model::GetInst()))->ReleaseModel();
}

// Resource
EXTERN RESOURCE_DLL void ReleaseResource()
{
	(*(BufferMgr::GetInst()))->DestroyInst();
	(*(Model::GetInst()))->DestroyInst();
	(*(StringUtil::GetInst()))->DestroyInst();
	(*(TextureUtil::GetInst()))->DestroyInst();
}


