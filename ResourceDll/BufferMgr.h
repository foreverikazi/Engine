#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "SystemConst.h"

class Buffer;
EXTERN class RESOURCE_DLL BufferMgr
{
	DECLARE_SINGLE(BufferMgr);
private :
	unordered_map<const TCHAR*, Buffer*> mBufferMap;

public:
	bool AddBuffer(ID3D11Device* pDevice, const BUFFERTYPE bufferType, const SHADERTYPE Shadertype, const TCHAR* key);
	bool LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* key, const TCHAR* fileName);
	void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
	void ReleaseBuffers();
	Buffer* FindBuffer(const TCHAR* key);
	BufferMgr();
	~BufferMgr();
};

