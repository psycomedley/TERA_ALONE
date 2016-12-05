#pragma once
#include "cAction.h"

class cActionMoveToAttack : public cAction
{
	SYNTHESIZE(D3DXVECTOR3, m_vFrom, From);
	SYNTHESIZE(D3DXVECTOR3, m_vTo, To);

public:
	// cAction override
	virtual void Start() override;
	virtual void Update() override;

public:
	cActionMoveToAttack();
	~cActionMoveToAttack();
};

