#pragma once
#include "Define.h"

const UINT PLANE_NUM = 6;

class FrustumCulling
{
	DECLARE_SINGLE(FrustumCulling);
public:
	void InitializeFrustum(const float screenDepth, XMMATRIX viewMat, XMMATRIX projMat);
	bool CullingSphere(const XMFLOAT3 point, const float radius);

private :
	XMVECTOR mPlane[PLANE_NUM];
};

