#include "pch.h"
#include "BufferMgr.h"
#include "Buffer.h"


BufferMgr::BufferMgr()
	: mBuffer(nullptr)
{

}

BufferMgr::~BufferMgr()
{

}

bool BufferMgr::AddBuffer(ID3D11Device* device)
{
	mBuffer = new Buffer;
	mBuffer->CreateBuffers(device);
	return true;
}

void BufferMgr::Buffer_Render(ID3D11DeviceContext* deviceContext)
{
	if (mBuffer != nullptr)
	{
		mBuffer->Render(deviceContext);
	}
}

void BufferMgr::ReleaseBuffer()
{
	if (mBuffer != nullptr)
	{
		mBuffer->ReleaseBuffer();
	}
}


int BufferMgr::GetIndexCount()
{
	return mBuffer->GetIndexCount();
}