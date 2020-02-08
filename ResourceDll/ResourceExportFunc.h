#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "SystemConst.h"
class Buffer;

// Buffer
EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device, const BUFFERTYPE bufferType, const SHADERTYPE shaderType, const TCHAR* key);
EXTERN RESOURCE_DLL void UpdateBuffers(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void RenderBuffers(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* key, const TCHAR* fileName);
EXTERN RESOURCE_DLL Buffer* FindBuffer(const TCHAR* key);
EXTERN RESOURCE_DLL void ReleaseBuffers();

// Model
EXTERN RESOURCE_DLL bool LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring pPath);
EXTERN RESOURCE_DLL void RenderModel(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void ReleaseModel();

// Resource
EXTERN RESOURCE_DLL void ReleaseResource();

