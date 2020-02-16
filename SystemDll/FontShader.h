#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

EXTERN class SYSTEM_DLL FontShader : public Shader
{
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename);
	virtual bool UpdateShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();
	bool SetColorShaderParameter(ID3D11DeviceContext* deviceContext, XMFLOAT4 color);

public:
	FontShader();
	virtual ~FontShader() = default;

private:
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer*		mColorBuffer;
};

