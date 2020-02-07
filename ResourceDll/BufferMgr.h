#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

class Buffer;
EXTERN class RESOURCE_DLL BufferMgr
{
	DECLARE_SINGLE(BufferMgr);
private :
	unordered_map<const TCHAR*, Buffer*> mBufferMap;

public:
	bool AddBuffer(ID3D11Device* pDevice, BUFFERTYPE type, const TCHAR* key);
	void LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* key, const TCHAR* fileName);
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
	void ReleaseBuffers();
	Buffer* FindBuffer(const TCHAR* key);
	BufferMgr();
	~BufferMgr();
};

