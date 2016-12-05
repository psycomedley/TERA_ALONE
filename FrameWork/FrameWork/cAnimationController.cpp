#include "stdafx.h"
#include "cAnimationController.h"
#include "iAnimationDelegate.h"


cAnimationController::cAnimationController()
	: m_fAnimBlendTime(0.2f)
	, m_fPassedAnimBlendTime(0.0f)
	, m_dPeriod(0.0f)
	, m_bPlayOnce(false)
	, m_nCurrentIdx(0)
	, m_pDelegate(NULL)
{
	m_stPrevAnimation.bBlend = true;
	m_stPrevAnimation.bPlayOnce = false;
	m_stPrevAnimation.nIndex = -1;
}


cAnimationController::~cAnimationController()
{
	SAFE_RELEASE(m_pController);
}


void cAnimationController::Update()
{
	if (m_pController)
	{
		if (!m_vecAnimation.empty())
		{
			m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);

			//1�� ����
			if (m_vecAnimation[m_nCurrentIdx].bPlayOnce)
			{
				D3DXTRACK_DESC td;
				m_pController->GetTrackDesc(0, &td);

				if (td.Position >= m_dPeriod)
				{
					m_pDelegate->OnAnimationFinish(this, m_vecAnimation[m_nCurrentIdx]);
				}
			}
		}
	}

//	if (m_pController)
//	{
//		if (!m_vecAnimation.empty())
//		{
//			m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
//			
//			//1�� ����
//			if (m_vecAnimation[m_nCurrentIdx].bPlayOnce)
//			{
//		//		m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
//				D3DXTRACK_DESC td;
//				m_pController->GetTrackDesc(0, &td);
//				
////				if (td.Position < m_dPeriod)
////				m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
////				else
//				if (td.Position >= m_dPeriod)
//				{
//					//m_stPrevAnimation.bBlend = m_vecAnimation[m_nCurrentIdx++].bBlend;
//					m_pDelegate->OnAnimationFinish(this, m_vecAnimation[m_nCurrentIdx]);
//				/*	m_stPrevAnimation = m_vecAnimation[m_nCurrentIdx++];
//
//					if (m_stPrevAnimation.bBlend)
//					{
//						SetAnimationIdxBlend(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
//					}
//					else
//					{
//						SetAnimationIdx(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
//					}*/
//				}
//		//		return;
//			}
//		//	else
//		//		m_pController->AdvanceTime(GETSINGLE(cTimeMgr)->getElapsedTime(), NULL);
//		}
//	}

	//Blend
	if (m_fPassedAnimBlendTime < m_fAnimBlendTime)
	{
		m_fPassedAnimBlendTime += GETSINGLE(cTimeMgr)->getElapsedTime(); //���� ����
		if (m_fPassedAnimBlendTime > m_fAnimBlendTime) //���� �ð��� ������
		{
			m_pController->SetTrackWeight(0, 1.0f); //0���� ����Ʈ ����
			m_pController->SetTrackEnable(1, false); //1�� Ʈ���� ����
		}
		else
		{
			float f = m_fPassedAnimBlendTime / m_fAnimBlendTime; //������ ���ؼ�
			m_pController->SetTrackWeight(1, 1 - f);  //1�� Ʈ���� ����ġ�� 1->0����
			m_pController->SetTrackWeight(0, f);      //0�� Ʈ���� ����ġ�� 0->1��
		}
	}
}


void cAnimationController::SetAnimationIdx(int nIdx, bool bPlayOnce)
{
	if (!m_pController)
		return;

	m_bPlayOnce = bPlayOnce;

	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pController->GetAnimationSet(nIdx, &pAnimationSet);

	if (pAnimationSet)
		m_dPeriod = pAnimationSet->GetPeriod();


	m_pController->GetAnimationSet(nIdx, &pAnimationSet);
	m_pController->SetTrackAnimationSet(0, pAnimationSet);
	SAFE_RELEASE(pAnimationSet);

	m_pController->SetTrackPosition(0, 0.0f);
	m_pController->ResetTime();
	m_pController->AdvanceTime(0, NULL);
}

void cAnimationController::SetAnimationIdxBlend(int nIdx, bool bPlayOnce)
{
	if (!m_pController)
		return;

	m_bPlayOnce = bPlayOnce;

	LPD3DXANIMATIONSET pAnimationSet = NULL;
	m_pController->GetAnimationSet(nIdx, &pAnimationSet);

	if (pAnimationSet)
		m_dPeriod = pAnimationSet->GetPeriod();


	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	m_pController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pController->GetAnimationSet(nIdx, &pNextAnimSet);

	D3DXTRACK_DESC stTrackDest;
	m_pController->GetTrackDesc(0, &stTrackDest);

	stTrackDest.Position -= m_fAnimBlendTime;

	m_pController->SetTrackDesc(1, &stTrackDest);

	m_pController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pController->SetTrackAnimationSet(1, pPrevAnimSet);

	m_pController->SetTrackWeight(0, 0.0f);
	m_pController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);

	m_fPassedAnimBlendTime = 0.0f;
	m_pController->SetTrackPosition(0, 0.0f);
	m_pController->ResetTime();
	m_pController->AdvanceTime(0, NULL);
}


void cAnimationController::AnimationStart()
{
	if (!m_vecAnimation.empty())
	{
		if (m_stPrevAnimation.bBlend)
			SetAnimationIdxBlend(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
		else
			SetAnimationIdx(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
	}
}


void cAnimationController::AnimationNext()
{
	if (m_vecAnimation.size() <= m_nCurrentIdx + 1)
		return;

	m_stPrevAnimation = m_vecAnimation[m_nCurrentIdx++];
	if (m_stPrevAnimation.bBlend)
		SetAnimationIdxBlend(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
	else
		SetAnimationIdx(m_vecAnimation[m_nCurrentIdx].nIndex, m_vecAnimation[m_nCurrentIdx].bPlayOnce);
}


void cAnimationController::AnimationRemove()
{
	if (m_vecAnimation.size() > 0)
		m_stPrevAnimation = m_vecAnimation[m_nCurrentIdx];
	m_nCurrentIdx = 0;
	m_vecAnimation.clear();
}


double cAnimationController::GetCurrentAnimPosition()
{
	D3DXTRACK_DESC td;
	m_pController->GetTrackDesc(0, &td);

	return td.Position / m_dPeriod;
}