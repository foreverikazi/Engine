#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

class Shader;
EXTERN  class SYSTEM_DLL  ShaderMgr
{
	DECLARE_SINGLE(ShaderMgr);
public:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERBUFFERTYPE type);
	void ReleaseShader();
	bool SetShader(ID3D11DeviceContext* deviceContext, const SHADERBUFFERTYPE type);
	void SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX worldMat, const XMMATRIX viewMat, const XMMATRIX projMat);
	void SetLightShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT4 ambientColor, const XMFLOAT4 diffuseColor, const XMFLOAT3 lightDirection, const XMFLOAT4 specularColor, const  float specularPower);
	void SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT3 cameraPosition);
	void SetCurrentShader(const SHADERBUFFERTYPE type);
	
private:
	map<SHADERBUFFERTYPE, Shader*> mShaderMap;
};

