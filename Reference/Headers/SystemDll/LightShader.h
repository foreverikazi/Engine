#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

class LightShader : public Shader
{
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename);
	virtual bool UpdateShader(ID3D11DeviceContext* deviceContext);
	virtual bool SetLightShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT4 ambientColor, const XMFLOAT4 diffuseColor, const XMFLOAT3 lightDirection, const XMFLOAT4 specularColor, const float specularPower);
	virtual bool SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT3 cameraPosition);
	virtual void ReleaseShader();

public:
	LightShader();
	virtual ~LightShader() = default;

private :
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer*		mLightBuffer;
	ID3D11Buffer*		mCameraBuffer;
};

