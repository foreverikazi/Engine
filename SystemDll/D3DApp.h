#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL D3DApp
{
	DECLARE_SINGLE(D3DApp);
public:
	D3DApp();
	~D3DApp();

	bool InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,float screenDepth, float screenNear);
	void Release3D();

	void BeginScene(const float r, const float g, const float b, const float a);
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();

	XMMATRIX GetOrthoMatrix() const;

	void GetVideoCardInfo(char*, int&);

	// 설정 빈도가 높아지면 상태를 미리 만들어놓고 써야할 것 같다
	void SetFrontCounterClockwise(const bool clockwise);
	void SetCullMode(const D3D11_CULL_MODE cullMode);
	void SetFillMode(const D3D11_FILL_MODE fillMode);
	void SetDepthFunc(const D3D11_COMPARISON_FUNC compFunc);

	void TurnOffZBuffer();
	void TurnOnZBuffer();
	void TurnOffAlphaBlending();
	void TurnOnAlphaBlending();

private:
	bool mVsyncEnabled;
	int mVideoCardMemory;
	char mVideoCardDescription[128];
	IDXGISwapChain* mSwapChain;
	ID3D11Device* mDevice;
	ID3D11DeviceContext* mDeviceContext;
	ID3D11RenderTargetView* mRenderTargetView;
	ID3D11Texture2D* mDepthStencilBuffer;
	ID3D11DepthStencilState* mDepthStencilState;
	ID3D11DepthStencilState* mDepthDisabledStencilState;
	ID3D11DepthStencilView* mDepthStencilView;
	ID3D11RasterizerState* mRasterState;
	ID3D11BlendState* mAlphaEnableBlendingState;
	ID3D11BlendState* mAlphaDisableBlendingState;
	XMMATRIX mOrthoMatrix;
};

