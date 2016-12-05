#include "stdafx.h"
#include "cObjectMgr.h"


cObjectMgr::cObjectMgr()
{

}


cObjectMgr::~cObjectMgr()
{

}


void cObjectMgr::AddObject(cObject* pObject)
{
	m_setObject.insert(pObject);
}


void cObjectMgr::RemoveObject(cObject* pObject)
{
	m_setObject.erase(pObject);
}


void cObjectMgr::Release()
{
	assert(m_setObject.empty() && "������ cObject�� ��ӹ��� ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
	cSingleton::Release();
}