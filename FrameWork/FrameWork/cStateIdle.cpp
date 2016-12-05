#include "stdafx.h"
#include "cStateIdle.h"
#include "cDynamicObj.h"

cStateIdle::cStateIdle()
{
}


cStateIdle::~cStateIdle()
{
}


void cStateIdle::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_IDLE, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateIdle::Update()
{

}


void cStateIdle::End()
{
	m_pParent->AnimationRemove();
}


void cStateIdle::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (animInfo.nIndex == E_ANI_DEFENCE_CALCEL)
	{
		pController->AnimationNext();
	}
}