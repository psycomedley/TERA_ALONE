#pragma once
#include "cMonster.h"

class iState;
class cOrcaClone : public cMonster
{
private:
	ST_SKILL_INFO	m_skillLongMove;
	SYNTHESIZE(bool, m_bActive, Active);

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	virtual void ChangeState(int pState, int nSkillIndex = -1) override;

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;

	virtual bool IsMoveAble() override;

public:
	cOrcaClone(char* szFolder, char* szFilename);
	~cOrcaClone();

private:
	cOrcaClone();
	virtual void SetupState() override;
	virtual void SetupStatus() override;
	virtual void Update() override;

};

