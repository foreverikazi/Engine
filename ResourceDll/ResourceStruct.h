#pragma once

struct WorldInfo
{
	XMFLOAT3 scale;
	XMFLOAT3 rotation;
	XMFLOAT3 position;
	XMMATRIX worldMat;

	WorldInfo(XMFLOAT3 _scale, XMFLOAT3 _rotation, XMFLOAT3 _position, XMMATRIX _worldMat)
	{
		scale = _scale;
		rotation = _rotation;
		position = _position;
		worldMat = _worldMat;
	}
};

struct Vertex
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
	XMFLOAT3 normal;
};

struct TextureVertex
{
	XMFLOAT3 position;
	XMFLOAT2 uv;
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


