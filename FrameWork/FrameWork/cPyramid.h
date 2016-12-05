#pragma once

class cPyramid
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	SYNTHESIZE_ADD_REF(LPDIRECT3DVERTEXBUFFER9, m_pVB, VB);
	SYNTHESIZE_PASS_BY_REF(int, m_nTriNum, TriNum);

public:
	cPyramid(void);
	virtual ~cPyramid(void);

	void Setup(D3DCOLOR c, D3DXMATRIXA16* pmat = NULL);
	virtual void Render();
};

