#include "pch.h"
#include "BitmapBuffer.h"
#include "SystemExportFunc.h"
#include "Shader.h"

BitmapBuffer::BitmapBuffer() :
	mTexture(nullptr),
	mScreenWidth(0),
	mScreenHeight(0),
	mBitmapWidth(0),
	mBitmapHeight(0),
	mPreviousPosX(0),
	mPreviousPosY(0)
{

}

void BitmapBuffer::SetTexturePosition(ID3D11DeviceContext* deviceContext, const XMFLOAT3 position, const XMFLOAT2 size)
{
	TextureVertex vertices[6];
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	mWorldInfo.position = position;

	vertices[0].position = XMFLOAT3(position.x, position.y + size.y, 0.0f);  // Top left.
	vertices[0].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
	vertices[1].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[2].position = XMFLOAT3(position.x, position.y, 0.0f);
	vertices[2].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(position.x, position.y + size.y, 0.0f);  // Top left.
	vertices[3].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[4].position = XMFLOAT3(position.x + size.x, position.y + size.y, 0.0f);  // Top right.
	vertices[4].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(position.x + size.x, position.y, 0.0f);
	vertices[5].uv = XMFLOAT2(1.0f, 1.0f);

	deviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	TextureVertex* verticesPtr = (TextureVertex*)mappedResource.pData;
	memcpy(verticesPtr, (void*)vertices, (sizeof(TextureVertex) * mVertexCount));
	deviceContext->Unmap(mVertexBuffer, 0);
}

bool BitmapBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = 6;
	mIndexCount = 6;
	TextureVertex vertices[6];
	DWORD indices[6] =
	{
		0, 1, 2,
		3, 4, 5
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer)))
	{
		return false;
	}

	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer)))
	{
		return false;
	}

	return true;
}

void BitmapBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	Buffer::UpdateBuffers(deviceContext);
}

void BitmapBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, GetViewMatrix(), GetOrthoMatrix());
	}
}

void BitmapBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(TextureVertex);
	unsigned int offset = 0;

	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(mIndexCount, 0, 0);
}

bool BitmapBuffer::LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName)
{
	HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, fileName, 0, 0, &mTexture, 0);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void BitmapBuffer::ReleaseBuffer()
{
	SAFE_RELEASE(mTexture);

	Buffer::ReleaseBuffer();
}

