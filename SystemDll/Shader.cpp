#include "pch.h"
#include "Shader.h"

Shader::Shader() :
	mVertexShader(nullptr),
	mPixelShader(nullptr),
	mMatrixBuffer(nullptr),
	mLayout(nullptr)
{
}

Shader::~Shader()
{
}

void Shader::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, const TCHAR* shaderFilename)
{
	// ���� �޽����� ���â�� ǥ���մϴ�.
	OutputDebugStringA(reinterpret_cast<const char*>(errorMessage->GetBufferPointer()));

	// ���� �޼����� ��ȯ�մϴ�.
	errorMessage->Release();
	errorMessage = 0;

	// ������ ������ ������ �˾� �޼����� �˷��ݴϴ�.
	MessageBox(hwnd, L"Error compiling shader.", shaderFilename, MB_OK);
}

bool Shader::SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat)
{
	if (mMatrixBuffer == nullptr)
	{
		return false;
	}

	worldMat = XMMatrixTranspose(worldMat);
	viewMat = XMMatrixTranspose(viewMat);
	projMat = XMMatrixTranspose(projMat);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	if (FAILED(deviceContext->Map(mMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return false;
	}

	MatrixBufferType* dataPtr = (MatrixBufferType*)mappedResource.pData;

	dataPtr->world = worldMat;
	dataPtr->view = viewMat;
	dataPtr->projection = projMat;

	deviceContext->Unmap(mMatrixBuffer, 0);

	unsigned bufferNumber = 0;
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &mMatrixBuffer);

	return true;
}
bool Shader::SetLightShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT4 ambientColor, const XMFLOAT4 diffuseColor, const XMFLOAT3 lightDirection, const XMFLOAT4 specularColor, const float specularPower)
{
	return true;
}

bool Shader::SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT3 cameraPosition)
{
	return true;
}

bool Shader::UpdateShader(ID3D11DeviceContext* deviceContext)
{
	return true;
}

void Shader::ReleaseShader()
{
	if (mLayout)
	{
		mLayout->Release();
		mLayout = 0;
	}
	
	if (mPixelShader)
	{
		mPixelShader->Release();
		mPixelShader = 0;
	}
	
	if (mVertexShader)
	{
		mVertexShader->Release();
		mVertexShader = 0;
	}
}