#pragma once
#include "cSingleton.h"

class cRay;
class cBoundingBox;
class cBoundingSphere;
class cCollision : public cSingleton<cCollision>
{
public:
	bool Collision(cRay* pRay, cBoundingSphere* pSphere);
	bool Collision(cBoundingSphere* pSphere, cRay* pRay);
	bool Collision(cBoundingSphere* pSphere1, cBoundingSphere* pSphere2);

public:
	void Release();

public:
	cCollision();
	~cCollision();
};

