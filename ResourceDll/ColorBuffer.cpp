#include "pch.h"
#include "ColorBuffer.h"

bool ColorBuffer::CreateBuffers(ID3D11Device* device, Vertex& vertices, vector<unsigned long>& indices, D3D11_PRIMITIVE_TOPOLOGY type)
{
	//D3D11_BUFFER_DESC vertexBufferDesc;
	//vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDesc.ByteWidth = sizeof(VertexType) * mVertexCount;
	//vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDesc.CPUAccessFlags = 0;
	//vertexBufferDesc.MiscFlags = 0;
	//vertexBufferDesc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA vertexData;
	//vertexData.pSysMem = &vertices;
	//vertexData.SysMemPitch = 0;
	//vertexData.SysMemSlicePitch = 0;

	//if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexData, &mVertexBuffer)))
	//{
	//	return false;
	//}

	//D3D11_BUFFER_DESC indexBufferDesc;
	//indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//indexBufferDesc.ByteWidth = sizeof(unsigned long) * mIndexCount;
	//indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	//indexBufferDesc.CPUAccessFlags = 0;
	//indexBufferDesc.MiscFlags = 0;
	//indexBufferDesc.StructureByteStride = 0;

	//D3D11_SUBRESOURCE_DATA indexData;
	//indexData.pSysMem = &indices;
	//indexData.SysMemPitch = 0;
	//indexData.SysMemSlicePitch = 0;

	//if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer)))
	//{
	//	return false;
	//}

	////delete[] vertices;
	////vertices = 0;

	////delete[] indices;
	////indices = 0;

	//return true;

	return true;
}

void ColorBuffer::Render(ID3D11DeviceContext* deviceContext)
{

}

void ColorBuffer::Shutdown()
{

}
