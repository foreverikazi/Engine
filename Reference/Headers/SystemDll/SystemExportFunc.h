#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
class Shader;

// D3DApp
EXTERN SYSTEM_DLL bool InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen, float screenDepth, float screenNear);
EXTERN SYSTEM_DLL void Release3D();
EXTERN SYSTEM_DLL void BeginScene(const float r, const float g, const float b, const float a);
EXTERN SYSTEM_DLL void EndScene();
EXTERN SYSTEM_DLL ID3D11Device* GetDevice();
EXTERN SYSTEM_DLL ID3D11DeviceContext* GetDeviceContext();
EXTERN SYSTEM_DLL void GetWorldMatrix(XMMATRIX& worldMatrix);
EXTERN SYSTEM_DLL void SetFrontCounterClockwise(const bool clockwise);
EXTERN SYSTEM_DLL void SetCullMode(const D3D11_CULL_MODE cullMode);
EXTERN SYSTEM_DLL void SetFillMode(const D3D11_FILL_MODE fillMode);
EXTERN SYSTEM_DLL void SetDepthFunc(const D3D11_COMPARISON_FUNC compFunc);

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
EXTERN SYSTEM_DLL float GetElapsedTime();
// Shader
EXTERN SYSTEM_DLL bool InitializeShader(ID3D11Device* device, HWND hwnd, const TCHAR* vsFilename, const TCHAR* psFilename, const SHADERTYPE type);
EXTERN SYSTEM_DLL void ReleaseShader();
EXTERN SYSTEM_DLL Shader* GetShader(const SHADERTYPE type);

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