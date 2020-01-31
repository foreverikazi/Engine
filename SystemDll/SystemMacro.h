#pragma once
#ifndef _SYSTEMMACRO_H
#define _SYSTEMMACRO_H

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


#ifdef _cplusplus
#define EXTERN extern "C"
#else
#define EXTERN 
#endif

#ifdef SYSTEM_EXPORT
#define SYSTEM_DLL _declspec(dllexport)
#else
#define SYSTEM_DLL _declspec(dllimport)
#endif

#endif _SYSTEMMACRO_H
