#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

class Shader;
EXTERN  class SYSTEM_DLL  ShaderMgr
{
	DECLARE_SINGLE(ShaderMgr);
public:
	bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERTYPE type);
	void ReleaseShader();
	Shader* GetShader(const SHADERTYPE type);

private:
	map<SHADERTYPE, Shader*> mShaderMap;
};

