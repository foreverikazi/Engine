#pragma once
#define SYSTEM_EXPORT
#include "SystemDef.h"
#include "chrono"

EXTERN class SYSTEM_DLL TimeMgr
{
	DECLARE_SINGLE(TimeMgr);
public :
	void InitializeTimer();
	void UpdateTimer();
	float GetElapsedTime();
	int GetFPS();

public:
	TimeMgr();
	~TimeMgr();
private :
	chrono::steady_clock::time_point mStartTime;
	chrono::steady_clock::time_point mPrevTime;
	chrono::steady_clock::time_point mCurrentTime;
	chrono::duration<float> mElapsedTime;


	float	mAccumulateTime;
	int		mFPS;
	int		mFrameCount;
};

