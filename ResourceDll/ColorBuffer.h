#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"
#include "Buffer.h"


EXTERN class RESOURCE_DLL ColorBuffer : public Buffer
{
public:
	virtual int GetIndexCount() { return mIndexCount; }
	bool CreateBuffers(ID3D11Device* device, Vertex& vertices, vector<unsigned long>& indices, D3D11_PRIMITIVE_TOPOLOGY type);

public:
	virtual void Render(ID3D11DeviceContext* deviceContext);
	virtual void Shutdown(void);

private:
};

