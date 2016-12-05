#pragma once
#include "cTimer.h"

class cTimeMgr : public cSingleton<cTimeMgr>
{
private:
	cTimer*		m_pTimer;

public:
	HRESULT		Setup();
	void		Update(float lock = 0.0f);
	void		Render(HDC hdc);
	void		Release();

	inline unsigned long getFrameRate() const { return m_pTimer->GetFrameRate(); }
	inline float		 getWorldTime() const{ return m_pTimer->GetWorldTime(); }
	inline float		 getElapsedTime() const { return m_pTimer->GetElapsedTime(); }

public:
	cTimeMgr();
	~cTimeMgr();
};

