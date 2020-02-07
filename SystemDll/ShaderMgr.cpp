#include "pch.h"
#include "ShaderMgr.h"
#include "Shader.h"
#include "ColorVertexShader.h"
#include "TextureShader.h"
#include "ModelShader.h"

bool ShaderMgr::InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, SHADERBUFFERTYPE type)
{
	auto shader = mShaderMap.find(type);
	if (shader != mShaderMap.end()) // 이미 생성된 데이터가 있음
	{
		return false;
	}
	Shader* newShader = nullptr;

	switch (type)
	{
	case SHADERBUFFERTYPE::COLORVERTEX:
		newShader = new ColorVertexShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;

	case SHADERBUFFERTYPE::MODEL :
		newShader = new ModelShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;

	case SHADERBUFFERTYPE::TEXTURE :
		newShader = new TextureShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;
	}

	//SetCurrentShader(type);
	return true;
}

void ShaderMgr::ReleaseShader()
{
	for (auto iter = mShaderMap.begin(); iter != mShaderMap.end(); iter++)
	{
		if (iter->second != nullptr)
		{
			iter->second->ReleaseShader();
			delete iter->second;
			iter->second = nullptr;
		}
	}

	mShaderMap.clear();
}

bool ShaderMgr::SetShader(ID3D11DeviceContext* deviceContext, SHADERBUFFERTYPE type)
{
	auto shaderIter = mShaderMap.find(type);
	Shader* shader = shaderIter->second;

	if (shader)
	{
		shader->SetShader(deviceContext);
	}

	return true;
}

void ShaderMgr::SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat)
{
	for(auto shader : mShaderMap)
	{
		shader.second->SetMatrixShaderParameters(deviceContext, worldMat, viewMat, projMat);
	}
}

void ShaderMgr::SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower)
{
	if (mCurrentShader)
	{
		mCurrentShader->SetLightShaderParameters(deviceContext, ambientColor, diffuseColor, lightDirection, specularColor, specularPower);
	}
}

void ShaderMgr::SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition)
{
	if (mCurrentShader)
	{
		mCurrentShader->SetCameraShaderParameters(deviceContext, cameraPosition);
	}
}

void ShaderMgr::SetCurrentShader(SHADERBUFFERTYPE type)
{
	auto shader = mShaderMap.find(type);
	mCurrentShader = shader->second;
}
