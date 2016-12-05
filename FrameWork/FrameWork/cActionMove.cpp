#include "StdAfx.h"
#include "cActionMove.h"
#include "cDynamicObj.h"

cActionMove::cActionMove(void)
	: m_vFrom(0, 0, 0)
	, m_vTo(0, 0, 0)
{
}

cActionMove::~cActionMove(void)
{
}

void cActionMove::Start()
{
	m_fPassedActionTime = 0.0f;
	if (m_pTarget)
		m_pTarget->SetPosition(m_vFrom);
}

void cActionMove::Update()
{
	if (!m_pTarget)
		return;

	cAction::Update();

	if (m_fPassedActionTime >= m_fActionTime)
	{
		m_pTarget->SetPosition(m_vTo);
		if (m_pDelegate)
			m_pDelegate->OnActionFinish(this);
		return;
	}

	float t = m_fPassedActionTime / m_fActionTime;

	D3DXVECTOR3 p;
	D3DXVec3Lerp(&p, &m_vFrom, &m_vTo, t);
	m_pTarget->SetPosition(p);
	m_pTarget->SetDirection(m_vFrom - m_vTo);
}
