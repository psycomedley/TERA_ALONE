#pragma once
#include "cDynamicObj.h"

class cMonster : public cDynamicObj
{
protected:
	SYNTHESIZE(ST_UNIT_INFO, m_stInfo, Info);

	bool			m_bIsBattle;
	float			m_fDetectRange;

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL) override;

public:
	cMonster(char* szFolder, char* szFilename);
	~cMonster();

protected:
	cMonster();
	virtual void SetupState() PURE;
	virtual void SetupStatus() PURE;
	virtual void Update() override;
};

