#pragma once
#define DECLARE_SINGLE(type)	\
public:\
	static type** GetInst(void)\
	{\
	static type* pInst = new type;\
	if(pInst == NULL)\
	pInst = new type;\
	return &pInst;\
	}\
	void DestroyInst(void)\
	{\
	type** ppInst = GetInst();\
	if(ppInst != NULL)\
		{\
		delete *ppInst;\
		*ppInst = NULL;\
		}\
	}