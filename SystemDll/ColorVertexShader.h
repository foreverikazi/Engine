#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "Shader.h"

EXTERN class SYSTEM_DLL ColorVertexShader : public Shader
{
public:
	virtual bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename);
	virtual bool SetShader(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseShader();
public:
	ColorVertexShader();
	virtual ~ColorVertexShader() = default;
};
