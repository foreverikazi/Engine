#include "pch.h"
#include "FontBuffer.h"
#include "SystemExportFunc.h"
#include "Shader.h"
#include "FontShader.h"

FontBuffer::FontBuffer() :
	mTexture(nullptr),
	mFontInfo(nullptr),
	mMaxLength(20),
	mTextLength(0)
{
	mViewMat = GetViewMatrix();
}

bool FontBuffer::CreateBuffers(ID3D11Device* device)
{
	mVertexCount = mMaxLength * 6;
	mIndexCount = mMaxLength * 6;

	std::vector<TextureVertex> vertices(mVertexCount);
	std::vector<DWORD> indices(mIndexCount);

	for (UINT i = 0; i < mIndexCount; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(TextureVertex) * mVertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &vertices[0];
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
	indexData.pSysMem = &indices[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	if (FAILED(device->CreateBuffer(&indexBufferDesc, &indexData, &mIndexBuffer)))
	{
		return false;
	}

	return true;
}

void FontBuffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	Buffer::UpdateBuffers(deviceContext);
}

void FontBuffer::UpdateSahder(ID3D11DeviceContext* deviceContext)
{
	if (mShader)
	{
		mShader->UpdateShader(deviceContext);
		mShader->SetMatrixShaderParameters(deviceContext, mWorldInfo.worldMat, mViewMat, GetOrthoMatrix());
		
		FontShader* shader = dynamic_cast<FontShader*>(mShader);
		if (shader)
		{
			shader->SetColorShaderParameter(deviceContext, mColor);
		}
	}
}

void FontBuffer::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	FontShader* shader = dynamic_cast<FontShader*>(mShader);
	if (shader == nullptr || mTextLength <= 0)
	{
		return;
	}

	UpdateBuffers(deviceContext); // 임시 처리
	UpdateSahder(deviceContext);

	unsigned int stride = sizeof(TextureVertex);
	unsigned int offset = 0;
	
	deviceContext->PSSetShaderResources(0, 1, &mTexture);
	deviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(mIndexCount, 0, 0);
}

bool FontBuffer::LoadTextureBuffer(ID3D11Device* device, const TCHAR* fileName)
{
	HRESULT result = D3DX11CreateShaderResourceViewFromFile(device, fileName, 0, 0, &mTexture, 0);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void FontBuffer::ReleaseBuffer()
{
	SAFE_RELEASE(mTexture);
	SAFE_DELETE_ARRAY(mFontInfo);
	Buffer::ReleaseBuffer();
}

bool FontBuffer::LoadFontData(const TCHAR* fileName)
{
	ifstream fin;
	int i;
	char temp;

	if (mFontInfo)
	{
		SAFE_DELETE_ARRAY(mFontInfo);
	}
	mFontInfo = new FontInfo[95];
	
	fin.open(fileName);
	if (fin.fail())
	{
		return false;
	}

	for (i = 0; i < 95; i++)
	{
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}
		fin.get(temp);
		while (temp != ' ')
		{
			fin.get(temp);
		}

		fin >> mFontInfo[i].left;
		fin >> mFontInfo[i].right;
		fin >> mFontInfo[i].size;
	}

	fin.close();

	return true;
}

void FontBuffer::SetText(ID3D11DeviceContext* deviceContext, const TCHAR* text, XMFLOAT2 position, const XMFLOAT4 color)
{
	if (mVertexCount <= 0)
	{
		return;
	}
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	vector<TextureVertex> vertices(mVertexCount);
	int letter = 0;
	int index = 0;

	mColor = color;
	mTextLength = (UINT)_tcslen(text);

	for (UINT i = 0; i < mTextLength; i++)
	{
		letter = ((int)text[i]) - 32;

		if (letter == 0)
		{
			position.x = position.x + 3.0f;
		}
		else
		{
			vertices[index].position = XMFLOAT3(position.x, position.y, 0.0f);  // Top left.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].left, 0.0f);
			index++;

			vertices[index].position = XMFLOAT3((position.x + mFontInfo[letter].size), (position.y - 16), 0.0f);  // Bottom right.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].right, 1.0f);
			index++;

			vertices[index].position = XMFLOAT3(position.x, (position.y - 16), 0.0f);  // Bottom left.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].left, 1.0f);
			index++;

			vertices[index].position = XMFLOAT3(position.x, position.y, 0.0f);  // Top left.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].left, 0.0f);
			index++;

			vertices[index].position = XMFLOAT3(position.x + mFontInfo[letter].size, position.y, 0.0f);  // Top right.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].right, 0.0f);
			index++;

			vertices[index].position = XMFLOAT3((position.x + mFontInfo[letter].size), (position.y - 16), 0.0f);  // Bottom right.
			vertices[index].uv = XMFLOAT2(mFontInfo[letter].right, 1.0f);
			index++;

			position.x = position.x + mFontInfo[letter].size + 1.0f;
		}
	}

	deviceContext->Map(mVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	TextureVertex* verticesPtr = (TextureVertex*)mappedResource.pData;
	memcpy(verticesPtr, (void*)&vertices[0], (sizeof(TextureVertex) * mVertexCount));
	
	deviceContext->Unmap(mVertexBuffer, 0);
}

