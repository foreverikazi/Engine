#include "pch.h"
#include "SystemExportFunc.h"
#include "D3DApp.h"
#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Light.h"
#include "ShaderMgr.h"
#include "TimeMgr.h"
#include "Shader.h"

EXTERN SYSTEM_DLL bool InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
	return (*(D3DApp::GetInst()))->InitializeD3D(screenWidth, screenHeight, vsync, hwnd, fullscreen, screenDepth, screenNear);
} 

EXTERN SYSTEM_DLL void Release3D()
{
	(*(D3DApp::GetInst()))->Release3D();
}

EXTERN SYSTEM_DLL void BeginScene(const float r, const float g, const float b, const float a)
{
	(*(D3DApp::GetInst()))->BeginScene(r, g, b, a);
}

EXTERN SYSTEM_DLL void EndScene()
{
	(*(D3DApp::GetInst()))->EndScene();
}

EXTERN SYSTEM_DLL ID3D11Device* GetDevice()
{
	return (*(D3DApp::GetInst()))->GetDevice();
}

EXTERN SYSTEM_DLL ID3D11DeviceContext* GetDeviceContext()
{
	return (*(D3DApp::GetInst()))->GetDeviceContext();
}

EXTERN SYSTEM_DLL void GetWorldMatrix(XMMATRIX& worldMatrix)
{
	(*(D3DApp::GetInst()))->GetWorldMatrix(worldMatrix);
}

EXTERN SYSTEM_DLL void SetFrontCounterClockwise(const bool clockwise)
{
	(*(D3DApp::GetInst()))->SetFrontCounterClockwise(clockwise);
}

EXTERN SYSTEM_DLL void SetCullMode(const D3D11_CULL_MODE cullMode)
{
	(*(D3DApp::GetInst()))->SetCullMode(cullMode);
}

EXTERN SYSTEM_DLL void SetFillMode(const D3D11_FILL_MODE fillMode)
{
	(*(D3DApp::GetInst()))->SetFillMode(fillMode);
}

EXTERN SYSTEM_DLL void SetDepthFunc(const D3D11_COMPARISON_FUNC compFunc)
{
	(*(D3DApp::GetInst()))->SetDepthFunc(compFunc);
}

// Camera
EXTERN SYSTEM_DLL void InitializeCamera(const XMFLOAT3 up, const XMFLOAT3 look, const XMFLOAT3 position)
{
	(*(Camera::GetInst()))->InitializeCamera(up, look, position);
}


EXTERN SYSTEM_DLL void InitializeProjectionMatrix(const float fov, const float aspectRatio, const float nearZ, const float farZ)
{
	(*(Camera::GetInst()))->InitializeProjectionMatrix(fov, aspectRatio, nearZ, farZ);
}

EXTERN SYSTEM_DLL void SetCameraPosition(const XMFLOAT3 position)
{
    (*(Camera::GetInst()))->SetPosition(position);
}

EXTERN SYSTEM_DLL void SetCameraRotation(const XMFLOAT3 rotation)
{
	(*(Camera::GetInst()))->SetRotation(rotation);
}

EXTERN SYSTEM_DLL XMFLOAT3 GetCameraPosition()
{
	return (*(Camera::GetInst()))->GetPosition();
}

EXTERN SYSTEM_DLL XMFLOAT3 GetCameraRotation()
{
	return (*(Camera::GetInst()))->GetRotation();
}

EXTERN SYSTEM_DLL void UpdateCamera()
{
	(*(Camera::GetInst()))->UpdateCamera();
}

EXTERN SYSTEM_DLL XMMATRIX GetViewMatrix()
{
	return (*(Camera::GetInst()))->GetViewMatrix();
}

EXTERN SYSTEM_DLL XMMATRIX GetProjectionMatrix()
{
	return (*(Camera::GetInst()))->GetProjectionMatrix();
}

EXTERN SYSTEM_DLL bool InitializeInput(HINSTANCE hinstance, HWND hwnd)
{
	return (*(Input::GetInst()))->InitializeInput(hinstance, hwnd);
}

EXTERN SYSTEM_DLL void UpdateInput()
{
	(*(Input::GetInst()))->UpdateInput();
}

EXTERN SYSTEM_DLL BOOL GetKeyBoardState(BYTE keyID)
{
	return (*(Input::GetInst()))->GetKeyBoardState(keyID);
}

EXTERN SYSTEM_DLL const DIMOUSESTATE* GetMouseState()
{
	return (*(Input::GetInst()))->GetMouseState();
}

EXTERN SYSTEM_DLL void InitializeTimer()
{
	(*(TimeMgr::GetInst()))->InitializeTimer();
}

EXTERN SYSTEM_DLL void UpdateTimer()
{
	(*(TimeMgr::GetInst()))->UpdateTimer();
}

EXTERN SYSTEM_DLL float GetElapsedTime()
{
	return (*(TimeMgr::GetInst()))->GetElapsedTime();
}

// Shader
EXTERN SYSTEM_DLL bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERTYPE type)
{
	return (*(ShaderMgr::GetInst()))->InitializeShader(device, hwnd, vsFilename, psFilename, type);
}

EXTERN SYSTEM_DLL void ReleaseShader()
{
	(*(ShaderMgr::GetInst()))->ReleaseShader();
}

EXTERN SYSTEM_DLL Shader* GetShader(const SHADERTYPE type)
{
	return (*(ShaderMgr::GetInst()))->GetShader(type);
}

EXTERN SYSTEM_DLL void SetAmbientColor(const XMFLOAT4 ambientColor)
{
	(*(Light::GetInst()))->SetAmbientColor(ambientColor);
}

EXTERN SYSTEM_DLL void SetDiffuseColor(const XMFLOAT4 diffuseColor)
{
	(*(Light::GetInst()))->SetDiffuseColor(diffuseColor);
}

EXTERN SYSTEM_DLL void SetSpecularColor(const XMFLOAT4 specularColor)
{
	(*(Light::GetInst()))->SetSpecularColor(specularColor);
}

EXTERN SYSTEM_DLL void SetLightDirection(const XMFLOAT3 direction)
{
	(*(Light::GetInst()))->SetLightDirection(direction);
}

EXTERN SYSTEM_DLL void SetSpecularPower(const float specularPower)
{
	(*(Light::GetInst()))->SetSpecularPower(specularPower);
}

EXTERN SYSTEM_DLL XMFLOAT4 GetAmbientColor()
{
	return (*(Light::GetInst()))->GetAmbientColor();
}

EXTERN SYSTEM_DLL XMFLOAT4 GetDiffuseColor()
{
	return (*(Light::GetInst()))->GetDiffuseColor();
}

EXTERN SYSTEM_DLL XMFLOAT4 GetSpecularColor()
{
	return (*(Light::GetInst()))->GetSpecularColor();
}

EXTERN SYSTEM_DLL XMFLOAT3 GetLightDirection()
{
	return (*(Light::GetInst()))->GetLightDirection();
}

EXTERN SYSTEM_DLL float GetSpecularPower()
{
	return (*(Light::GetInst()))->GetSpecularPower();
}

// System
EXTERN SYSTEM_DLL void ReleaseSystem()
{
	(*(ShaderMgr::GetInst()))->DestroyInst();
	(*(D3DApp::GetInst()))->DestroyInst();
	(*(Camera::GetInst()))->DestroyInst();
	(*(Input::GetInst()))->DestroyInst();
	(*(TimeMgr::GetInst()))->DestroyInst();
	(*(Light::GetInst()))->DestroyInst();
}

