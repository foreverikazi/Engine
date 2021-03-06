#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "TimeMgr.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
using namespace std;

Camera::Camera()
	: mUp(0.0f, 1.0f, 0.0f),
	mLookAt(0.0f, 0.0f, 1.0f),
	mPosition(0.0f, 0.0f, 0.0f),
	mRotation(0.0f, 0.0f, 0.0f),
	mCameraSpeed(10),
	mMouseSensitivity(0.2f)
{
}

Camera::~Camera()
{
}

void Camera::InitializeCamera(const XMFLOAT3 up, const XMFLOAT3 look, const XMFLOAT3 position)
{
	mUp = up;
	mLookAt = look;
	mPosition = position;
	UpdateViewMatrix();
}



void Camera::UpdateCamera()
{
	CheckKeyboardInput();
	CheckMouseInput();
	UpdateViewMatrix();
}

void Camera::CheckKeyboardInput()
{
	Input* input = (*Input::GetInst());
	TimeMgr* timeMgr = (*TimeMgr::GetInst());

	if (input->GetKeyBoardState(DIK_UP))
	{
		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
		XMVECTOR dir = XMVector4Normalize(lookAt - position);

		float ElapseTime = timeMgr->GetElapsedTime();
		position += dir * mCameraSpeed * ElapseTime;
		lookAt += dir * mCameraSpeed * ElapseTime;

		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mLookAt, lookAt);
	}

	if (input->GetKeyBoardState(DIK_DOWN))
	{
		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
		XMVECTOR dir = XMVector4Normalize(lookAt - position);

		float ElapseTime = timeMgr->GetElapsedTime();
		position -= dir * mCameraSpeed * ElapseTime;
		lookAt -= dir * mCameraSpeed * ElapseTime;

		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mLookAt, lookAt);
	}

	if (input->GetKeyBoardState(DIK_LEFT))
	{
		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
		XMVECTOR up = XMLoadFloat3(&mUp);
		XMVECTOR dir = XMVector4Normalize(lookAt - position);
		XMVECTOR left = XMVector3Cross(dir, up);
		left = XMVector4Normalize(left);

		float ElapseTime = timeMgr->GetElapsedTime();
		position += left * mCameraSpeed * ElapseTime;
		lookAt += left * mCameraSpeed * ElapseTime;

		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mLookAt, lookAt);
	}

	if (input->GetKeyBoardState(DIK_RIGHT))
	{
		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
		XMVECTOR up = XMLoadFloat3(&mUp);
		XMVECTOR dir = XMVector4Normalize(lookAt - position);
		XMVECTOR right = XMVector3Cross(up, dir);
		right = XMVector4Normalize(right);

		float ElapseTime = timeMgr->GetElapsedTime();
		position += right * mCameraSpeed * ElapseTime;
		lookAt += right * mCameraSpeed * ElapseTime;

		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mLookAt, lookAt);
	}
}

void Camera::CheckMouseInput()
{
	const DIMOUSESTATE* mouseState = (*Input::GetInst())->GetMouseState();
	if ((mouseState->rgbButtons[1] & 0x80))
	{
		if (mouseState->lX)
		{
			XMMATRIX matRot;
			XMVECTOR position = XMLoadFloat3(&mPosition);
			XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
			XMVECTOR up = XMLoadFloat3(&mUp);
			matRot = XMMatrixRotationAxis(up, XMConvertToRadians(mouseState->lX * mMouseSensitivity));

			XMVECTOR dir = XMVector4Normalize(lookAt - position);
			dir = XMVector3TransformNormal(dir, matRot);
			
			lookAt = position + dir;
			XMStoreFloat3(&mLookAt, lookAt);
		}
		
		if (mouseState->lY)
		{
			XMMATRIX matRot;
			XMVECTOR position = XMLoadFloat3(&mPosition);
			XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
			XMVECTOR up = XMLoadFloat3(&mUp);

			XMVECTOR dir = XMVector4Normalize(lookAt - position);
			XMVECTOR right = XMVector3Cross(up, dir);
			right = XMVector4Normalize(right);

			matRot = XMMatrixRotationAxis(right, XMConvertToRadians(mouseState->lY * mMouseSensitivity));
			dir = XMVector3TransformNormal(dir, matRot);
			
			lookAt = position + dir;
			XMStoreFloat3(&mLookAt, lookAt);
		}
	}
	if (mouseState->lZ)
	{
		TimeMgr* timeMgr = (*TimeMgr::GetInst());
		float ElapseTime = timeMgr->GetElapsedTime();

		XMVECTOR position = XMLoadFloat3(&mPosition);
		XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
		XMVECTOR dir = XMVector4Normalize(lookAt - position);

		position += dir * mMouseSensitivity * ElapseTime * (float)mouseState->lZ;
		lookAt += dir * mMouseSensitivity * ElapseTime * (float)mouseState->lZ;

		XMStoreFloat3(&mPosition, position);
		XMStoreFloat3(&mLookAt, lookAt);
	}
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR upVector, positionVector, lookAtVector;
	XMMATRIX rotationMatrix;
	float yaw, pitch, roll;

	upVector = XMLoadFloat3(&mUp);
	positionVector = XMLoadFloat3(&mPosition);
	lookAtVector = XMLoadFloat3(&mLookAt);

	pitch = XMConvertToRadians(mRotation.x);
	yaw = XMConvertToRadians(mRotation.y);
	roll = XMConvertToRadians(mRotation.z);

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	mViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}

void Camera::InitializeProjectionMatrix(const float fov, const float aspectRatio, const float nearZ, const float farZ)
{
	mFieldOfView = fov;
	mAspectRatio = aspectRatio;
	mNearZ = nearZ;
	mFarZ = farZ;

	mProjMatrix = XMMatrixPerspectiveFovLH(mFieldOfView, aspectRatio, nearZ, farZ);
	
}

XMMATRIX Camera::GetViewMatrix() const
{
	return mViewMatrix;
}

XMMATRIX Camera::GetProjectionMatrix() const
{
	return mProjMatrix;
}

void Camera::SetPosition(const XMFLOAT3 position)
{
	mPosition = position;
}

void Camera::SetRotation(const XMFLOAT3 rotation)
{
	mRotation = rotation;
}

void Camera::SetFieldOfView(const float fov)
{
	mFieldOfView = fov;
}

XMFLOAT3 Camera::GetPosition() const
{
	return mPosition;
}

XMFLOAT3 Camera::GetRotation() const
{
	return mRotation;
}

float Camera::GetFieldOfView() const
{
	return mFieldOfView;
}