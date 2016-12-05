#include "stdafx.h"
#include "cMonster.h"


cMonster::cMonster(char* szFolder, char* szFilename)
	: m_fDetectRange(0.0f)
	, m_bIsBattle(false)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);

	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::cMonster()
	: m_fDetectRange(0.0f)
{
	ZeroMemory(&m_stInfo, sizeof(ST_UNIT_INFO));
}


cMonster::~cMonster()
{
}


void cMonster::Update()
{

}


void cMonster::UpdateAndRender(D3DXMATRIXA16* pmat /*= NULL*/)
{
	cDynamicObj::UpdateAndRender(pmat);
}