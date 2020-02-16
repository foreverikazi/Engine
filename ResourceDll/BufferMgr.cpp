#include "pch.h"
#include "BufferMgr.h"
#include "Buffer.h"
#include "SystemExportFunc.h"
#include "ColorCubeBuffer.h"
#include "TextureCubeBuffer.h"
#include "LightCubeBuffer.h"
#include "GridBuffer.h"
#include "SkyBuffer.h"
#include "BitmapBuffer.h"
#include "FontBuffer.h"

BufferMgr::BufferMgr()
{

}

BufferMgr::~BufferMgr()
{

}

bool BufferMgr::AddBuffer(ID3D11Device* device, BUFFERTYPE bufferType, const SHADERTYPE Shadertype, const TCHAR* key)
{
	Buffer* newBuffer = nullptr;
	Shader* shader = GetShader(Shadertype);

	if (shader == nullptr)
	{
		return false;
	}

	// ���߿� object Ŭ���� ����� ���丮�� �ڵ� �ٲܰ�
	switch (bufferType)
	{
	case BUFFERTYPE::COLOR_CUBE:
		newBuffer = new ColorCubeBuffer();
		
		break;

	case BUFFERTYPE::GRID :
		newBuffer = new GridBuffer();
		break;

	case BUFFERTYPE::TEXTURE_CUBE :
		newBuffer = new TextureCubeBuffer();
		break;

	case BUFFERTYPE::LIGHT_CUBE:
		newBuffer = new LightCubeBuffer();
		break;

	case BUFFERTYPE::SKY :
		newBuffer = new SkyBuffer();
		break;

	case BUFFERTYPE::BITMAP :
		newBuffer = new BitmapBuffer();
		break;

	default :
		return false;
	}
	
	if (newBuffer)
	{
		newBuffer->CreateBuffers(device);
		newBuffer->SetShader(shader);
		mBufferMap.insert({ key, newBuffer });
	}
	return true;
}

bool BufferMgr::LoadTextureBuffer(ID3D11Device* device, const TCHAR* key, const TCHAR* fileName)
{
	Buffer* buffer = FindBuffer(key);
	
	if (buffer)
	{
		return buffer->LoadTextureBuffer(device, fileName);
	}

	return false;
}

void BufferMgr::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	for (auto buffer : mBufferMap)
	{
		buffer.second->UpdateBuffers(deviceContext);
	}
}

void BufferMgr::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	for (auto buffer : mBufferMap)
	{
		buffer.second->RenderBuffers(deviceContext);
	}
}

void BufferMgr::ReleaseBuffers()
{
	for (auto buffer : mBufferMap)
	{
		if (buffer.second != nullptr)
		{
			buffer.second->ReleaseBuffer();
			delete buffer.second;
			buffer.second = nullptr;
		}
	}

	mBufferMap.clear();
}

Buffer* BufferMgr::FindBuffer(const TCHAR* key)
{
	auto buffer = mBufferMap.find(key);

	if (buffer != mBufferMap.end())
	{
		return buffer->second;
	}

	return nullptr;
}
