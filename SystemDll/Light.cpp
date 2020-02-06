#include "pch.h"
#include "Light.h"

void Light::SetAmbientColor(const XMFLOAT4 ambientColor)
{
	mAmbientColor = ambientColor;
}

void Light::SetDiffuseColor(const XMFLOAT4 diffuseColor)
{
	mDiffuseColor = diffuseColor;
}

void Light::SetSpecularColor(const XMFLOAT4 specularColor)
{
	mSpecularColor = specularColor;
}

void Light::SetLightDirection(const XMFLOAT3 direction)
{
	mDirection = direction;
}

void Light::SetSpecularPower(const float specularPower)
{
	mSpecularPower = specularPower;
}

DirectX::XMFLOAT4 Light::GetAmbientColor() const
{
	return mAmbientColor;
}

DirectX::XMFLOAT4 Light::GetDiffuseColor() const
{
	return mDiffuseColor;
}

DirectX::XMFLOAT4 Light::GetSpecularColor() const
{
	return mSpecularColor;
}

DirectX::XMFLOAT3 Light::GetLightDirection() const
{
	return mDirection;
}

float Light::GetSpecularPower() const
{
	return mSpecularPower;
}
