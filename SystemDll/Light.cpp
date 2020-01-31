#include "pch.h"
#include "Light.h"

void Light::SetAmbientColor(XMFLOAT4 ambientColor)
{
	mAmbientColor = ambientColor;
}

void Light::SetDiffuseColor(XMFLOAT4 diffuseColor)
{
	mDiffuseColor = diffuseColor;
}

void Light::SetSpecularColor(XMFLOAT4 specularColor)
{
	mSpecularColor = specularColor;
}

void Light::SetLightDirection(XMFLOAT3 direction)
{
	mDirection = direction;
}

void Light::SetSpecularPower(float specularPower)
{
	mSpecularPower = specularPower;
}

DirectX::XMFLOAT4 Light::GetAmbientColor()
{
	return mAmbientColor;
}

DirectX::XMFLOAT4 Light::GetDiffuseColor()
{
	return mDiffuseColor;
}

DirectX::XMFLOAT4 Light::GetSpecularColor()
{
	return mSpecularColor;
}

DirectX::XMFLOAT3 Light::GetLightDirection()
{
	return mDirection;
}

float Light::GetSpecularPower()
{
	return mSpecularPower;
}
