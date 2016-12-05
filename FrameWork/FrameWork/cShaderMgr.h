#pragma once

class cShaderMgr : public cSingleton<cShaderMgr>
{
private:
	map<string, LPD3DXEFFECT>	m_mapEffect;

public:
	LPD3DXEFFECT GetEffect(string sKey);

public:
	void Release();

public:
	cShaderMgr();
	~cShaderMgr();
};

