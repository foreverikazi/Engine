#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

class Shader;
EXTERN  class SYSTEM_DLL  ShaderMgr
{
	DECLARE_SINGLE(ShaderMgr);
public:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, SHADERBUFFERTYPE type);
	void ReleaseShader();
	bool SetShader(ID3D11DeviceContext* deviceContext, SHADERBUFFERTYPE type);
	void SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
	void SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower);
	void SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition);
	void SetCurrentShader(SHADERBUFFERTYPE type);
	
private:
	map<SHADERBUFFERTYPE, Shader*> mShaderMap;
};

