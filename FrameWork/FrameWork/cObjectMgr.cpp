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
	assert(m_setObject.empty() && "생성된 cObject를 상속받은 객체 중 삭제되지 않은 객체가 있습니다.");
	cSingleton::Release();
}