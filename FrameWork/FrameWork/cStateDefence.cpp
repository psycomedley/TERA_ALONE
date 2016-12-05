#include "stdafx.h"
#include "cStateDefence.h"
#include "cDynamicObj.h"


cStateDefence::cStateDefence()
{
}


cStateDefence::~cStateDefence()
{
}


void cStateDefence::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_START, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_DEFENCE_LOOP, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateDefence::Update()
{

}


void cStateDefence::End()
{
	m_pParent->AnimationRemove();
	ST_ANIMATION_INFO aniInfo(E_ANI_DEFENCE_CALCEL, true, true);
	m_pParent->AddAnimation(aniInfo);
//	pObj->GetAnimController()->m_pController->SetTrackPosition(0, 0);

//	pObj->GetAnimController()->m_stCurrentAnimation = ST_ANIMATION_INFO(5, true, false);
//	pObj->AnimationStart();
//	pObj->GetAnimController()->m_pController->SetTrackPosition(0, 0.0f);
//	pObj->SetAnimationIdx(5, false);
}


void cStateDefence::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEFENCE_START)
	{
//		pController->SetAnimationIdx(3, false);
//		pController->m_stCurrentAnimation = ST_ANIMATION_INFO(3, false, true);
		pController->AnimationNext();
	}
	/*if (animInfo.nIndex == 5)
	{
		if (animInfo.bBlend)
			pController->SetAnimationIdxBlend(0, false);
		else
			pController->SetAnimationIdx(0, false);
		pController->m_stCurrentAnimation = ST_ANIMATION_INFO(0, false, true);
	}*/

	//char msg[128];
	//static int a = 0;
	//a++;
	//OutputInteger(msg, "x", animInfo.nIndex);
}