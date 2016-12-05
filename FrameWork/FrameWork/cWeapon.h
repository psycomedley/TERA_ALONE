#pragma once
#include "cStaticMesh.h"
#include "cStaticObj.h"

class cWeapon : public cStaticObj
{
private:
//	SYNTHESIZE(string, m_sHolderKey, HolderKey);
	string m_sHolderKey;
	SYNTHESIZE(string, m_sParentKey, ParentKey);
	SYNTHESIZE(D3DXMATRIXA16*, m_matParent, MatParent);
	D3DXMATRIXA16 m_matWorld;

public:
	string GetHolderKey() { return m_sHolderKey; }
	void SetHolderKey(char* szFolder, char* szFilename) { m_sHolderKey = string(szFolder) + string("/") + string(szFilename); }

	HRESULT SetParentMat();

private:
	void SetWorldMat();

public:
	virtual void Update() override;
	virtual void Render() override;

public:
	cWeapon(char* szFolder, char* szFilename);
	~cWeapon();

private:
	cWeapon();
};
