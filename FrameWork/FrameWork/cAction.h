#pragma once

class cDynamicObj;
class cAction;

class iActionDelegate
{
public:
	virtual void OnActionFinish(cAction* pSender) PURE;
};

class cAction : public cObject
{
protected:
	float m_fPassedActionTime;
	SYNTHESIZE(iActionDelegate*, m_pDelegate, Delegate);
	SYNTHESIZE(float, m_fActionTime, ActionTime);
	SYNTHESIZE(cDynamicObj*, m_pTarget, Target);

public:
	cAction(void);
	virtual ~cAction(void);

	virtual void Start();
	virtual void Update();
};

