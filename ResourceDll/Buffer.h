#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL Buffer
{
public:
	int GetIndexCount() { return mIndexCount; }

	virtual bool CreateBuffers(ID3D11Device* device) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext) = 0;
	void ReleaseBuffer();

public:
	Buffer();
	virtual ~Buffer();

protected:
	ID3D11Buffer*	mVertexBuffer;
	UINT			mVertexCount;
	ID3D11Buffer*	mIndexBuffer;
	UINT			mIndexCount;


};

