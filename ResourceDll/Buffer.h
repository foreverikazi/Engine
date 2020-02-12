#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

class Shader;
EXTERN class RESOURCE_DLL Buffer
{
public:
	int GetIndexCount() { return mIndexCount; }

	virtual bool CreateBuffers(ID3D11Device* device) = 0;
	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual void UpdateSahder(ID3D11DeviceContext* deviceContext) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext) = 0;
	virtual bool LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* fileName) { return false; }
	virtual void ReleaseBuffer();

	void SetShader(Shader* shader);
	void SetPosition(XMFLOAT3 position);
	void SetScale(XMFLOAT3 scale);
	void SetRotation(XMFLOAT3 rotation);
	
	XMFLOAT3 GetPosition() const;
	XMFLOAT3 GetScale() const;
	XMFLOAT3 GetRotation() const;
	XMMATRIX GetWorldMatrix() const;

public:
	Buffer();
	virtual ~Buffer();

protected:
	WorldInfo		mWorldInfo;
	Shader*			mShader;
	ID3D11Buffer*	mVertexBuffer;
	UINT			mVertexCount;
	ID3D11Buffer*	mIndexBuffer;
	UINT			mIndexCount;
};

