#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

EXTERN class SYSTEM_DLL ColorVertexShader : public Shader
{
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename);
	virtual bool UpdateShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();
public:
	ColorVertexShader();
	virtual ~ColorVertexShader() = default;
};

