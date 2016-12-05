#include "stdafx.h"
#include "cAutoReleasePool.h"


cAutoReleasePool::cAutoReleasePool()
{
}


cAutoReleasePool::~cAutoReleasePool()
{
}


void cAutoReleasePool::AddObject(cObject* pObject)
{
	m_setPool.insert(pObject);
}


void cAutoReleasePool::Drain()
{
	for each(auto p in m_setPool)
		SAFE_RELEASE(p);
	m_setPool.clear();
}