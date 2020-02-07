#include "pch.h"
#include "TextureUtil.h"
#include "../include/FreeImage.h"
#include <atlstr.h>

TextureUtil::TextureUtil()
{

}

TextureUtil::~TextureUtil()
{

}

ID3D11ShaderResourceView* TextureUtil::LoadTextureUtil(ID3D11Device* device, ID3D11DeviceContext* deviceContext, wstring fileName)
{
	FIBITMAP *dib(0);
	unsigned char* bits(0);
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	string path = converter.to_bytes(fileName.c_str());

	fif = FreeImage_GetFileType(path.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(path.c_str());

	if (fif == FIF_UNKNOWN)
		return nullptr;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, path.c_str());

	//if the image failed to load, return failure
	if (!dib)	return nullptr;

	//�̹��� ���°� 32 ��Ʈ�� �ƴϸ� 32�� ��ȯ. dx11�� 24 format �� ���� ���ϴ�..
	if (FreeImage_GetBPP(dib) != 32) {
		dib = FreeImage_ConvertTo32Bits(dib);
	}
	FreeImage_FlipVertical(dib);

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	unsigned int width = FreeImage_GetWidth(dib);
	unsigned int height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return nullptr;


	//�ؽ�ó�� ����ü�� �����մϴ�.
	D3D11_TEXTURE2D_DESC textureDesc;
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// �� �ؽ�ó�� �����մϴ�.
	ID3D11Texture2D*			texture = nullptr;
	HRESULT hResult = device->CreateTexture2D(&textureDesc, nullptr, &texture);
	if (FAILED(hResult)) {
		return nullptr;
	}

	//�̹��� ������
	UINT rowPitch = (width * 4) * sizeof(unsigned char);

	// �̹��� �����͸� �ؽ�ó�� �����մϴ�.
	deviceContext->UpdateSubresource(texture, 0, nullptr, bits, rowPitch, 0);

	// ���̴� ���ҽ� �� ����ü�� �����մϴ�.
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// �ؽ�ó�� ���̴� ���ҽ� �並 ����ϴ�.
	ID3D11ShaderResourceView* texData = nullptr;
	hResult = device->CreateShaderResourceView(texture, &srvDesc, &texData);
	if (FAILED(hResult)) {
		return nullptr;
	}

	// �� �ؽ�ó�� ���� �Ӹ��� �����մϴ�.
	deviceContext->GenerateMips(texData);

	texture->Release();
	FreeImage_Unload(dib);
	return texData;
}