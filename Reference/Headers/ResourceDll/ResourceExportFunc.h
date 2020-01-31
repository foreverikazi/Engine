#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device);
EXTERN RESOURCE_DLL void Buffer_Render(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void ReleaseBuffer();
EXTERN RESOURCE_DLL int GetIndexCount();
// Model
EXTERN RESOURCE_DLL bool LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring pPath);
EXTERN RESOURCE_DLL void ModelRender(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void ReleaseModel();

// Resource
EXTERN RESOURCE_DLL void ReleaseResource();

