#include "pch.h"
#include "ShaderMgr.h"
#include "Shader.h"
#include "ColorVertexShader.h"
#include "TextureShader.h"
#include "ModelShader.h"
#include "LightShader.h"
#include "SkyShader.h"
#include "FontShader.h"

bool ShaderMgr::InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERTYPE type)
{
	auto shader = mShaderMap.find(type);
	if (shader != mShaderMap.end()) // 이미 생성된 데이터가 있음
	{
		return false;
	}
	Shader* newShader = nullptr;

	// 나중에 object 클래스 만들면 팩토리로 코드 바꿀것
	switch (type)
	{
	case SHADERTYPE::COLORVERTEX:
		newShader = new ColorVertexShader();
		break;

	case SHADERTYPE::MODEL :
		newShader = new ModelShader();
		break;

	case SHADERTYPE::TEXTURE :
		newShader = new TextureShader();
		break;

	case SHADERTYPE::LIGHT :
		newShader = new LightShader();
		break;

	case SHADERTYPE::SKY :
		newShader = new SkyShader();
		break;

	case SHADERTYPE::FONT :
		newShader = new FontShader();
		break;

	default :
		return false;
	}

	newShader->InitializeShader(device, hwnd, vsFilename, psFilename);
	mShaderMap.insert({ type, newShader });

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

	if (shaderIter != mShaderMap.end())
	{
		return shaderIter->second;
	}
	return nullptr;
}
