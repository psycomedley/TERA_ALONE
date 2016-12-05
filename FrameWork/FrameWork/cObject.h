#pragma once

class cObject
{
private:
	int m_nRefCount;

public:
	void AddRef();
	void Release();
	void AutoRelease();

public:
	cObject(void);
	virtual ~cObject(void);

};