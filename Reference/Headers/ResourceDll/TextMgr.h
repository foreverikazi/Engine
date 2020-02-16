#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"

class FontBuffer;
EXTERN class RESOURCE_DLL TextMgr
{
	DECLARE_SINGLE(TextMgr);
public :
	bool AddFontBuffer(ID3D11Device* device, const TCHAR* fontFileName, const TCHAR* textureFileName);
	void SetText(ID3D11DeviceContext* deviceContext, const TCHAR* text, XMFLOAT2 position, const XMFLOAT4 color);
	void SetFPSText(ID3D11DeviceContext* deviceContext, int fps, XMFLOAT2 position);
	void RenderText(ID3D11DeviceContext* deviceContext);
	void ReleaseText();

public :
	TextMgr();
	~TextMgr();

private :
	FontBuffer* mFontBuffer;


};

