#include "pch.h"
#include "TimeMgr.h"

TimeMgr::TimeMgr()
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
}