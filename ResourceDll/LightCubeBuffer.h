#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

class LightCubeBuffer : public Buffer
{
public:
	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);
	virtual void LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* fileName);

public:
	LightCubeBuffer() = default;
	virtual ~LightCubeBuffer() = default;

private:
	ID3D11ShaderResourceView* mTexture;
};

