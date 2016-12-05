#include "stdafx.h"
#include "cOrcaClone.h"
#include "iState.h"
#include "cStateWait.h"
#include "cStateBossSkill.h"


cOrcaClone::cOrcaClone(char* szFolder, char* szFilename)
	: m_bActive(true)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
	
	SetupState();
	SetupStatus();
}


cOrcaClone::cOrcaClone()
	: m_bActive(true)
{
}


cOrcaClone::~cOrcaClone()
{
}


void cOrcaClone::SetupState()
{
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
}


void cOrcaClone::SetupStatus()
{
	m_stInfo.sName = "Orca_Clone";

	m_stInfo.nMaxHp = 100;
	m_stInfo.nHp = m_stInfo.nMaxHp;
	m_stInfo.nMaxMp = 100;
	m_stInfo.nMp = m_stInfo.nMaxMp;

	m_stInfo.fDamage = 100.0f;
	m_stInfo.fDefence = 100.0f;

	m_fDetectRange = 15.0f;

	m_skillLongMove.SetInfo(0.0f, 100);
}


void cOrcaClone::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	if (m_bActive == false)
		return;
	if (m_pState == m_aStates[E_STATE_WAIT])
		m_bActive = false;

	Update();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cOrcaClone::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == pState)
			return;

	iState* pPrevState = m_pState;
	m_pState = pState;

	if (pPrevState)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
		((cStateBossSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


void cOrcaClone::ChangeState(int pState, int nSkillIndex /*= -1*/)
{
	if (m_pState)
		if (m_pState == m_aStates[pState])
			return;

	iState* pPrevState = m_pState;
	m_pState = m_aStates[pState];

	if (pPrevState)
		pPrevState->End();

	((cDynamicMesh*)m_pMesh)->GetAnimController()->SetDelegate(m_pState);

	if (m_pState == m_aStates[E_STATE_SKILL])
		((cStateBossSkill*)m_pState)->SetSkillIndex(nSkillIndex);

	m_pState->Start();
}


bool cOrcaClone::IsMoveAble()
{
	return true;
}


void cOrcaClone::Update()
{
	cMonster::Update();
}
