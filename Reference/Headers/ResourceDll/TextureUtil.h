#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL TextureUtil
{
	DECLARE_SINGLE(TextureUtil);

private :
	ID3D11ShaderResourceView* mDiffuseRV;
	ID3D11Texture2D* mTexture;

public :
	ID3D11ShaderResourceView* LoadTextureUtil(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring fileName);
public :
	TextureUtil();
	~TextureUtil();
};

