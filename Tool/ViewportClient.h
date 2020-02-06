#pragma once

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_FAR = 1000.0f;
const float SCREEN_NEAR = 0.1f;

// ViewportClient 폼 보기

class ViewportClient : public CFormView
{
	DECLARE_DYNCREATE(ViewportClient)
private :
	HWND mHwnd;
	HINSTANCE mHinstance;
	int mScreenWidth;
	int mScreenHeight;

protected:
	ViewportClient();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ViewportClient();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIEWPORT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public :
	virtual void OnDraw(CDC* pDC);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate();
	DECLARE_MESSAGE_MAP()

private :
	void InitCamera();
	void InitShader();
	void InitBuffers();
	void InitModel();
	void InitLight();
	void UpdateShader(ID3D11DeviceContext* deviceContext);
};


