#include "pch.h"
#include "ShaderMgr.h"
#include "Shader.h"
#include "ColorVertexShader.h"
#include "TextureShader.h"
#include "ModelShader.h"
#include "LightShader.h"

bool ShaderMgr::InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERTYPE type)
{
	auto shader = mShaderMap.find(type);
	if (shader != mShaderMap.end()) // 이미 생성된 데이터가 있음
	{
		return false;
	}
	Shader* newShader = nullptr;

	switch (type)
	{
	case SHADERTYPE::COLORVERTEX:
		newShader = new ColorVertexShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;

	case SHADERTYPE::MODEL :
		newShader = new ModelShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;

	case SHADERTYPE::TEXTURE :
		newShader = new TextureShader();
		newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
		mShaderMap.insert({ type, newShader });
		break;

	case SHADERTYPE::LIGHT :
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

Shader* ShaderMgr::GetShader(const SHADERTYPE type)
{
	auto shaderIter = mShaderMap.find(type);

	if (shaderIter->second != nullptr)
	{
		return shaderIter->second;
	}
	return nullptr;
}
