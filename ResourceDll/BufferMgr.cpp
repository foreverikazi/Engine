#include "pch.h"
#include "BufferMgr.h"
#include "Buffer.h"
#include "CubeBuffer.h"

BufferMgr::BufferMgr()
	: mBuffer(nullptr)
{

}

BufferMgr::~BufferMgr()
{

}

bool BufferMgr::AddBuffer(ID3D11Device* device, BUFFERTYPE type)
{
	switch (type)
	{
	case BUFFERTYPE::BUFFERTYPE_CUBE :
		mBuffer = new CubeBuffer();
		mBuffer->CreateBuffers(device);
		break;
	}
	
	return true;
}

void BufferMgr::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	if (mBuffer != nullptr)
	{
		mBuffer->RenderBuffers(deviceContext);
	}
}

void BufferMgr::ReleaseBuffers()
{
	if (mBuffer != nullptr)
	{
		mBuffer->ReleaseBuffer();
		delete mBuffer;
		mBuffer = nullptr;
	}
}


int BufferMgr::GetIndexCount()
{
	return mBuffer->GetIndexCount();
}