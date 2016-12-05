#pragma once
#include <stddef.h>

template <typename T>
class cSingleton
{
private:
	static T* pInst;

public:
	static T* GetInst()
	{
		if (pInst == NULL)
			pInst = new T;

		return pInst;
	}
	void Release()
	{
		if (pInst != NULL)
		{
			delete pInst;
			pInst = NULL;
		}
	}

public:
	cSingleton() {}
	~cSingleton() {}
};

template <typename T> T* cSingleton <T>::pInst = NULL;
#define GETSINGLE(type) (type::GetInst())