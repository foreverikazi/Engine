#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL Camera
{
	DECLARE_SINGLE(Camera);
public :
	void InitializeCamera(const XMFLOAT3 up, const XMFLOAT3 look, const XMFLOAT3 position);
	void UpdateCamera();
	void CheckKeyboardInput();
	void CheckMouseInput();
	void UpdateViewMatrix();
	void InitializeProjectionMatrix(const float fov, const float aspectRatio, const float nearZ, const float farZ);

public :
	void SetPosition(const XMFLOAT3 position);
	void SetRotation(const XMFLOAT3 rotation);
	void SetFieldOfView(const float fov);

	XMFLOAT3 GetPosition() const;
	XMFLOAT3 GetRotation() const;
	float GetFieldOfView() const;
	XMMATRIX GetViewMatrix() const;
	XMMATRIX GetProjectionMatrix() const;

private:
	XMMATRIX mViewMatrix;
	XMMATRIX mProjMatrix;

	XMFLOAT3 mUp;
	XMFLOAT3 mLookAt;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	
	float	 mCameraSpeed;
	float	 mMouseSensitivity;
	float	 mFieldOfView;
	float	 mAspectRatio;
	float	 mNearZ;
	float	 mFarZ;

public :
	Camera();
	~Camera();
};
