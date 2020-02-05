#include "pch.h"
#include "Camera.h"
#include "Input.h"
#include "TimeMgr.h"
#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera()
	: mUp(0.0f, 1.0f, 0.0f),
	mLookAt(0.0f, 0.0f, 1.0f),
	mPosition(0.0f, 0.0f, 0.0f),
	mRotation(0.0f, 0.0f, 0.0f),
	mCameraSpeed(10)
{
}

Camera::~Camera()
{
}

void Camera::InitializeCamera(XMFLOAT3 up, XMFLOAT3 look, XMFLOAT3 position)
{
	mUp = up;
	mLookAt = look;
	mPosition = position;
}

void Camera::SetPosition(XMFLOAT3 position)
{
	mPosition = position;
}

void Camera::SetRotation(XMFLOAT3 rotation)
{
	mRotation = rotation;
}

XMFLOAT3 Camera::GetPosition()
{
	return mPosition;
}

XMFLOAT3 Camera::GetRotation()
{
	return mRotation;
}

void Camera::UpdateCamera()
{
	CheckKeyboardInput();
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

void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = mViewMatrix;
}
