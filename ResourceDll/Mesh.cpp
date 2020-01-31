#include "pch.h"
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

Mesh::Mesh() 
	: mVertexBuffer(nullptr),
	mNormalBuffer(nullptr),
	mUVBuffer(nullptr),
	mIndexBuffer(nullptr),
	mDiffuseSRV(nullptr),
	mSpecSRV(nullptr)
{

}

Mesh::~Mesh()
{

}

void Mesh::InitializeMesh(ID3D11Device* device, vector <Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& texture)
{
	mVertices = vertices;
	mIndices = indices;
	mTextures = texture;
	SetupMesh(device);
}

void Mesh::SetupMesh(ID3D11Device* device)
{
	// 다이나믹 분기 필요
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.ByteWidth = (UINT)(sizeof(Vertex) * mVertices.size());
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &mVertices[0];
	device->CreateBuffer(&vbd, &vinitData, &mVertexBuffer);


	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * (UINT)mIndices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &mIndices[0];
	device->CreateBuffer(&ibd, &iinitData, &mIndexBuffer);
}

void Mesh::DrawMesh(ID3D11DeviceContext* deviceContext)
{
	UINT offset = 0;

	for (auto texture : mTextures)
	{
		if (texture.type == L"texture_diffuse")
		{
			deviceContext->PSSetShaderResources(0, 1, &texture.textureRV);
		}
	}

	UINT stride = sizeof(Vertex);
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->DrawIndexed((UINT)mIndices.size(), 0, 0);
}

void Mesh::ReleaseMesh()
{
	if (mVertexBuffer)
	{
		mVertexBuffer->Release();
		mVertexBuffer = 0;
	}

	if (mNormalBuffer)
	{
		mNormalBuffer->Release();
		mNormalBuffer = 0;
	}

	if (mUVBuffer)
	{
		mUVBuffer->Release();
		mUVBuffer = 0;
	}

	if(mIndexBuffer)
	{
		mIndexBuffer->Release();
		mIndexBuffer = 0;
	}

	if (mDiffuseSRV)
	{
		mDiffuseSRV->Release();
		mDiffuseSRV = 0;
	}

	if (mSpecSRV)
	{
		mDiffuseSRV->Release();
		mDiffuseSRV = 0;
	}
}
