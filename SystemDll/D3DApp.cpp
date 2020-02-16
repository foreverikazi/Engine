#include "pch.h"
#include "D3DApp.h"

D3DApp::D3DApp() : 
	mVsyncEnabled(false),
	mVideoCardMemory(0),
	mSwapChain(nullptr),
	mDevice(nullptr),
	mDeviceContext(nullptr),
	mRenderTargetView(nullptr),
	mDepthStencilBuffer(nullptr),
	mDepthStencilState(nullptr),
	mDepthDisabledStencilState(nullptr),
	mRasterState(nullptr),
	mDepthStencilView(nullptr),
	mAlphaEnableBlendingState(nullptr),
	mAlphaDisableBlendingState(nullptr),
	mOrthoMatrix(XMMatrixIdentity())
{
	ZeroMemory(mVideoCardDescription, sizeof(mVideoCardDescription));
}

D3DApp::~D3DApp()
{
}


bool D3DApp::InitializeD3D(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
	float screenDepth, float screenNear)
{
	mVsyncEnabled = vsync;

	IDXGIFactory* factory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory)))
	{
		return false;
	}

	IDXGIAdapter* adapter = nullptr;
	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		return false;
	}

	IDXGIOutput* adapterOutput = nullptr;
	if (FAILED(adapter->EnumOutputs(0, &adapterOutput)))
	{
		return false;
	}

	unsigned int numModes = 0;
	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL)))
	{
		return false;
	}

	DXGI_MODE_DESC* displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		return false;
	}

	if (FAILED(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList)))
	{
		return false;
	}

	unsigned int numerator = 0;
	unsigned int denominator = 0;
	for (unsigned int i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if (displayModeList[i].Height == (unsigned int)screenHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	if (FAILED(adapter->GetDesc(&adapterDesc)))
	{
		return false;
	}

	mVideoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	if (wcstombs_s(&stringLength, mVideoCardDescription, 128, adapterDesc.Description, 128) != 0)
	{
		return false;
	}

	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = 0;

	adapter->Release();
	adapter = 0;

	factory->Release();
	factory = 0;

#pragma region 스왑체인
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 1;

	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (mVsyncEnabled)
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	if (fullscreen)
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain, &mDevice, NULL, &mDeviceContext)))
	{
		return false;
	}

	ID3D11Texture2D* backBufferPtr = nullptr;
	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr)))
	{
		return false;
	}

	if (FAILED(mDevice->CreateRenderTargetView(backBufferPtr, NULL, &mRenderTargetView)))
	{
		return false;
	}

	backBufferPtr->Release();
	backBufferPtr = 0;
#pragma endregion

	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	if (FAILED(mDevice->CreateTexture2D(&depthBufferDesc, NULL, &mDepthStencilBuffer)))
	{
		return false;
	}

#pragma region 뎁스 스텐실
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	if (FAILED(mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState)))
	{
		return false;
	}

	depthStencilDesc.DepthEnable = false;

	if (FAILED(mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthDisabledStencilState)))
	{
		return false;
	}

	mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 0x1);
	
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer, &depthStencilViewDesc, &mDepthStencilView)))
	{
		return false;
	}
	
	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
#pragma endregion

#pragma region 블렌드
	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(D3D11_BLEND_DESC));

	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	if (FAILED(mDevice->CreateBlendState(&blendStateDescription, &mAlphaEnableBlendingState)))
	{
		return false;
	}

	blendStateDescription.RenderTarget[0].BlendEnable = FALSE;
	if (FAILED(mDevice->CreateBlendState(&blendStateDescription, &mAlphaDisableBlendingState)))
	{
		return false;
	}

#pragma endregion

#pragma region 레스터라이즈
	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(mDevice->CreateRasterizerState(&rasterDesc, &mRasterState)))
	{
		return false;
	}
	mDeviceContext->RSSetState(mRasterState);

#pragma endregion

	D3D11_VIEWPORT viewport;
	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	mDeviceContext->RSSetViewports(1, &viewport);

	mOrthoMatrix = XMMatrixOrthographicLH((float)screenWidth, (float)screenHeight, screenNear, screenDepth);

	return true;
}


void D3DApp::Release3D()
{
	// 종료 전 윈도우 모드로 설정하지 않으면 스왑 체인을 해제 할 때 예외가 발생합니다.
	if (mSwapChain)
	{
		mSwapChain->SetFullscreenState(false, NULL);
	}
	SAFE_RELEASE(mAlphaEnableBlendingState);
	SAFE_RELEASE(mAlphaDisableBlendingState);
	SAFE_RELEASE(mRasterState);
	SAFE_RELEASE(mDepthStencilView);
	SAFE_RELEASE(mDepthStencilState);
	SAFE_RELEASE(mDepthDisabledStencilState);
	SAFE_RELEASE(mDepthStencilBuffer);
	SAFE_RELEASE(mRenderTargetView);
	SAFE_RELEASE(mDeviceContext);
	SAFE_RELEASE(mDevice);
	SAFE_RELEASE(mSwapChain);
}


void D3DApp::BeginScene(const float r, const float g, const float b, const float a)
{
	float fColor[4] = { r, g, b, a };
	
	mDeviceContext->ClearRenderTargetView(mRenderTargetView, fColor);
	mDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}


void D3DApp::EndScene()
{
	if (mVsyncEnabled)
	{
		mSwapChain->Present(1, 0);
	}
	else
	{
		mSwapChain->Present(0, 0);
	}
}

ID3D11Device* D3DApp::GetDevice()
{
	return mDevice;
}

ID3D11DeviceContext* D3DApp::GetDeviceContext()
{
	return mDeviceContext;
}

XMMATRIX D3DApp::GetOrthoMatrix() const
{
	return mOrthoMatrix;
}

void D3DApp::GetVideoCardInfo(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, mVideoCardDescription);
	memory = mVideoCardMemory;
}

void D3DApp::SetFrontCounterClockwise(const bool clockwise)
{
	D3D11_RASTERIZER_DESC rasterDesc;
	if (mRasterState)
	{
		mRasterState->GetDesc(&rasterDesc);
		rasterDesc.FrontCounterClockwise = clockwise;
	}
	
	if (mDevice)
	{
		mDevice->CreateRasterizerState(&rasterDesc, &mRasterState);
	}
}

void D3DApp::SetCullMode(const D3D11_CULL_MODE cullMode)
{
	D3D11_RASTERIZER_DESC rasterDesc;
	if (mRasterState)
	{
		mRasterState->GetDesc(&rasterDesc);
		rasterDesc.CullMode = cullMode;
	}

	if (mDevice)
	{
		mDevice->CreateRasterizerState(&rasterDesc, &mRasterState);
		mDeviceContext->RSSetState(mRasterState);
	}
}

void D3DApp::SetFillMode(const D3D11_FILL_MODE fillMode)
{
	D3D11_RASTERIZER_DESC rasterDesc;
	if (mRasterState)
	{
		mRasterState->GetDesc(&rasterDesc);
		rasterDesc.FillMode = fillMode;
	}

	if (mDevice)
	{
		mDevice->CreateRasterizerState(&rasterDesc, &mRasterState);
		mDeviceContext->RSSetState(mRasterState);
	}
}

void D3DApp::SetDepthFunc(const D3D11_COMPARISON_FUNC compFunc)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	if (mDepthStencilState)
	{
		mDepthStencilState->GetDesc(&depthStencilDesc);
		depthStencilDesc.DepthFunc = compFunc;
	}

	if (mDevice)
	{
		mDevice->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState);
		mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 0x1);
	}
}

void D3DApp::TurnOffZBuffer()
{
	mDeviceContext->OMSetDepthStencilState(mDepthDisabledStencilState, 0x1);
}

void D3DApp::TurnOnZBuffer()
{
	mDeviceContext->OMSetDepthStencilState(mDepthStencilState, 0x1);
}

void D3DApp::TurnOffAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	mDeviceContext->OMSetBlendState(mAlphaDisableBlendingState, blendFactor, 0xffffffff);
}

void D3DApp::TurnOnAlphaBlending()
{
	float blendFactor[4];

	blendFactor[0] = 0.0f;
	blendFactor[1] = 0.0f;
	blendFactor[2] = 0.0f;
	blendFactor[3] = 0.0f;

	mDeviceContext->OMSetBlendState(mAlphaEnableBlendingState, blendFactor, 0xffffffff);
}
