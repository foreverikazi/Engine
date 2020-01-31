#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL EditorCameraController
{
	DECLARE_SINGLE(EditorCameraController);
public :
	void InitCamera(XMFLOAT3 up, XMFLOAT3 look, XMFLOAT3 position);
	void SetPosition(XMFLOAT3 position);
	void SetRotation(XMFLOAT3 rotation);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void UpdateCamera();
	void GetViewMatrix(XMMATRIX& viewMatrix);

private:
	XMFLOAT3 mUp;
	XMFLOAT3 mLook;
	XMFLOAT3 mPosition;
	XMFLOAT3 mRotation;
	XMMATRIX mViewMatrix;

public :
	EditorCameraController();
	~EditorCameraController();
};
