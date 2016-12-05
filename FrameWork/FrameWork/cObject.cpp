#include "stdafx.h"
#include "cObject.h"


cObject::cObject()
	: m_nRefCount(1)
{
	GETSINGLE(cObjectMgr)->AddObject(this);
}


cObject::~cObject()
{
	assert(m_nRefCount == 0 && "�̷��� ����..");
	GETSINGLE(cObjectMgr)->RemoveObject(this);
}


void cObject::AddRef()
{
	assert(m_nRefCount != INT_MAX && "RefCount�� ��� ������ ������ �Ѿ�ϴ�.");
	++m_nRefCount;
}


void cObject::Release()
{
	assert(m_nRefCount > 0 && "�̷� ���� �� �߻��ؾߵ���??");
	
	if (--m_nRefCount == 0)
		delete this;
}


void cObject::AutoRelease()
{
	GETSINGLE(cAutoReleasePool)->AddObject(this);
}