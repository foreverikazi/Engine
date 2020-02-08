#include "pch.h"
#include "GridBuffer.h"
#include "SystemExportFunc.h"
#include "Shader.h"

GridBuffer::GridBuffer() :
	mRadius(10),
	mInterval(5)
{
	
}

bool GridBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = 60;
	ColorVertex vertices[60];
	float gridPoint = 15;
	XMFLOAT4 color = XMFLOAT4(0, 0, 0, 0);

	int halfIndex = UINT(gridPoint / 2);
	float startPoint = halfIndex * -mInterval;

	for (UINT i = 0; i < gridPoint; i++)
	{
		vertices[4 * i].position = XMFLOAT3(startPoint, 0, startPoint + i * mInterval);
		vertices[4 * i + 1].position = XMFLOAT3(startPoint + (gridPoint - 1) * mInterval, 0, startPoint + i * mInterval);
		vertices[4 * i + 2].position = XMFLOAT3(startPoint + i * mInterval, 0, startPoint);
		vertices[4 * i + 3].position = XMFLOAT3(startPoint + i * mInterval, 0, startPoint + (gridPoint - 1) * mInterval);

		if (i == halfIndex)
		{
			color = XMFLOAT4(0.f, 0.f, 0.f, 1.f);
		}
		else
		{
			color = XMFLOAT4(0.325f, 0.325f, 0.325f, 1.0f);
		}

		vertices[4 * i].color = color;
		vertices[4 * i + 1].color = color;
		vertices[4 * i + 2].color = color;
		vertices[4 * i + 3].color = color;
	}

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
	return true;
}

void GridBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
}

void GridBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	mShader->UpdateShader(deviceContext);

	XMMATRIX matWorld = XMMatrixIdentity();
	mShader->SetMatrixShaderParameters(deviceContext, matWorld, GetViewMatrix(), GetProjectionMatrix());
}

void GridBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(ColorVertex);
	unsigned int offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	deviceContext->Draw(mVertexCount, 0);
}
