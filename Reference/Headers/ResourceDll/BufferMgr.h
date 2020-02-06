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
		//, BUFFERTYPE Type
		//, const TCHAR* pBufferKey);
	/*HRESULT AddBuffer_Terrain(LPDIRECT3DDEVICE9 device
		, const TCHAR* pBufferKey
		, const DWORD& dwVtxCntX
		, const DWORD& dwVtxCntZ
		, const DWORD& dwVtxInterval);*/
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
		//const TCHAR* pBufferKey,
		//_D3DPRIMITIVETYPE iType = D3DPT_TRIANGLELIST);

	void ReleaseBuffers();
	//void Terrain_Release(const TCHAR* pBufferKey);
	BufferMgr();
	~BufferMgr();
};

