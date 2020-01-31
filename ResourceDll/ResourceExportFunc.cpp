#include "pch.h"
#include "ResourceExportFunc.h"
#include "BufferMgr.h"
#include "Model.h"
#include "StringUtil.h"
#include "TextureUtil.h"

EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device)
{
	return (*(BufferMgr::GetInst()))->AddBuffer(device);
}

EXTERN RESOURCE_DLL void Buffer_Render(ID3D11DeviceContext* deviceContext)
{
	(*(BufferMgr::GetInst()))->Buffer_Render(deviceContext);
}

EXTERN RESOURCE_DLL void ReleaseBuffer(void)
{
	(*(BufferMgr::GetInst()))->ReleaseBuffer();
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

EXTERN RESOURCE_DLL void ModelRender(ID3D11DeviceContext* deviceContext)
{
	(*(Model::GetInst()))->Render(deviceContext);
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


