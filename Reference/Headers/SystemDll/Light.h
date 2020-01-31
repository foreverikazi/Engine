#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL Light
{
	DECLARE_SINGLE(Light);
public :
	void SetAmbientColor(XMFLOAT4 ambientColor);
	void SetDiffuseColor(XMFLOAT4 diffuseColor);
	void SetSpecularColor(XMFLOAT4 specularColor);
	void SetLightDirection(XMFLOAT3 direction);
	void SetSpecularPower(float specularPower);

	XMFLOAT4 GetAmbientColor();
	XMFLOAT4 GetDiffuseColor();
	XMFLOAT4 GetSpecularColor();
	XMFLOAT3 GetLightDirection();
	float GetSpecularPower();

public :
	Light() = default;
	~Light() = default;

private :
	XMFLOAT4 mAmbientColor;
	XMFLOAT4 mDiffuseColor;
	XMFLOAT4 mSpecularColor;
	XMFLOAT3 mDirection;
	float	 mSpecularPower;
};

