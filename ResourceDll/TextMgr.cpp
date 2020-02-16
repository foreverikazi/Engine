#include "pch.h"
#include "TextMgr.h"
#include "SystemExportFunc.h"
#include "Shader.h"
#include "FontBuffer.h"

TextMgr::TextMgr() :
	mFontBuffer(nullptr)
{

}

TextMgr::~TextMgr()
{
	
}

bool TextMgr::AddFontBuffer(ID3D11Device* device, const TCHAR* fontFileName, const TCHAR* textureFileName)
{
	Shader* shader = GetShader(SHADERTYPE::FONT);
	if (shader == nullptr)
	{
		return false;
	}

	if (mFontBuffer)
	{
		SAFE_DELETE(mFontBuffer);
	}
	mFontBuffer = new FontBuffer();
	
	if (!mFontBuffer->LoadFontData(fontFileName) || !mFontBuffer->LoadTextureBuffer(device, textureFileName))
	{
		return false;
	}

	mFontBuffer->CreateBuffers(device);
	mFontBuffer->SetShader(shader);

	return true;
}

void TextMgr::SetText(ID3D11DeviceContext* deviceContext, const TCHAR* text, XMFLOAT2 position, const XMFLOAT4 color)
{
	if (mFontBuffer)
	{
		mFontBuffer->SetText(deviceContext, text, position, color);
	}
}

void TextMgr::SetFPSText(ID3D11DeviceContext* deviceContext, int fps, XMFLOAT2 position)
{
	XMFLOAT4 color;
	TCHAR strFps[64] = L"";
	wsprintf(strFps, L"FPS: %d", fps);

	if (60 <= fps)
	{
		color = XMFLOAT4(0, 1, 0, 1);
	}
	else if (30 <= fps && fps < 60)
	{
		color = XMFLOAT4(1, 1, 0, 1);
	}
	else if (fps < 30)
	{
		color = XMFLOAT4(1, 0, 0, 1);
	}

	mFontBuffer->SetText(deviceContext, strFps, position, color);
}

void TextMgr::RenderText(ID3D11DeviceContext* deviceContext)
{
	if (mFontBuffer)
	{
		mFontBuffer->RenderBuffers(deviceContext);
	}
}

void TextMgr::ReleaseText()
{
	if (mFontBuffer)
	{
		mFontBuffer->ReleaseBuffer();
	}
	SAFE_DELETE(mFontBuffer);
}

