#include "pch.h"
#include "BufferMgr.h"
#include "Buffer.h"
#include "ColorCubeBuffer.h"
#include "TextureCubeBuffer.h"
#include "LightCubeBuffer.h"
#include "GridBuffer.h"

BufferMgr::BufferMgr()
{

}

BufferMgr::~BufferMgr()
{

}

bool BufferMgr::AddBuffer(ID3D11Device* device, BUFFERTYPE type, const TCHAR* key)
{
	Buffer* newBuffer = nullptr;

	switch (type)
	{
	case BUFFERTYPE::BUFFERTYPE_COLOR_CUBE:
		newBuffer = new ColorCubeBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
		break;

	case BUFFERTYPE::BUFFERTYPE_GRID :
		newBuffer = new GridBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
		break;

	case BUFFERTYPE::BUFFERTYPE_TEXTURE_CUBE :
		newBuffer = new TextureCubeBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
		break;

	case BUFFERTYPE::BUFFERTYPE_LIGHT_CUBE:
		newBuffer = new LightCubeBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
		break;
	}
	
	return true;
}

void BufferMgr::LoadTextureBuffer(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const TCHAR* key, const TCHAR* fileName)
{
	Buffer* buffer = FindBuffer(key);
	
	if (buffer)
	{
		buffer->LoadTextureBuffer(device, deviceContext, fileName);
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
	for (auto iter = mBufferMap.begin(); iter != mBufferMap.end(); iter ++)
	{
		if (iter->second != nullptr)
		{
			iter->second->ReleaseBuffer();
			delete iter->second;
			iter->second = nullptr;
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
