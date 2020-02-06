#include "pch.h"
#include "SceneView.h"
#include "SystemExportFunc.h"
#include "ResourceExportFunc.h"

SceneView::SceneView()
{
}


SceneView::SceneView(const SceneView& other)
{
}


SceneView::~SceneView()
{
}

bool SceneView::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	InitializeD3D(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	
	// Direct3D 객체 생성
	//m_Direct3D = new D3DClass;
	//if (!m_Direct3D)
	//{
	//	return false;
	//}

	//// Direct3D 객체 초기화
	//if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	//{
	//	MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
	//	return false;
	//}

	//// m_Camera 객체 생성
	//if (!m_Camera)
	//{
	//	return false;
	//}

	//// 카메라 포지션 설정
	SetCameraPosition(XMFLOAT3(0.0f, 0.0f, -5.50f));
	//m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	//// m_Model 객체 생성
	//m_Model = new ModelClass;
	//if (!m_Model)
	//{
	//	return false;
	//}
	//AddBuffer(GetDevice());
	//// m_Model 객체 초기화
	//if (!m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Dx11Demo_05/data/stone01.tga"))
	//{
	//	MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
	//	return false;
	//}

	//// m_TextureShader 객체 생성
	//m_TextureShader = new TextureShaderClass;
	//if (!m_TextureShader)
	//{
	//	return false;
	//}
	//WCHAR vs[] = L"../Shader/color.vs";
	//WCHAR ps[] = L"../Shader/color.ps";
	//WCHAR vs[] = L"../Shader/Shader.vs";
	//WCHAR ps[] = L"../Shader/texture.ps";
	//InitializeShader(GetDevice(), hwnd, vs, ps);
	//// m_TextureShader 객체 초기화
	//if (!m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	//{
	//	MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
	//	return false;
	//}

	return true;
}


void SceneView::Shutdown()
{
	ReleaseShader();
	// m_TextureShader 객체 반환
	//if (m_TextureShader)
	//{
	//	m_TextureShader->Shutdown();
	//	delete m_TextureShader;
	//	m_TextureShader = 0;
	//}

	//// m_Model 객체 반환
	//if (m_Model)
	//{
	//	m_Model->Shutdown();
	//	delete m_Model;
	//	m_Model = 0;
	//}
	ReleaseBuffers();
	
	//// m_Camera 객체 반환
	//if (m_Camera)
	//{
	//	delete m_Camera;
	//	m_Camera = 0;
	//}
	Release3D();
	//// Direct3D 객체 반환
	//if (m_Direct3D)
	//{
	//	m_Direct3D->Shutdown();
	//	delete m_Direct3D;
	//	m_Direct3D = 0;
	//}
}


bool SceneView::Frame()
{
	// 그래픽 랜더링 처리
	return Render();
}


bool SceneView::Render()
{
	BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	UpdateCamera();

	//// 카메라 및 d3d 객체에서 월드, 뷰 및 투영 행렬을 가져옵니다
	//XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	//m_Direct3D->GetWorldMatrix(worldMatrix);
	//m_Camera->GetViewMatrix(viewMatrix);
	//m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
	//m_Model->Render(m_Direct3D->GetDeviceContext());
	RenderBuffers(GetDeviceContext());
	//// 텍스쳐 쉐이더를 사용하여 모델을 렌더링합니다.
	//if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture()))
	//{
	//	return false;
	//}
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	GetWorldMatrix(worldMatrix);
	viewMatrix = GetViewMatrix();
	projectionMatrix = GetProjectionMatrix();

	//ShaderRender(GetDeviceContext(), GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//// 버퍼의 내용을 화면에 출력합니다
	//m_Direct3D->EndScene();
	EndScene();
	return true;
}