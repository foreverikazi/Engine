#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"

EXTERN class RESOURCE_DLL FontBuffer : public Buffer
{
private :
	struct FontInfo
	{
		float left, right;
		int size;
		
	};

public :
	virtual bool CreateBuffers(ID3D11Device* device);
	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual void UpdateSahder(ID3D11DeviceContext* deviceContext);
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext);
	virtual bool LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName);
	virtual void ReleaseBuffer();

	bool LoadFontData(const TCHAR* fileName);
	void SetText(ID3D11DeviceContext* deviceContext, const TCHAR* text, XMFLOAT2 position, const XMFLOAT4 color);
public:
	FontBuffer();
	virtual ~FontBuffer() = default;

private:
	ID3D11ShaderResourceView* mTexture;
	FontInfo* mFontInfo;
	XMFLOAT4 mColor;
	UINT mMaxLength;
	UINT mTextLength;
};

