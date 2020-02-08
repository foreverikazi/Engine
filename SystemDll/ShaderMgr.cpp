#include "pch.h"
#include "ShaderMgr.h"
#include "Shader.h"
#include "ColorVertexShader.h"
#include "TextureShader.h"
#include "ModelShader.h"
#include "LightShader.h"

bool ShaderMgr::InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERBUFFERTYPE type)
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

	case SHADERBUFFERTYPE::LIGHT :
		newShader = new LightShader();
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

bool ShaderMgr::SetShader(ID3D11DeviceContext* deviceContext, const SHADERBUFFERTYPE type)
{
	auto shaderIter = mShaderMap.find(type);

	if (shaderIter != mShaderMap.end())
	{
		shaderIter->second->SetShader(deviceContext);
	}

	return true;
}

void ShaderMgr::SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, const XMMATRIX worldMat, const XMMATRIX viewMat, const XMMATRIX projMat)
{
	// 나중에 바꾸자
	for(auto shader : mShaderMap)
	{
		shader.second->SetMatrixShaderParameters(deviceContext, worldMat, viewMat, projMat);
	}
}

void ShaderMgr::SetLightShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT4 ambientColor, const XMFLOAT4 diffuseColor, const XMFLOAT3 lightDirection, const  XMFLOAT4 specularColor, const float specularPower)
{
	// 나중에 바꾸자
	for (auto shader : mShaderMap)
	{
		shader.second->SetLightShaderParameters(deviceContext, ambientColor, diffuseColor, lightDirection, specularColor, specularPower);
	}
}

void ShaderMgr::SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, const XMFLOAT3 cameraPosition)
{
	// 나중에 바꾸자
	for (auto shader : mShaderMap)
	{
		shader.second->SetCameraShaderParameters(deviceContext, cameraPosition);
	}
}
