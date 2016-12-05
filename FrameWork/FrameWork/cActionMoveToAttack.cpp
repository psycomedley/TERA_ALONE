#include "stdafx.h"
#include "cActionMoveToAttack.h"
#include "cDynamicObj.h"

cActionMoveToAttack::cActionMoveToAttack()
{
}


cActionMoveToAttack::~cActionMoveToAttack()
{
}


void cActionMoveToAttack::Start()
{
	m_fPassedActionTime = 0.0f;
	if (m_pTarget)
		m_pTarget->SetPosition(m_vFrom);
}

void cActionMoveToAttack::Update()
{
	if (!m_pTarget)
		return;

	m_fPassedActionTime += GETSINGLE(cTimeMgr)->getElapsedTime();

	if (m_fPassedActionTime >= m_fActionTime)
	{
		m_pTarget->ChangeState(E_STATE_WAIT);
		m_pTarget->SetPosition(m_vTo);
		if (m_pDelegate)
			m_pDelegate->OnActionFinish(this);
		return;
	}

	if (m_pTarget->IsTargetCollision())
	{
		m_pTarget->Attack();
		m_vTo = m_pTarget->GetPosition();
		return;
	}
	float t = m_fPassedActionTime / m_fActionTime;

	D3DXVECTOR3 p;
	D3DXVec3Lerp(&p, &m_vFrom, &m_vTo, t);
	m_pTarget->SetPosition(p);
	m_pTarget->LookTarget();
	//m_pTarget->SetDirection(m_vFrom - m_vTo);
	m_pTarget->ChangeState(E_STATE_RUN);
}
