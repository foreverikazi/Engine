#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

EXTERN class RESOURCE_DLL Mesh
{
public:
	vector <Vertex> mVertices;
	vector<unsigned int> mIndices;
	vector<Texture> mTextures;

public :
	ID3D11Buffer* mVertexBuffer;
	ID3D11Buffer* mNormalBuffer;
	ID3D11Buffer* mUVBuffer;
	ID3D11Buffer* mIndexBuffer;

	ID3D11ShaderResourceView* mDiffuseSRV;
	ID3D11ShaderResourceView* mSpecSRV;

public:
	void InitializeMesh(ID3D11Device* device, vector <Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& texture);
	void SetupMesh(ID3D11Device* device);
	void DrawMesh(ID3D11DeviceContext* deviceContext);
	void ReleaseMesh();

	/*const D3DXVECTOR3* GetMax(void) {
		return &m_vMax;
	}
	const D3DXVECTOR3* GetMin(void) {
		return &m_vMin;
	}

	D3DXMATRIX GetWorld() { return m_WeaponWorld; }*/

public:
	//virtual void CloneMesh(LPDIRECT3DDEVICE9 pDevice, CAnimationCtrl** ppAniCtrl) {}
	//virtual void InvalidateMesh(D3DXMATRIX* pMatWorld, float fAngle) {}

public:
	//virtual bool AddMesh(const wstring pPath, const wstring pFileName) = 0;
	/*
	virtual void Render(LPDIRECT3DDEVICE9 pDevice, BONE* pBone = NULL)PURE;
	virtual void Release(void) {}*/

public :
	Mesh();
	virtual ~Mesh();

};

