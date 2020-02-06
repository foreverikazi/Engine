#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

EXTERN class RESOURCE_DLL GridBuffer : public Buffer
{
public:
	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);

private :
	float mRadius;
	float mInterval;

public:
	GridBuffer();
	virtual ~GridBuffer() = default;
};

