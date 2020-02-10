#include "pch.h"
#include "FrustumCulling.h"

void FrustumCulling::InitializeFrustum(const float screenDepth, XMMATRIX viewMat, XMMATRIX projMat)
{
	XMMATRIX viewProjMat, newProjMat;
	XMFLOAT4X4 fProjMat, fViewProjMat;
	XMFLOAT4 plane[PLANE_NUM];

	XMStoreFloat4x4(&fProjMat, projMat);

	float nearZ = -fProjMat._43 / fProjMat._33;;
	float r = screenDepth / (screenDepth - nearZ);
	fProjMat._33 = r;
	fProjMat._43 = -r * nearZ;

	newProjMat = XMLoadFloat4x4(&fProjMat);
	viewProjMat = XMMatrixMultiply(viewMat, newProjMat);
	XMStoreFloat4x4(&fViewProjMat, viewProjMat);

#pragma region 절두체 평면 데이터 
	// near
	plane[0].x = fViewProjMat._14 + fViewProjMat._13;
	plane[0].y = fViewProjMat._24 + fViewProjMat._23;
	plane[0].z = fViewProjMat._34 + fViewProjMat._33;
	plane[0].w = fViewProjMat._44 + fViewProjMat._43;

	// far
	plane[1].x = fViewProjMat._14 - fViewProjMat._13;
	plane[1].y = fViewProjMat._24 - fViewProjMat._23;
	plane[1].z = fViewProjMat._34 - fViewProjMat._33;
	plane[1].w = fViewProjMat._44 - fViewProjMat._43;

	// left
	plane[2].x = fViewProjMat._14 + fViewProjMat._11;
	plane[2].y = fViewProjMat._24 + fViewProjMat._21;
	plane[2].z = fViewProjMat._34 + fViewProjMat._31;
	plane[2].w = fViewProjMat._44 + fViewProjMat._41;

	// right
	plane[3].x = fViewProjMat._14 - fViewProjMat._11;
	plane[3].y = fViewProjMat._24 - fViewProjMat._21;
	plane[3].z = fViewProjMat._34 - fViewProjMat._31;
	plane[3].w = fViewProjMat._44 - fViewProjMat._41;

	// top
	plane[4].x = fViewProjMat._14 - fViewProjMat._12;
	plane[4].y = fViewProjMat._24 - fViewProjMat._22;
	plane[4].z = fViewProjMat._34 - fViewProjMat._32;
	plane[4].w = fViewProjMat._44 - fViewProjMat._42;

	// bottom
	plane[5].x = fViewProjMat._14 + fViewProjMat._12;
	plane[5].y = fViewProjMat._24 + fViewProjMat._22;
	plane[5].z = fViewProjMat._34 + fViewProjMat._32;
	plane[5].w = fViewProjMat._44 + fViewProjMat._42;

#pragma endregion

	for (int i = 0; i < PLANE_NUM; i++)
	{
		mPlane[i] = XMPlaneNormalize(XMLoadFloat4(&plane[i]));
	}
}

bool FrustumCulling::CullingSphere(const XMFLOAT3 point, const float radius)
{
	XMVECTOR posVec = XMVectorSet(point.x, point.y, point.z , 1.0f);
	
	for (UINT i = 0; i < PLANE_NUM; i++)
	{
		if(XMVectorGetX(XMPlaneDotCoord(mPlane[i], posVec)) < radius)
		{
			return false;
		}
	}
	return true;
}
