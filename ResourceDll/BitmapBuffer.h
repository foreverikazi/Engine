#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

EXTERN class RESOURCE_DLL BitmapBuffer : public Buffer
{
public:
	void SetTexturePosition(ID3D11DeviceContext* deviceContext,const XMFLOAT3 position, const XMFLOAT2 size);

	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual void UpdateSahder(ID3D11DeviceContext* deviceContext);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);
	virtual bool LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* fileName);
	virtual void ReleaseBuffer();

public:
	BitmapBuffer();
	virtual ~BitmapBuffer() = default;

private :
	ID3D11ShaderResourceView* mTexture;
	XMFLOAT2 mSize;

	int mScreenWidth;
	int mScreenHeight;
	int mBitmapWidth;
	int mBitmapHeight;
	int mPreviousPosX;
	int mPreviousPosY;
};

