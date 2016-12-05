#include "stdafx.h"
#include "cObjMgr.h"
#include "cDynamicObj.h"


cObjMgr::cObjMgr()
{
}


cObjMgr::~cObjMgr()
{
}


void cObjMgr::AddMonster(string sKey, cDynamicObj* pMonster)
{
	auto iter = m_mapMonster.find(sKey);

	if (iter == m_mapMonster.end())
	{
		vector<cDynamicObj*> ObjList;
		ObjList.push_back(pMonster);
		m_mapMonster.insert(make_pair(sKey, ObjList));
	}

	else
		iter->second.push_back(pMonster);
}


void cObjMgr::Update()
{
	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			(*iter2)->Update();
		}
	}
}


void cObjMgr::Render()
{
	if (m_pPlayer)
		m_pPlayer->UpdateAndRender();

	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			(*iter2)->UpdateAndRender();
//			(*iter2)->Bounding_Render();
		}
	}
}


void cObjMgr::Release()
{
	SAFE_RELEASE(m_pPlayer);

	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			SAFE_RELEASE((*iter2));
		}
		iter->second.clear();
	}

	cSingleton::Release();
}


vector<cDynamicObj*>* cObjMgr::GetMonsterList(string sKey)
{
	auto iter = m_mapMonster.find(sKey);

	if (iter == m_mapMonster.end())
		return NULL;
	return &m_mapMonster[sKey];
}