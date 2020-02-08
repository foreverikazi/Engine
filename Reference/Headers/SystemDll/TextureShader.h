#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

EXTERN class SYSTEM_DLL TextureShader : public Shader
{
public :
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename);
	virtual bool SetShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();

public :
	TextureShader();
	virtual ~TextureShader() = default;

private :
	ID3D11SamplerState* mSampleState;
};

