#include "pch.h"
#include "StringUtil.h"
#include <filesystem>

namespace fs = std::experimental::filesystem::v1;
CString StringUtil::GetFileName(CString path)
{
	int index = path.ReverseFind('\\') + 1;

	if (index == 0) {
		index = path.ReverseFind('/') + 1;
	}

	CString name = path.Right(path.GetLength() - index);

	return name;
}

CString StringUtil::GetDirectoryPath(CString path)
{
	int index = path.ReverseFind('\\') + 1;

	if (index == 0) {
		index = path.ReverseFind('/') + 1;
	}

	CString dirPath = path.Left(index);

	return dirPath;
}
