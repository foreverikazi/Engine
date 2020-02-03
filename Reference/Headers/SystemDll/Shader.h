#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"


EXTERN class SYSTEM_DLL Shader
{
protected :
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	virtual bool SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
	virtual bool SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower);
	virtual bool SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition);
	virtual bool SetShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();

protected:
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);

public:
	Shader();
	virtual ~Shader();

protected:
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader*	mPixelShader;
	ID3D11InputLayout*	mLayout;
	ID3D11Buffer*		mMatrixBuffer;
	SHADERBUFFERTYPE	mShaderBufferType;
};
