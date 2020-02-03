#pragma once

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
};

struct ColorVertex
{
	XMFLOAT3 position;
	XMFLOAT4 color;
};

struct Texture
{
	ID3D11ShaderResourceView *textureRV;
	wstring type;
	wstring path;
};

struct Material
{
	wstring name = L"";

	Texture* diffuseMap = NULL;
	Texture* alphaMap = NULL;
	Texture* normalMap = NULL;
	Texture* sepcularMap = NULL;
	Texture* lightMap = NULL;
};


