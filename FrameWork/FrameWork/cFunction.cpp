#include "stdafx.h"
#include "cFunction.h"

namespace MY_FUNCTION
{
	int GetInt(int nNum) { return rand() % nNum; }
	int GetFromIntTo(int fromNum, int toNum) { return (rand() % (toNum - fromNum + 1)) + fromNum; }

	//getFloat 
	//0.0 ~ 1.0 RAND_MAX의 최대값 (32767)
	float GetFloat(void) { return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float num) { return (float)rand() / (float)RAND_MAX * num; }
	float GetFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x, y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
		return rc;
	}

	int GetWindowWidth()
	{
		RECT rect;
		GetWindowRect(g_hWnd, &rect);
		return (rect.right - rect.left);
	}
	int GetWindowHeight()
	{
		RECT rect;
		GetWindowRect(g_hWnd, &rect);
		return (rect.bottom - rect.top);
	}
}