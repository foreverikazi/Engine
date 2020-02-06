#include "pch.h"
#include "BufferMgr.h"
#include "Buffer.h"
#include "CubeBuffer.h"
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
	case BUFFERTYPE::BUFFERTYPE_CUBE :
		newBuffer = new CubeBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
		break;

	case BUFFERTYPE::BUFFERTYPE_GRID :
		newBuffer = new GridBuffer();
		newBuffer->CreateBuffers(device);
		mBufferMap.insert({ key, newBuffer });
	}
	
	return true;
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
