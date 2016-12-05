#pragma once

class iAnimationDelegate;
class cAnimationController
{
public:
	LPD3DXANIMATIONCONTROLLER		m_pController;

	float							m_fAnimBlendTime;
	float							m_fPassedAnimBlendTime;
	double							m_dPeriod;
	bool							m_bPlayOnce;

	std::vector<ST_ANIMATION_INFO>	m_vecAnimation;
	int								m_nCurrentIdx;
	ST_ANIMATION_INFO				m_stPrevAnimation;
	ST_ANIMATION_INFO				m_stCurrentAnimation;

	SYNTHESIZE(iAnimationDelegate*, m_pDelegate, Delegate);

//	bool							m_bBlend;

//	SYNTHESIZE(double, m_dPeriod, Period);
//	SYNTHESIZE(bool, m_bPlayOnce, PlayOnce);

public:
	void AddAnimation(ST_ANIMATION_INFO stAnimationInfo) { m_vecAnimation.push_back(stAnimationInfo); }
	void SetAnimationIdx(int nIdx, bool bPlayOnce = false);
	void SetAnimationIdxBlend(int nIdx, bool bPlayOnce = false);

	void AnimationStart();
	void AnimationNext();
	void AnimationRemove();

public:
	ST_ANIMATION_INFO GetCurrentAnimInfo() { return m_vecAnimation[m_nCurrentIdx]; }
	//0~1 ªÁ¿Ã
	double GetCurrentAnimPosition();

public:
	void Update();

public:
	cAnimationController();
	~cAnimationController();
};

