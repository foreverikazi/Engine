#include "pch.h"
#include "TimeMgr.h"

TimeMgr::TimeMgr() :
	mAccumulateTime(0.f),
	mFrameCount(0),
	mFPS(0)
{

}

TimeMgr::~TimeMgr()
{

}

void TimeMgr::InitializeTimer()
{
	mStartTime = chrono::high_resolution_clock::now();
	mPrevTime = chrono::high_resolution_clock::now();
}

void TimeMgr::UpdateTimer()
{
	mCurrentTime = chrono::high_resolution_clock::now();
	mElapsedTime = mCurrentTime - mPrevTime;
	mPrevTime = mCurrentTime;

	mAccumulateTime += mElapsedTime.count();
	mFrameCount++;

	if (mAccumulateTime >= 1.0f)
	{
		mFPS = mFrameCount;
		mFrameCount = 0;
		mAccumulateTime = 0;
	}
}

float TimeMgr::GetElapsedTime()
{
	return mElapsedTime.count();
}

int TimeMgr::GetFPS()
{
	return mFPS;
}
