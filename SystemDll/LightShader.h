#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

EXTERN class SYSTEM_DLL LightShader : public Shader
{
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	virtual bool SetShader(ID3D11DeviceContext* deviceContext);
	virtual bool SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower);
	virtual void ReleaseShader();

public:
	LightShader();
	virtual ~LightShader() = default;

private :
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer*		mLightBuffer;

};

