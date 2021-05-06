#include "..\..\Header\Util\Timer.h"
#include <stdio.h>
#pragma comment(lib,"winmm.lib")

GatesEngine::Util::Timer::Timer() :isShow(true), fps(0), frameTime(0), timeStart({}), timeEnd({}), timeFreq({})
{
	QueryPerformanceFrequency(&timeFreq);
	QueryPerformanceCounter(&timeStart);
}

GatesEngine::Util::Timer::~Timer()
{
}

void GatesEngine::Util::Timer::SetIsShow(bool b)
{
	isShow = b;
}

float GatesEngine::Util::Timer::GetElapsedTime()
{
	return (float)frameTime;
}

bool GatesEngine::Util::Timer::Wait(const float setFrameRate)
{
	const float SET_FRAME_TIME = 1.0f / setFrameRate;
	QueryPerformanceCounter(&timeEnd);
	frameTime = static_cast<double>(timeEnd.QuadPart - timeStart.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	if (frameTime < SET_FRAME_TIME)
	{
		//Sleep‚ÌŽžŠÔ‚ðŒvŽZ
		DWORD sleepTime = static_cast<DWORD>((SET_FRAME_TIME - frameTime) * 1000);
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);
		return true;
	}
	timeStart = timeEnd;
	fps = 1.0f / frameTime;
	if (isShow)printf("%3.3ffps\n", fps);
	return false;
}

void GatesEngine::Util::Timer::Start()
{
	QueryPerformanceCounter(&startBuffer);
}

void GatesEngine::Util::Timer::End(bool isShow, const char * addComment)
{
	QueryPerformanceCounter(&endBuffer);
	double elapsedTime = static_cast<double>(endBuffer.QuadPart - startBuffer.QuadPart) / static_cast<double>(timeFreq.QuadPart);
	if (isShow)printf("%3.5fms : %s\n", elapsedTime * 1000, addComment);
}
