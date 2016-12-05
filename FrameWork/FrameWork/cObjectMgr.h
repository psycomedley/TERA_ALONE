#pragma once
#include "cSingleton.h"

class cObject;
class cObjectMgr : public cSingleton<cObjectMgr>
{
private:
	set<cObject*> m_setObject;

public:
	void AddObject(cObject* pObject);
	void RemoveObject(cObject* pObject);
	void Release();

public:
	cObjectMgr();
	~cObjectMgr();
};

