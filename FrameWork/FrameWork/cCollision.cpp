#include "stdafx.h"
#include "cCollision.h"
#include "cRay.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

cCollision::cCollision()
{
}


cCollision::~cCollision()
{
}


void cCollision::Release()
{
	cSingleton::Release();
}


bool cCollision::Collision(cRay* pRay, cBoundingSphere* pSphere)
{ 
	float qq = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetOri());
	float qv = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetDir());
	float vv = D3DXVec3Dot(&pRay->GetDir(), &pRay->GetDir());
	float rr = pSphere->GetRadius() * pSphere->GetRadius();

	return qv * qv - vv * (qq - rr) >= 0;
}


bool cCollision::Collision(cBoundingSphere* pSphere, cRay* pRay)
{
	float qq = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetOri());
	float qv = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetDir());
	float vv = D3DXVec3Dot(&pRay->GetDir(), &pRay->GetDir());
	float rr = pSphere->GetRadius() * pSphere->GetRadius();

	return qv * qv - vv * (qq - rr) >= 0;
}


bool cCollision::Collision(cBoundingSphere* pSphere1, cBoundingSphere* pSphere2)
{
	D3DXVECTOR3 v = pSphere1->GetCenter() - pSphere2->GetCenter();
	float distance = D3DXVec3Length(&v);

	if (pSphere1->GetRadius() + pSphere2->GetRadius() > distance)
		return true;
	return false;
}