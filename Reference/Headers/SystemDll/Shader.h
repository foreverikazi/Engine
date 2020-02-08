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

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT3 lightDirection;
		float specularPower;
		XMFLOAT4 specularColor;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename) = 0;
	virtual bool SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX worldMat, const XMMATRIX viewMat, const XMMATRIX projMat);
	virtual bool SetLightShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT4 ambientColor, const XMFLOAT4 diffuseColor, const XMFLOAT3 lightDirection, const XMFLOAT4 specularColor, const float specularPower);
	virtual bool SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT3 cameraPosition);
	virtual bool SetShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();

protected:
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const TCHAR* shaderFilename);

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
