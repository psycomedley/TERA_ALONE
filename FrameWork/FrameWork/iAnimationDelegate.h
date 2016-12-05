#pragma once
class cAnimationController;
class iAnimationDelegate
{
public:
	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) PURE;
};

