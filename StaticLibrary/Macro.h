#pragma once
#define DECLARE_SINGLE(type)	\
public:\
	static type** GetInst(void)\
	{\
	static type* pInst = new type;\
	if(pInst == nullptr)\
	pInst = new type;\
	return &pInst;\
	}\
	void DestroyInst(void)\
	{\
	type** ppInst = GetInst();\
	if(ppInst != nullptr)\
		{\
		delete *ppInst;\
		*ppInst = nullptr;\
		}\
	}

#define SAFE_RELEASE(p) { if ( (p) ) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(a) if( (a) != nullptr ) delete (a); (a) = nullptr;
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }