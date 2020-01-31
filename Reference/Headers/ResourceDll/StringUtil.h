#pragma once
#define RESOURCE_EXPORT
#include "ResourceDef.h"


EXTERN class RESOURCE_DLL StringUtil
{
	DECLARE_SINGLE(StringUtil);

public :
	CString GetFileName(CString path);
	CString GetDirectoryPath(CString path);
};

