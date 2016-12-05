#pragma once
#include "cSingleton.h"

class cObject;
class cAutoReleasePool : public cSingleton<cAutoReleasePool>
{
private:
	std::set<cObject*> m_setPool;

public:
	void AddObject(cObject* pObject);
	void Drain();

public:
	cAutoReleasePool();
	~cAutoReleasePool();
};

