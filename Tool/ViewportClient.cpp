// ViewportClient.cpp: 구현 파일
//

#include "pch.h"
#include "Tool.h"
#include "ViewportClient.h"
#include "SystemExportFunc.h"
#include "ResourceExportFunc.h"
#include <filesystem>



// ViewportClient
namespace fs = std::experimental::filesystem::v1;

IMPLEMENT_DYNCREATE(ViewportClient, CFormView)

ViewportClient::ViewportClient()
	: CFormView(IDD_VIEWPORT),
	mScreenWidth(1600),
	mScreenHeight(600)
{

}

ViewportClient::~ViewportClient()
{
	ReleaseModel();
	ReleaseShader();
	ReleaseBuffers();
	Release3D();

	ReleaseResource();
	ReleaseSystem();
}

void ViewportClient::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ViewportClient, CFormView)
END_MESSAGE_MAP()


// ViewportClient 진단

#ifdef _DEBUG
void ViewportClient::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ViewportClient::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
void ViewportClient::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	
	mHwnd = m_hWnd; 
	mHinstance = AfxGetInstanceHandle();

	InitializeD3D(mScreenWidth, mScreenHeight, VSYNC_ENABLED, mHwnd, FULL_SCREEN, SCREEN_FAR, SCREEN_NEAR);
	InitializeInput(mHinstance, AfxGetMainWnd()->m_hWnd);
	InitCamera();
	InitializeTimer();
	InitShader();
	InitBuffers();
	//InitModel();
	//InitLight();
}

void ViewportClient::OnDraw(CDC* pDC)
{
	ID3D11DeviceContext* deviceContext = GetDeviceContext();
	BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	UpdateCamera();
	UpdateInput();
	UpdateTimer();
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	GetWorldMatrix(worldMatrix);
	viewMatrix = GetViewMatrix();
	projectionMatrix = GetProjectionMatrix();
	SetMatrixShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	
	/*
	SetLightShaderParameters(deviceContext, GetAmbientColor(), GetDiffuseColor(), GetLightDirection(), GetSpecularColor(), GetSpecularPower());
	SetCameraShaderParameters(deviceContext, GetCameraPosition());
	*/

	SetShader(deviceContext);
	RenderBuffers(deviceContext);

	/*
	ModelRender(deviceContext);
	ShaderRender(GetDeviceContext(), GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	*/

	Invalidate(false); 
	EndScene();
}


#endif
#endif //_DEBUG

// ViewportClient 메시지 처리기

void ViewportClient::InitCamera()
{
	float fieldOfView = XM_PI / 4.0f;
	float screenAspect = (float)mScreenWidth / (float)mScreenHeight;
	InitializeProjectionMatrix(fieldOfView, screenAspect, SCREEN_NEAR, SCREEN_FAR);
	//SetCameraPosition(XMFLOAT3(0.0f, 1.0f, -20.0f));
	InitializeCamera(XMFLOAT3(0, 1, 0), XMFLOAT3(0, 0, 1), XMFLOAT3(0, 0, -10));
	SetCameraRotation(XMFLOAT3(0, 0, 0));
	//SetCameraRotation(XMFLOAT3(90, 0, 180));
}

void ViewportClient::InitShader()
{
	ID3D11Device* device = GetDevice();

	WCHAR vs[] = L"../Shader/color.vs";
	WCHAR ps[] = L"../Shader/color.ps";
	//WCHAR vs[] = L"../Shader/light.vs";
	//WCHAR ps[] = L"../Shader/light.ps";
	InitializeShader(device, mHwnd, vs, ps, SHADERBUFFERTYPE::CUBE);
}

void ViewportClient::InitBuffers()
{
	AddBuffer(GetDevice(), BUFFERTYPE::BUFFERTYPE_CUBE);
}

void ViewportClient::InitModel()
{
	ID3D11Device* device = GetDevice();
	ID3D11DeviceContext* deviceContext = GetDeviceContext();

	fs::path contentPolderPath = fs::current_path().parent_path() /= "Content";
	wstring strPath = contentPolderPath.c_str();

	//LoadModel(device, deviceContext, strPath + L"\\Weapon\\Sword.FBX");
	LoadModel(device, deviceContext, strPath + L"\\Weapon\\Alisa.fbx");
}

void ViewportClient::InitLight()
{
	SetAmbientColor(XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f));
	SetDiffuseColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	SetSpecularColor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	SetLightDirection(XMFLOAT3(0.0f, 1.0f, -1.0f));
	SetSpecularPower(32.0f);
}
