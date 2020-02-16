#include "pch.h"
#include "ResourceExportFunc.h"
#include "BufferMgr.h"
#include "Model.h"
#include "StringUtil.h"
#include "TextureUtil.h"
#include "Buffer.h"
#include "TextMgr.h"

EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device, const BUFFERTYPE bufferType, const SHADERTYPE shaderType, const TCHAR* key)
{
	return (*(BufferMgr::GetInst()))->AddBuffer(device, bufferType, shaderType, key);
}

EXTERN RESOURCE_DLL void UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	(*(BufferMgr::GetInst()))->UpdateBuffers(deviceContext);
}

EXTERN RESOURCE_DLL void RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	(*(BufferMgr::GetInst()))->RenderBuffers(deviceContext);
}

EXTERN RESOURCE_DLL bool LoadTextureBuffer(ID3D11Device* device, const TCHAR* key, const TCHAR* fileName)
{
	return (*(BufferMgr::GetInst()))->LoadTextureBuffer(device, key, fileName);
}

EXTERN RESOURCE_DLL Buffer* FindBuffer(const TCHAR* key)
{
	return (*(BufferMgr::GetInst()))->FindBuffer(key);
}

EXTERN RESOURCE_DLL void ReleaseBuffers(void)
{
	(*(BufferMgr::GetInst()))->ReleaseBuffers();
}

// Text
EXTERN RESOURCE_DLL bool AddFontBuffer(ID3D11Device* device, const TCHAR* fontFileName, const TCHAR* textureFileName)
{
	return (*(TextMgr::GetInst()))->AddFontBuffer(device, fontFileName, textureFileName);
}

EXTERN RESOURCE_DLL void SetText(ID3D11DeviceContext* deviceContext, const TCHAR* text, XMFLOAT2 position, const XMFLOAT4 color)
{
	(*(TextMgr::GetInst()))->SetText(deviceContext, text, position, color);
}

EXTERN RESOURCE_DLL void SetFPSText(ID3D11DeviceContext* deviceContext, int fps, XMFLOAT2 position)
{
	(*(TextMgr::GetInst()))->SetFPSText(deviceContext, fps, position);
}

EXTERN RESOURCE_DLL void RenderText(ID3D11DeviceContext* deviceContext)
{
	(*(TextMgr::GetInst()))->RenderText(deviceContext);
}

EXTERN RESOURCE_DLL void ReleaseText()
{
	(*(TextMgr::GetInst()))->ReleaseText();
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
	(*(TextMgr::GetInst()))->DestroyInst();
}


