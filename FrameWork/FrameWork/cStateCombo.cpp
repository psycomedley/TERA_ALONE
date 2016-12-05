#include "stdafx.h"
#include "cStateCombo.h"
#include "cDynamicObj.h"
#include "cPlayer.h"


cStateCombo::cStateCombo()
	: m_bNextAttack(false)
{
}


cStateCombo::~cStateCombo()
{
}


void cStateCombo::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_COMBO1, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO2, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO3, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO4, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO5, true, false);
	m_pParent->AddAnimation(aniInfo);

	m_pParent->AnimationStart();
}


void cStateCombo::Update()
{
	if (MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
		m_bNextAttack = true;

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO1 ||
		m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO2 || 
		m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO3)
		m_pParent->Move(0.1f);

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO4)
		if (m_pParent->GetCurrentAnimPosition() > 0.5f)
			m_pParent->Move(0.1f);
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO5)
		if (m_pParent->GetCurrentAnimPosition() < 0.5f)
			m_pParent->Move(0.1f);
}


void cStateCombo::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateCombo::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (m_bNextAttack)
	{
		if (animInfo.nIndex == E_ANI_COMBO1 ||
			animInfo.nIndex == E_ANI_COMBO2 ||
			animInfo.nIndex == E_ANI_COMBO3 ||
			animInfo.nIndex == E_ANI_COMBO4)
		{
			pController->AnimationNext();
			m_bNextAttack = false;
		}
	}
	else
	{
		if (animInfo.nIndex == E_ANI_COMBO1R ||
			animInfo.nIndex == E_ANI_COMBO2R ||
			animInfo.nIndex == E_ANI_COMBO3R ||
			animInfo.nIndex == E_ANI_COMBO4R)
		{
			if (m_bNextAttack)
			{
				pController->AnimationNext();
				m_bNextAttack = false;
			}
			else
				End();
		}
		else
		{
			m_pParent->AnimationRemove();
			ST_ANIMATION_INFO aniInfo;
			switch (animInfo.nIndex)
			{
			case E_ANI_COMBO1:
				aniInfo.SetInfo(E_ANI_COMBO1R, true, true);
				break;
			case E_ANI_COMBO2:
				aniInfo.SetInfo(E_ANI_COMBO2R, true, true);
				break;
			case E_ANI_COMBO3:
				aniInfo.SetInfo(E_ANI_COMBO3R, true, true);
				break;
			case E_ANI_COMBO4:
				aniInfo.SetInfo(E_ANI_COMBO4R, true, true);
				break;
			}
			m_pParent->AddAnimation(aniInfo);
			pController->AnimationNext();
		}
	}
	
	if (animInfo.nIndex == E_ANI_COMBO5)
		End();
}
