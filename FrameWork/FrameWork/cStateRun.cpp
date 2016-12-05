#include "stdafx.h"
#include "cStateRun.h"
#include "cDynamicObj.h"


cStateRun::cStateRun()
{
}


cStateRun::~cStateRun()
{
}


void cStateRun::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_RUN, false, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateRun::Update()
{

}


void cStateRun::End()
{
	m_pParent->AnimationRemove();
}


void cStateRun::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{

}
