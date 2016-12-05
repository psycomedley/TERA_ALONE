#include "stdafx.h"
#include "cStateWait.h"
#include "cDynamicObj.h"


cStateWait::cStateWait()
{
}


cStateWait::~cStateWait()
{
}


void cStateWait::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_WAIT, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateWait::Update()
{

}


void cStateWait::End()
{
	m_pParent->AnimationRemove();
}


void cStateWait::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEFENCE_CALCEL)
	{
		pController->AnimationNext();
	}
}
