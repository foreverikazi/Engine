#pragma once

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_FAR = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class SceneView
{
public:
	SceneView();
	SceneView(const SceneView&);
	~SceneView();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	//D3DClass* m_Direct3D = nullptr;
	//CameraController* m_Camera = nullptr;
	//ModelClass* m_Model = nullptr;
	//TextureShaderClass* m_TextureShader = nullptr;
};