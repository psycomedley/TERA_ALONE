#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: m_nRefCount(1)
{
	GETSINGLE(cObjectMgr)->AddObject(this);
}


cObject::~cObject()
{
	assert(m_nRefCount == 0 && "이러지 말자..");
	GETSINGLE(cObjectMgr)->RemoveObject(this);
}


void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount가 사용 가능한 범위를 넘어섭니다.");
	++m_nRefCount;
}


void cObject::Release()
{
	assert(m_nRefCount > 0 && "이런 일이 왜 발생해야되죠??");
	
	if (--m_nRefCount == 0)
		delete this;
}


void cObject::AutoRelease()
{
	GETSINGLE(cAutoReleasePool)->AddObject(this);
}