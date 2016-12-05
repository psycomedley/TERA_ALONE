#pragma once
class cTimer
{
private:
	bool			m_bIsHardware;		
	float			m_fTimeScale;		
	float			m_fTimeElapsed;		
	__int64			m_nCurTime;			
	__int64			m_nLastTime;			
	__int64			m_nPeriodFrequency;	

	unsigned long	m_lFrameRate;			
	unsigned long	m_lFPSFrameCount;		
	float			m_fFPSTimeElapsed;
	float			m_fWorldTime;			

public:
	HRESULT Setup();

	void Tick(float lockFPS = 0.0f);

	inline unsigned long GetFrameRate() const { return m_lFrameRate; }
	inline float		 GetElapsedTime() const { return m_fTimeElapsed; }
	inline float		 GetWorldTime() const { return m_fWorldTime; }

public:
	cTimer();
	~cTimer();
};

