#include "stdafx.h"
#include "cTimer.h"
#include <MMSystem.h>

#pragma comment (lib, "winmm.lib")

cTimer::cTimer()
	: m_bIsHardware(false)
	, m_fTimeScale(0.0f)
	, m_fTimeElapsed(0.0f)
	, m_nCurTime(0)
	, m_nLastTime(0)
	, m_nPeriodFrequency(0)
	, m_lFrameRate(0)
	, m_lFPSFrameCount(0)
	, m_fFPSTimeElapsed(0.0f)
	, m_fWorldTime(0.0f)
{
}


cTimer::~cTimer()
{
}


HRESULT cTimer::Setup()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&m_nPeriodFrequency))
	{
		m_bIsHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nLastTime);

		m_fTimeScale = 1.0f / m_nPeriodFrequency;
	}
	else
	{
		m_bIsHardware = false;
		m_nLastTime = timeGetTime();
		m_fTimeScale = 0.001f;
	}

	return S_OK;
}


void cTimer::Tick(float lockFPS)
{
	if (m_bIsHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&m_nCurTime);
	else
		m_nCurTime = timeGetTime();

	m_fTimeElapsed = (m_nCurTime - m_nLastTime) * m_fTimeScale;

	if (lockFPS > 0.0f)
	{
		while (m_fTimeElapsed < (1.0f / lockFPS))
		{
			if (m_bIsHardware) QueryPerformanceCounter((LARGE_INTEGER*)& m_nCurTime);
			else m_nCurTime = timeGetTime();

			m_fTimeElapsed = (m_nCurTime - m_nLastTime) * m_fTimeScale;
		}
	}

	m_nLastTime = m_nCurTime;

	m_lFPSFrameCount++;

	m_fFPSTimeElapsed += m_fTimeElapsed;

	m_fWorldTime += m_fTimeElapsed;

	if (m_fFPSTimeElapsed > 1.0f)
	{
		m_lFrameRate = m_lFPSFrameCount;
		m_lFPSFrameCount = 0;
		m_fFPSTimeElapsed = 0.0f;
	}
}