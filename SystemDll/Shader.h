#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

enum Shader_Type
{
	Triangle,
	Mesh,
};

EXTERN class SYSTEM_DLL Shader
{
	DECLARE_SINGLE(Shader);
private:
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
		//float specularPower;
		//XMFLOAT4 specularColor;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

public:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	bool Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
	bool SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
	bool SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower);
	bool SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition);

	bool Render2(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
	void ReleaseShader();

private:
	void OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename);
	void RenderShader(ID3D11DeviceContext* deviceContext, int indexCount);

public:
	Shader();
	~Shader();

private:
	ID3D11VertexShader* mVertexShader;
	ID3D11PixelShader*	mPixelShader;
	ID3D11InputLayout*	mLayout;
	ID3D11SamplerState* mSampleState;
	ID3D11Buffer*		mMatrixBuffer;
	ID3D11Buffer*		mLightBuffer;
	ID3D11Buffer*		mCameraBuffer;
};
