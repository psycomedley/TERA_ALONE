#include "stdafx.h"
#include "cStateSkill.h"
#include "cDynamicObj.h"
#include "cPlayer.h"

cStateSkill::cStateSkill()
	: m_nSkillIndex(-1)
{
}


cStateSkill::~cStateSkill()
{
}


void cStateSkill::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);

	if (m_nSkillIndex == E_ANI_DOUBLEATTACK)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(E_ANI_DOUBLEATTACK, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_ANI_DOUBLEATTACKR, true, false);
		m_pParent->AddAnimation(aniInfo);
	}


	m_pParent->AnimationStart();
}


void cStateSkill::Update()
{
}


void cStateSkill::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DOUBLEATTACK)
	{
		m_pParent->AnimationNext();
		return;
	}
	End();
}
