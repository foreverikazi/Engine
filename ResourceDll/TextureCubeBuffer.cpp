#include "pch.h"
#include "TextureCubeBuffer.h"
#include "SystemExportFunc.h"
#include "TextureUtil.h"
#include "Shader.h"

bool TextureCubeBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = 36;

	TextureVertex vertices[36];

#pragma  region 큐브 버텍스 데이터

	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[0].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[1].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[1].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[2].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[3].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[4].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[5].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[5].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[6].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[6].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[7].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[7].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[8].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[8].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[9].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[9].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[10].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[10].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[11].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[11].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[12].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[12].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[13].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[13].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[14].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[14].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[15].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[15].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[16].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[16].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[17].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[17].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[18].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[18].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[19].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[19].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[20].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[20].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[21].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[21].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[22].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[22].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[23].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[23].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[24].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[24].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[25].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[25].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[26].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[26].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[27].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[27].uv = XMFLOAT2(-.0f, 1.0f);

	vertices[28].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[28].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[29].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[29].uv = XMFLOAT2(1.0f, 1.0f);

	vertices[30].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[30].uv = XMFLOAT2(0.0f, 0.0f);

	vertices[31].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[31].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[32].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[32].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[33].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[33].uv = XMFLOAT2(0.0f, 1.0f);

	vertices[34].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[34].uv = XMFLOAT2(1.0f, 0.0f);

	vertices[35].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[35].uv = XMFLOAT2(1.0f, 1.0f);

#pragma endregion

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertex) * mVertexCount;
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

void TextureCubeBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{

}

void TextureCubeBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, GetViewMatrix(), GetProjectionMatrix());
	}
}

void TextureCubeBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(TextureVertex);
	unsigned int offset = 0;

	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->Draw(mVertexCount, 0);
}

bool TextureCubeBuffer::LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* fileName)
{
	mTexture = (*(TextureUtil::GetInst()))->LoadTextureUtil(device, deviceContext, fileName);
	return true;
}

void TextureCubeBuffer::ReleaseBuffer()
{
	if (mTexture)
	{
		mTexture->Release();
		mTexture = nullptr;
	}

	Buffer::ReleaseBuffer();
}
