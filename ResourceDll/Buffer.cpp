#include "pch.h"
#include "Buffer.h"


Buffer::Buffer() :mWorldInfo(
		XMFLOAT3(1, 1, 1), 
		XMFLOAT3(0, 0, 0), 
		XMFLOAT3(0, 0, 0), 
		XMMatrixIdentity())
{

}

Buffer::~Buffer()
{

}

void Buffer::UpdateBuffers(ID3D11DeviceContext* deviceContext)
{
	XMMATRIX scaleMat, rotMat, transMat;
	scaleMat = XMMatrixScaling(mWorldInfo.scale.x, mWorldInfo.scale.y, mWorldInfo.scale.z);
	rotMat = XMMatrixRotationRollPitchYaw(mWorldInfo.rotation.x, mWorldInfo.rotation.y, mWorldInfo.rotation.z);
	transMat = XMMatrixTranslation(mWorldInfo.position.x, mWorldInfo.position.y, mWorldInfo.position.z);

	mWorldInfo.worldMat = scaleMat * rotMat * transMat;
}

void Buffer::ReleaseBuffer()
{
	SAFE_RELEASE(mIndexBuffer);
	SAFE_RELEASE(mVertexBuffer);
}

void Buffer::SetShader(Shader* shader)
{
	mShader = shader;
}

void Buffer::SetPosition(const XMFLOAT3 position)
{
	mWorldInfo.position = position;
}

void Buffer::SetScale(const XMFLOAT3 scale)
{
	mWorldInfo.scale = scale;
}

void Buffer::SetRotation(const XMFLOAT3 rotation)
{
	mWorldInfo.rotation = rotation;
}

XMFLOAT3 Buffer::GetPosition() const
{
	return mWorldInfo.position;
}

XMFLOAT3 Buffer::GetScale() const
{
	return mWorldInfo.scale;
}

XMFLOAT3 Buffer::GetRotation() const
{
	return mWorldInfo.rotation;
}

XMMATRIX Buffer::GetWorldMatrix() const
{
	return mWorldInfo.worldMat;
}

int Buffer::GetIndexCount() const
{
	return mIndexCount;
}
