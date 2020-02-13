#include "pch.h"
#include "SkyBuffer.h"
#include "SystemExportFunc.h"
#include "TextureUtil.h"
#include "Shader.h"

SkyBuffer::SkyBuffer() :
	mLatLine(10),
	mLongLine(10)
{
	mWorldInfo.scale = XMFLOAT3(5.0f, 5.0f, 5.0f);
}

bool SkyBuffer::CreateBuffers(ID3D11Device* device)
{
	XMMATRIX matRotX, matRotY;
	mVertexCount = ((mLatLine - 2) * mLongLine) + 2;
	mIndexCount = (((mLatLine - 3)*(mLongLine) * 2) + (mLongLine * 2)) * 3;

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	std::vector<TextureVertex> vertices(mVertexCount);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].position.x = 0.0f;
	vertices[0].position.y = 0.0f;
	vertices[0].position.z = 1.0f;

	for (DWORD i = 0; i < mLatLine - 2; ++i)
	{
		spherePitch = (i + 1) * (XM_PI / (mLatLine - 1));
		matRotX = XMMatrixRotationX(spherePitch);
		for (DWORD j = 0; j < mLongLine; ++j)
		{
			sphereYaw = j * (2.0f * XM_PI / (mLongLine));
			matRotY = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (matRotX * matRotY));
			currVertPos = XMVector3Normalize(currVertPos);
			vertices[i*mLongLine + j + 1].position.x = XMVectorGetX(currVertPos);
			vertices[i*mLongLine + j + 1].position.y = XMVectorGetY(currVertPos);
			vertices[i*mLongLine + j + 1].position.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[mVertexCount - 1].position.x = 0.0f;
	vertices[mVertexCount - 1].position.y = 0.0f;
	vertices[mVertexCount - 1].position.z = -1.0f;


	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));

	vertexBufferData.pSysMem = &vertices[0];

	if (FAILED(device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &mVertexBuffer)))
	{
		return false;
	}


	std::vector<DWORD> indices(mIndexCount);

		int k = 0;
		for (DWORD l = 0; l < mLongLine - 1; ++l)
		{
			indices[k] = 0;
			indices[k + 1] = l + 1;
			indices[k + 2] = l + 2;
			k += 3;
		}

	indices[k] = 0;
	indices[k + 1] = mLongLine;
	indices[k + 2] = 1;
	k += 3;

	for (DWORD i = 0; i < mLatLine - 3; ++i)
	{
		for (DWORD j = 0; j < mLongLine - 1; ++j)
		{
			indices[k] = i * mLongLine + j + 1;
			indices[k + 1] = i * mLongLine + j + 2;
			indices[k + 2] = (i + 1)*mLongLine + j + 1;

			indices[k + 3] = (i + 1)*mLongLine + j + 1;
			indices[k + 4] = i * mLongLine + j + 2;
			indices[k + 5] = (i + 1)*mLongLine + j + 2;

			k += 6; // next quad
		}

		indices[k] = (i*mLongLine) + mLongLine;
		indices[k + 1] = (i*mLongLine) + 1;
		indices[k + 2] = ((i + 1)*mLongLine) + mLongLine;

		indices[k + 3] = ((i + 1)*mLongLine) + mLongLine;
		indices[k + 4] = (i*mLongLine) + 1;
		indices[k + 5] = ((i + 1)*mLongLine) + 1;

		k += 6;
	}

	for (DWORD l = 0; l < mLongLine - 1; ++l)
	{
		indices[k] = mVertexCount - 1;
		indices[k + 1] = (mVertexCount - 1) - (l + 1);
		indices[k + 2] = (mVertexCount - 1) - (l + 2);
		k += 3;
	}

	indices[k] = mVertexCount - 1;
	indices[k + 1] = (mVertexCount - 1) - mLongLine;
	indices[k + 2] = mVertexCount - 2;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * mIndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	if (FAILED(device->CreateBuffer(&indexBufferDesc, &iinitData, &mIndexBuffer)))
	{
		return false;
	}

	return true;
}

void SkyBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	mWorldInfo.position = GetCameraPosition();
	Buffer::UpdateBuffers(deviceContext);
}

void SkyBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, GetViewMatrix(), GetProjectionMatrix());
	}
}

void SkyBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(TextureVertex);
	unsigned int offset = 0;


	SetCullMode(D3D11_CULL_MODE::D3D11_CULL_NONE);
	SetDepthFunc(D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL);
	//SetFrontCounterClockwise(false);

	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(mIndexCount, 0, 0);

	SetCullMode(D3D11_CULL_MODE::D3D11_CULL_BACK);
	SetDepthFunc(D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS);
	//SetFrontCounterClockwise(true);
}

bool SkyBuffer::LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* fileName)
{
	ID3D11Texture2D* texture2D;
	D3DX11_IMAGE_LOAD_INFO loadInfo;
	loadInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
	if (FAILED(D3DX11CreateTextureFromFile(device, fileName, &loadInfo, 0, (ID3D11Resource**)&texture2D, 0)))
	{
		return false;
	}
	D3D11_TEXTURE2D_DESC textureDesc;
	texture2D->GetDesc(&textureDesc);

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = textureDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	viewDesc.TextureCube.MipLevels = textureDesc.MipLevels;
	viewDesc.TextureCube.MostDetailedMip = 0;

	if (FAILED(device->CreateShaderResourceView(texture2D, &viewDesc, &mTexture)))
	{
		return false;
	}

	return true;
}

void SkyBuffer::ReleaseBuffer()
{
	if (mTexture)
	{
		mTexture->Release();
		mTexture = nullptr;
	}

	Buffer::ReleaseBuffer();
}

