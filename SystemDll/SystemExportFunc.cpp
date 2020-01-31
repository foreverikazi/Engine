#include "pch.h"
#include "SystemExportFunc.h"
#include "D3DApp.h"
#include "CameraController.h"
#include "Shader.h"
#include "Light.h"

EXTERN SYSTEM_DLL bool InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear)
{
	return (*(D3DApp::GetInst()))->InitializeD3D(screenWidth, screenHeight, vsync, hwnd, fullscreen, screenDepth, screenNear);
} 

EXTERN SYSTEM_DLL void Release3D()
{
	(*(D3DApp::GetInst()))->Release3D();
}

EXTERN SYSTEM_DLL void BeginScene(float red, float green, float blue, float alpha)
{
	(*(D3DApp::GetInst()))->BeginScene(red, green, blue, alpha);
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

EXTERN SYSTEM_DLL void GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	(*(D3DApp::GetInst()))->GetProjectionMatrix(projectionMatrix);
}

EXTERN SYSTEM_DLL void GetWorldMatrix(XMMATRIX& worldMatrix)
{
	(*(D3DApp::GetInst()))->GetWorldMatrix(worldMatrix);
}

// Camera
EXTERN SYSTEM_DLL void SetCameraPosition(XMFLOAT3 position)
{
    (*(EditorCameraController::GetInst()))->SetPosition(position);
}

EXTERN SYSTEM_DLL void SetCameraRotation(XMFLOAT3 rotation)
{
	(*(EditorCameraController::GetInst()))->SetRotation(rotation);
}

EXTERN SYSTEM_DLL XMFLOAT3 GetCameraPosition()
{
	return (*(EditorCameraController::GetInst()))->GetPosition();
}

EXTERN SYSTEM_DLL XMFLOAT3 GetCameraRotation()
{
	return (*(EditorCameraController::GetInst()))->GetRotation();
}

EXTERN SYSTEM_DLL void UpdateCamera()
{
	(*(EditorCameraController::GetInst()))->UpdateCamera();
}

EXTERN SYSTEM_DLL void GetViewMatrix(XMMATRIX& viewMatrix)
{
	(*(EditorCameraController::GetInst()))->GetViewMatrix(viewMatrix);
}

// Shader
EXTERN SYSTEM_DLL bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	return (*(Shader::GetInst()))->InitializeShader(device, hwnd, vsFilename, psFilename);
}

//EXTERN SYSTEM_DLL bool InitializeShader2(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
//{
//	return (*(Shader::GetInst()))->InitializeShader2(device, hwnd, vsFilename, psFilename);
//}

EXTERN SYSTEM_DLL void ReleaseShader()
{
	(*(Shader::GetInst()))->ReleaseShader();
}

EXTERN SYSTEM_DLL bool ShaderRender(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat)
{
	return (*(Shader::GetInst()))->Render(deviceContext, indexCount, worldMat, viewMat, projMat);
}

EXTERN SYSTEM_DLL bool ShaderRender2(ID3D11DeviceContext* deviceContext,XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat)
{
	return (*(Shader::GetInst()))->Render2(deviceContext, worldMat, viewMat, projMat);
}

EXTERN SYSTEM_DLL void SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat)
{
	(*(Shader::GetInst()))->SetMatrixShaderParameters(deviceContext, worldMat, viewMat, projMat);
}

EXTERN SYSTEM_DLL void SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower)
{
	(*(Shader::GetInst()))->SetLightShaderParameters(deviceContext, diffuseColor, ambientColor, lightDirection,specularColor, specularPower);
}

EXTERN SYSTEM_DLL void SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition)
{
	(*(Shader::GetInst()))->SetCameraShaderParameters(deviceContext, cameraPosition);

}

EXTERN SYSTEM_DLL void SetAmbientColor(XMFLOAT4 ambientColor)
{
	(*(Light::GetInst()))->SetAmbientColor(ambientColor);
}

EXTERN SYSTEM_DLL void SetDiffuseColor(XMFLOAT4 diffuseColor)
{
	(*(Light::GetInst()))->SetDiffuseColor(diffuseColor);
}

EXTERN SYSTEM_DLL void SetSpecularColor(XMFLOAT4 specularColor)
{
	(*(Light::GetInst()))->SetSpecularColor(specularColor);
}

EXTERN SYSTEM_DLL void SetLightDirection(XMFLOAT3 direction)
{
	(*(Light::GetInst()))->SetLightDirection(direction);
}

EXTERN SYSTEM_DLL void SetSpecularPower(float specularPower)
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
	(*(Shader::GetInst()))->DestroyInst();
	(*(D3DApp::GetInst()))->DestroyInst();
	(*(EditorCameraController::GetInst()))->DestroyInst();
	(*(Light::GetInst()))->DestroyInst();
}

