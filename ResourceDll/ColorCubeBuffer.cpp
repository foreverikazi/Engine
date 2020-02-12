
#include "pch.h"
#include "ColorCubeBuffer.h"
#include "SystemExportFunc.h"
#include "Shader.h"

bool ColorCubeBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = 8;
	mIndexCount = 36;

	ColorVertex vertices[8];

	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[0].color = XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[3].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[4].color = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	vertices[5].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[5].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[6].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[6].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[7].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[7].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	DWORD indices[36] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 4, 5,
		0, 5, 1
	};

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ColorVertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &vertices;
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
	indexData.pSysMem = &indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer)))
	{
		return false;
	}

	return true;
}

void ColorCubeBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	
}

void ColorCubeBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, GetViewMatrix(), GetProjectionMatrix());
	}
}

void ColorCubeBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(ColorVertex);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(mIndexCount, 0, 0);
}
