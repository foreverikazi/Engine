#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL Camera
{
	DECLARE_SINGLE(Camera);
public :
	void InitializeCamera(XMFLOAT3 up, XMFLOAT3 look, XMFLOAT3 position);
	void SetPosition(XMFLOAT3 position);
	void SetRotation(XMFLOAT3 rotation);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void UpdateCamera();
	void CheckKeyboardInput();
	void UpdateViewMatrix();
	void GetViewMatrix(XMMATRIX& viewMatrix);

private:
	XMFLOAT3 mUp;
	XMFLOAT3 mLookAt;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMMATRIX mViewMatrix;
	float	 mCameraSpeed;

public :
	Camera();
	~Camera();
};
