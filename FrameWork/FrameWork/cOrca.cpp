#include "stdafx.h"
#include "cOrca.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cStateWait.h"
#include "cStateCombo.h"
#include "cStateBossSkill.h"
#include "cAnimationController.h"
#include "cActionMoveToAttack.h"
#include "cOrcaClone.h"


cOrca::cOrca(char* szFolder, char* szFilename)
	: m_nNumClone(0)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	SetupState();
	SetupStatus();
}


cOrca::cOrca()
	: m_nNumClone(0)
{
}


cOrca::~cOrca()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cOrca::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_RUN] = new cStateRun;
	m_aStates[E_STATE_RUN]->SetParent(this);
	m_aStates[E_STATE_WAIT] = new cStateWait;
	m_aStates[E_STATE_WAIT]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
	ChangeState(E_STATE_IDLE);
}


void cOrca::SetupStatus()
{
	m_stInfo.sName = "Orca";

	m_stInfo.nMaxHp = 100;
	m_stInfo.nHp = m_stInfo.nMaxHp;
	m_stInfo.nMaxMp = 100;
	m_stInfo.nMp = m_stInfo.nMaxMp;

	m_stInfo.fDamage = 100.0f;
	m_stInfo.fDefence = 100.0f;

	m_fDetectRange = 15.0f;

	m_skillLongMove.SetInfo(10.0f, 100);
//	m_skillLongMove.sSpeech = "어디 한 번 나의 속도를 느껴보아라!!";
	m_skillLongMove.sSpeech = "나의 속도를 쬐끔만 느껴보아라!!";
	m_skillHeavyAtk.SetInfo(20.0f, 100);
	m_skillAttack.SetInfo(3.0f, 10);
}


void cOrca::UpdateAndRender(D3DXMATRIXA16* pmat)
{
	Update();
	m_pState->Update();
	cDynamicObj::UpdateAndRender(pmat);
}


void cOrca::ChangeState(iState* pState, int nSkillIndex /*= -1*/)
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


void cOrca::ChangeState(int pState, int nSkillIndex /*= -1*/)
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


bool cOrca::IsMoveAble()
{
	if (m_pState == m_aStates[E_STATE_RUN] ||
		m_pState == m_aStates[E_STATE_IDLE] ||
		m_pState == m_aStates[E_STATE_WAIT])
		return true;
	return false;
}


void cOrca::Update()
{
	cMonster::Update();

	if (!m_bIsBattle)
	{
		D3DXVECTOR3 distance = m_vPosition - GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();
		if (D3DXVec3Length(&distance) < m_fDetectRange)
		{
			m_bIsBattle = true;
			m_pTarget = GETSINGLE(cObjMgr)->GetPlayer();
			ChangeState(E_STATE_WAIT);
		}
	}
	else
	{
		float fElapsedTime = GETSINGLE(cTimeMgr)->getElapsedTime();
		m_skillHeavyAtk.fPassedTime += fElapsedTime;
		m_skillLongMove.fPassedTime += fElapsedTime;
		m_skillAttack.fPassedTime += fElapsedTime;

		if (IsMoveAble())
		{
			if (m_nNumClone > 0)
			{
				m_nNumClone = 3;
				auto cloneList = GETSINGLE(cObjMgr)->GetMonsterList("Orca_Clone");
	
				for (auto iter = cloneList->begin(); iter != cloneList->end(); iter++)
				{
					if (!((cOrcaClone*)(*iter))->GetActive())
						m_nNumClone--;
				}

				return;
			}
			if (m_skillLongMove.fPassedTime >= m_skillLongMove.fCoolTime)
			{
				LongMove();
			}
			else if (m_skillHeavyAtk.fPassedTime >= m_skillHeavyAtk.fCoolTime)
			{
				m_skillHeavyAtk.fPassedTime = 0.0f;
				LookTarget();
				ChangeState(E_STATE_SKILL, E_BOSS_HEAVYATK_START);
			}
			else if (m_skillAttack.fPassedTime >= m_skillAttack.fCoolTime)
			{
				if (IsTargetCollision())
				{
					if (m_pAction)
						SAFE_RELEASE(m_pAction);
					m_skillAttack.fPassedTime = 0.0f;
					LookTarget();
					ChangeState(E_STATE_SKILL, E_BOSS_ATK1);
				}
				else
				{
					cActionMoveToAttack* pActionMove = new cActionMoveToAttack;
					pActionMove->SetFrom(m_vPosition);
					pActionMove->SetTo(m_pTarget->GetPosition());
					float fDist = D3DXVec3Length(&(m_vPosition - m_pTarget->GetPosition()));
					pActionMove->SetActionTime(fDist * 0.2);
					pActionMove->SetTarget(this);
					SetAction(pActionMove);
					SAFE_RELEASE(pActionMove);
				}
			}
			else
			{
				LookTarget();
			}
		}
	}
}


void cOrca::LongMove()
{
	RECT rect = RectMakeCenter(GetWindowWidth() / 2, 150, 500, 50);
	GETSINGLE(cTextMgr)->AddText(E_FONT_BOSS, m_skillLongMove.sSpeech, 3, rect);
	if (m_pAction)
		SAFE_RELEASE(m_pAction);
	m_skillLongMove.fPassedTime = 0.0f;
	m_nNumClone = 3;

	//본체
	D3DXVECTOR3 vEnemyPos = m_pTarget->GetPosition();
	int nRealOrca = GetInt(4);
	int nSign = pow(-1, (nRealOrca % 2));
	int nX = nSign * (nRealOrca / 2) * 15;
	D3DXVECTOR3 vPos(nX, 0, (15 - abs(nX)) * nSign);
	SetPosition(vEnemyPos + vPos);
	LookTarget();

	//있으면 재사용
	auto cloneList = GETSINGLE(cObjMgr)->GetMonsterList("Orca_Clone");
	if (cloneList)
	{
		int i = 0;
		for (auto iter = cloneList->begin(); iter != cloneList->end(); i++)
		{
			if (i == nRealOrca)
				continue;
			int sign = pow(-1, (i % 2));
			int x = sign * (i / 2) * 15;
			D3DXVECTOR3 vPos(x, 0, ((15 - abs(x))) * sign);
			((cOrcaClone*)(*iter))->SetActive(true);
			(*iter)->SetPosition(vEnemyPos + vPos);
			(*iter)->LookTarget();
			(*iter)->ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
			iter++;
		}
	}
	else
	{
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, D3DX_PI / 2);

		for (int i = 0; i < 4; i++)
		{
			if (i == nRealOrca)
				continue;
			int sign = pow(-1, (i % 2));
			int x = sign * (i / 2) * 15;
			D3DXVECTOR3 vPos(x, 0, ((15 - abs(x))) * sign);
			cDynamicObj* clone = new cOrcaClone("Monster", "Orca.X");
			clone->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
			clone->SetRevision(matR);
			clone->SetPosition(vEnemyPos + vPos);
			clone->SetTarget(m_pTarget);
			clone->LookTarget();
			GETSINGLE(cObjMgr)->AddMonster("Orca_Clone", clone);
		}
	}
	ChangeState(E_STATE_SKILL, E_BOSS_LONGMOVE_START);
}