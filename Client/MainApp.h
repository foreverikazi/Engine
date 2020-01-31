#pragma once

class SceneView;
class MainApp
{
public:
	MainApp();
	MainApp(const MainApp&);
	~MainApp();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	SceneView* mSceneView;
	//InputClass* m_Input = nullptr;
	//GraphicsClass* m_Graphics = nullptr;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static MainApp* ApplicationHandle = 0;