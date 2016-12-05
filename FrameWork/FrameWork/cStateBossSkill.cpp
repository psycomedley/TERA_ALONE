#include "stdafx.h"
#include "cStateBossSkill.h"
#include "cDynamicObj.h"
#include "cOrca.h"


cStateBossSkill::cStateBossSkill()
	: m_nSkillIndex(-1)
{
}


cStateBossSkill::~cStateBossSkill()
{
}


void cStateBossSkill::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);

	if (m_nSkillIndex == E_BOSS_LONGMOVE_START)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(m_nSkillIndex, true, false);
		m_pParent->AddAnimation(aniInfo);
		
		aniInfo.SetInfo(E_BOSS_LONGMOVE_LOOP, true, false);
		int loop = GetFromIntTo(1, 3);
		for (int i = 0; i < loop; i++)
			m_pParent->AddAnimation(aniInfo);
		
		aniInfo.SetInfo(E_BOSS_LONGMOVE_RUN, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_LONGMOVE_END, true, true);
		m_pParent->AddAnimation(aniInfo);
	}
	else if (m_nSkillIndex == E_BOSS_HEAVYATK_START)
	{
		m_pParent->AnimationRemove();
		aniInfo.SetInfo(m_nSkillIndex, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_HEAVYATK_LOOP, true, false);
		m_pParent->AddAnimation(aniInfo);
		aniInfo.SetInfo(E_BOSS_HEAVYATK_END, true, true);
		m_pParent->AddAnimation(aniInfo);
	}

	m_pParent->AnimationStart();
}


void cStateBossSkill::Update()
{
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_LONGMOVE_RUN)
	{
		m_pParent->Move(1.0f);
	}
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_BOSS_HEAVYATK_LOOP)
	{
		m_pParent->Move(0.2f);
	}
}


void cStateBossSkill::End()
{
	m_pParent->AnimationRemove();
	m_pParent->ChangeState(E_STATE_WAIT);
}


void cStateBossSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_BOSS_HEAVYATK_END ||
		animInfo.nIndex == E_BOSS_LONGMOVE_END ||
		animInfo.nIndex == E_BOSS_ATK1 ||
		animInfo.nIndex == E_BOSS_ATK2)
	{
		End();
	}
	else
	{
		m_pParent->AnimationNext();
	}
}
