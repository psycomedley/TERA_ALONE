#pragma once
#include "iAnimationDelegate.h"
#include "cAnimationController.h"

class cDynamicObj;
class iState : public iAnimationDelegate
{
protected:
	cDynamicObj* m_pParent;

public:
	void SetParent(cDynamicObj* pParent) { m_pParent = pParent; }

public:
	virtual void Start() PURE;
	virtual void Update() PURE;
//	virtual void Render() PURE;
	virtual void End() PURE;

public:
	iState();
	~iState();
};

