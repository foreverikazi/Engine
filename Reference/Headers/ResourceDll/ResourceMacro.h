#pragma once
#ifdef _cplusplus
#define EXTERN extern "C"
#else
#define EXTERN 
#endif

#ifdef RESOURCE_EXPORT
#define RESOURCE_DLL _declspec(dllexport)
#else
#define RESOURCE_DLL _declspec(dllimport)
#endif
