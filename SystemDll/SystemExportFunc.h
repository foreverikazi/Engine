#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

// D3DApp
EXTERN SYSTEM_DLL bool InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
EXTERN SYSTEM_DLL void Release3D();
EXTERN SYSTEM_DLL void BeginScene(float red, float green, float blue, float alpha);
EXTERN SYSTEM_DLL void EndScene();
EXTERN SYSTEM_DLL ID3D11Device* GetDevice();
EXTERN SYSTEM_DLL ID3D11DeviceContext* GetDeviceContext();
EXTERN SYSTEM_DLL void GetWorldMatrix(XMMATRIX& worldMatrix);

// Camera
EXTERN SYSTEM_DLL void InitializeCamera(const XMFLOAT3 up, const XMFLOAT3 look, const XMFLOAT3 position);
EXTERN SYSTEM_DLL void InitializeProjectionMatrix(const float fov, const float aspectRatio, const float nearZ, const float farZ);
EXTERN SYSTEM_DLL void SetCameraPosition(const XMFLOAT3 position);
EXTERN SYSTEM_DLL void SetCameraRotation(const XMFLOAT3 rotation);
EXTERN SYSTEM_DLL XMFLOAT3 GetCameraPosition();
EXTERN SYSTEM_DLL XMFLOAT3 GetCameraRotation();
EXTERN SYSTEM_DLL void UpdateCamera();
EXTERN SYSTEM_DLL XMMATRIX GetViewMatrix();
EXTERN SYSTEM_DLL XMMATRIX GetProjectionMatrix();

// Input
EXTERN SYSTEM_DLL bool InitializeInput(HINSTANCE hinstance, HWND hwnd);
EXTERN SYSTEM_DLL void UpdateInput();
EXTERN SYSTEM_DLL BOOL GetKeyBoardState(BYTE keyID);
EXTERN SYSTEM_DLL const DIMOUSESTATE* GetMouseState();

// Timer
EXTERN SYSTEM_DLL void InitializeTimer();
EXTERN SYSTEM_DLL void UpdateTimer();

// Shader
EXTERN SYSTEM_DLL bool InitializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename, SHADERBUFFERTYPE type);
EXTERN SYSTEM_DLL void ReleaseShader();
EXTERN SYSTEM_DLL bool SetShader(ID3D11DeviceContext* deviceContext);
EXTERN SYSTEM_DLL void SetMatrixShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMat, XMMATRIX viewMat, XMMATRIX projMat);
EXTERN SYSTEM_DLL void SetLightShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, XMFLOAT4 specularColor, float specularPower);
EXTERN SYSTEM_DLL void SetCameraShaderParameters(ID3D11DeviceContext* deviceContext, XMFLOAT3 cameraPosition);

// Light
EXTERN SYSTEM_DLL void SetAmbientColor(const XMFLOAT4 ambientColor);
EXTERN SYSTEM_DLL void SetDiffuseColor(const XMFLOAT4 diffuseColor);
EXTERN SYSTEM_DLL void SetSpecularColor(const XMFLOAT4 specularColor);
EXTERN SYSTEM_DLL void SetLightDirection(const XMFLOAT3 direction);
EXTERN SYSTEM_DLL void SetSpecularPower(const float specularPower);

EXTERN SYSTEM_DLL XMFLOAT4 GetAmbientColor();
EXTERN SYSTEM_DLL XMFLOAT4 GetDiffuseColor();
EXTERN SYSTEM_DLL XMFLOAT4 GetSpecularColor();
EXTERN SYSTEM_DLL XMFLOAT3 GetLightDirection();
EXTERN SYSTEM_DLL float GetSpecularPower();

// System
EXTERN SYSTEM_DLL void ReleaseSystem();