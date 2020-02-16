#pragma once
#ifndef _SYSTEMMACRO_H
#define _SYSTEMMACRO_H

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
