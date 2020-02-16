#pragma once

template <typename T, typename T1>
class CFactory
{
public:
	static T* CreateObject(void)
	{
		T* pObject = new T1;
		pObject->Initialize();
		return pObject;
	}
public:
	CFactory(void) {}
	~CFactory(void) {}
};
