#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

EXTERN class RESOURCE_DLL CubeBuffer : public Buffer
{
public:
	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

public:
	CubeBuffer() = default;
	virtual ~CubeBuffer() = default;
};