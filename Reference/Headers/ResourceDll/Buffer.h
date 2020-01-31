#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL Buffer
{
protected:
	ID3D11Buffer*	mVertexBuffer;
	int				mVertexCount;

protected:
	ID3D11Buffer*	mIndexBuffer;
	int				mIndexCount;

public:
	//void PasteIdx(INDEX* pVtx, const int& iTriCnt);
	//void CopyVtx(VTXTEX* pVtx);
	//void PasteVtx(VTXTEX* pVtx);
	virtual int GetIndexCount() { return mIndexCount; }

public:
    virtual bool CreateBuffers(ID3D11Device* device);
	/*virtual HRESULT CreateVertexIndexBuffer(LPDIRECT3DDEVICE9 pDevice
		, const DWORD& dwVtxCntX = 0
		, const DWORD& dwVtxCntZ = 0
		, const DWORD& dwVtxInterval = 0);

	HRESULT CBuffer::CreateVertexBuffer(LPDIRECT3DDEVICE9 pDevice
		, const DWORD& dwVtxCntX = 0
		, const DWORD& dwVtxCntZ = 0
		, const DWORD& dwVtxInterval = 0);*/

public:
	virtual void Render(ID3D11DeviceContext* deviceContext);
	virtual void ReleaseBuffer(void);
public:
	Buffer();
	virtual ~Buffer();

};

