#include "pch.h"
#include "LightCubeBuffer.h"
#include "SystemExportFunc.h"
#include "TextureUtil.h"
#include "Shader.h"

LightCubeBuffer::LightCubeBuffer() :
	mTexture(nullptr)
{
	mWorldInfo.scale = XMFLOAT3(2.0f, 2.0f, 2.0f);
}


bool LightCubeBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = 36;
	Vertex vertices[36];

#pragma  region 큐브 버텍스 데이터

	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[0].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[1].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[1].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[2].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[3].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[4].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[4].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[4].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[5].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[5].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[5].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	vertices[6].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[6].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[6].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[7].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[7].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[7].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[8].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[8].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[8].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[9].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[9].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[9].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[10].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[10].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[10].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[11].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[11].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[11].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);

	vertices[12].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[12].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[12].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[13].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[13].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[13].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[14].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[14].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[14].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[15].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[15].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[15].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[16].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[16].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[17].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[17].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[17].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);

	vertices[18].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[18].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[18].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[19].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[19].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[19].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[20].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[20].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[20].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[21].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[21].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[21].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[22].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[22].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[22].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[23].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[23].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[23].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);

	vertices[24].position = XMFLOAT3(-1.0f, 1.0f, 1.0f);
	vertices[24].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[24].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[25].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[25].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[25].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[26].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[26].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[26].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[27].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	vertices[27].uv = XMFLOAT2(-.0f, 1.0f);
	vertices[27].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[28].position = XMFLOAT3(1.0f, 1.0f, 1.0f);
	vertices[28].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[28].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[29].position = XMFLOAT3(1.0f, 1.0f, -1.0f);
	vertices[29].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[29].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);

	vertices[30].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	vertices[30].uv = XMFLOAT2(0.0f, 0.0f);
	vertices[30].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	vertices[31].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[31].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[31].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	vertices[32].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[32].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[32].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	vertices[33].position = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vertices[33].uv = XMFLOAT2(0.0f, 1.0f);
	vertices[33].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	vertices[34].position = XMFLOAT3(1.0f, -1.0f, -1.0f);
	vertices[34].uv = XMFLOAT2(1.0f, 0.0f);
	vertices[34].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

	vertices[35].position = XMFLOAT3(1.0f, -1.0f, 1.0f);
	vertices[35].uv = XMFLOAT2(1.0f, 1.0f);
	vertices[35].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);

#pragma endregion

	D3D11_BUFFER_DESC vertexBufferDesc;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * mVertexCount;
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

void LightCubeBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	Buffer::UpdateBuffers(deviceContext);
}

void LightCubeBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, GetViewMatrix(), GetProjectionMatrix());
		mShader->SetCameraShaderParameters(deviceContext, GetCameraPosition());
		mShader->SetLightShaderParameters(deviceContext, GetAmbientColor(), GetDiffuseColor(), GetLightDirection(), GetSpecularColor(), GetSpecularPower());
	}
}

void LightCubeBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->Draw(mVertexCount, 0);
}

bool LightCubeBuffer::LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName)
{
	HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, fileName, 0, 0, &mTexture, 0);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void LightCubeBuffer::ReleaseBuffer()
{
	if (mTexture)
	{
		mTexture->Release();
		mTexture = nullptr;
	}

	Buffer::ReleaseBuffer();
}

