#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"

EXTERN class SYSTEM_DLL Light
{
	DECLARE_SINGLE(Light);
public :
	void SetAmbientColor(const XMFLOAT4 ambientColor);
	void SetDiffuseColor(const XMFLOAT4 diffuseColor);
	void SetSpecularColor(const XMFLOAT4 specularColor);
	void SetLightDirection(const XMFLOAT3 direction);
	void SetSpecularPower(const float specularPower);

	XMFLOAT4 GetAmbientColor() const;
	XMFLOAT4 GetDiffuseColor() const;
	XMFLOAT4 GetSpecularColor() const;
	XMFLOAT3 GetLightDirection() const;
	float GetSpecularPower() const;

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

