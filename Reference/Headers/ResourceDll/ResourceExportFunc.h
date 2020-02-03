#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

// Buffer
EXTERN RESOURCE_DLL bool AddBuffer(ID3D11Device* device, BUFFERTYPE type);
EXTERN RESOURCE_DLL void RenderBuffers(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void ReleaseBuffers();
EXTERN RESOURCE_DLL int GetIndexCount();
// Model
EXTERN RESOURCE_DLL bool LoadModel(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wstring pPath);
EXTERN RESOURCE_DLL void RenderModel(ID3D11DeviceContext* deviceContext);
EXTERN RESOURCE_DLL void ReleaseModel();

// Resource
EXTERN RESOURCE_DLL void ReleaseResource();

