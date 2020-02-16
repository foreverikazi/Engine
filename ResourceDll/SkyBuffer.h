#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

class SkyBuffer : public Buffer
{
public:
	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual void UpdateSahder(ID3D11DeviceContext* deviceContext);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);
	virtual bool LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName);
	virtual void ReleaseBuffer();

public:
	SkyBuffer();
	virtual ~SkyBuffer() = default;

private :
	ID3D11ShaderResourceView* mTexture;
	UINT mLatLine;
	UINT mLongLine;
};

