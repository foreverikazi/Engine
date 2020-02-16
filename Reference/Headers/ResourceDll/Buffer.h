#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

class Shader;
EXTERN class RESOURCE_DLL Buffer
{
public:
	virtual bool CreateBuffers(ID3D11Device* device) = 0;
	virtual void UpdateSahder(ID3D11DeviceContext* deviceContext) = 0;
	virtual void RenderBuffers(ID3D11DeviceContext* deviceContext) = 0;
	virtual void UpdateBuffers(ID3D11DeviceContext* deviceContext);
	virtual bool LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName) { return false; }
	virtual void ReleaseBuffer();

public :
	void SetShader(Shader* shader);
	void SetPosition(const XMFLOAT3 position);
	void SetScale(const XMFLOAT3 scale);
	void SetRotation(const XMFLOAT3 rotation);
	
	XMFLOAT3 GetPosition() const;
	XMFLOAT3 GetScale() const;
	XMFLOAT3 GetRotation() const;
	XMMATRIX GetWorldMatrix() const;
	int GetIndexCount() const;

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

