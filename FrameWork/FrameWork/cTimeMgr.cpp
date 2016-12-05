#include "stdafx.h"
#include "cTimeMgr.h"


cTimeMgr::cTimeMgr()
{
}


cTimeMgr::~cTimeMgr()
{
}


HRESULT cTimeMgr::Setup()
{
	//타이머를 생성한다
	m_pTimer = new cTimer();
	m_pTimer->Setup();

	return S_OK;
}


void cTimeMgr::Update(float lock)
{
	if (m_pTimer != NULL)
		m_pTimer->Tick(lock);
}


void cTimeMgr::Render(HDC hdc)
{
	char str[256];
	sprintf_s(str, "MyVar: %d\n", getFrameRate());

	SetWindowText(g_hWnd, str);

	//#ifdef _DEBUG
	//	if (_timer != NULL)
	//	{
	//		//프레임을 찍는다.
	//		sprintf_s(str, "framePerSec : %d", _timer->getFrameRate());
	//		TextOut(hdc, 0, 0, str, strlen(str));
	//
	//		//월드타임을 찍는다.
	//		sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
	//		TextOut(hdc, 0, 20, str, strlen(str));
	//
	//		//갱신시간을 찍는다.
	//		sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
	//		TextOut(hdc, 0, 40, str, strlen(str));
	//	}
	//#else
	//	if (_timer != NULL)
	//	{
	//		//프레임을 찍는다.
	//		sprintf_s(str, "framePerSec : %d", _timer->getFrameRate());
	//		TextOut(hdc, 0, 0, str, strlen(str));
	//	}
	//#endif
}


void cTimeMgr::Release()
{
	SAFE_DELETE(m_pTimer);
	cSingleton::Release();
}
