#pragma once

class cPyramid;
class cGrid
{
private:
	SYNTHESIZE_ADD_REF(LPDIRECT3DVERTEXBUFFER9, m_pVB, VB);
	SYNTHESIZE_PASS_BY_REF(int, m_nLineNum, LineNum);
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	std::vector<cPyramid*>		m_vecPyramid;

public:
	cGrid(void);
	~cGrid(void);

	void Setup(int nNumLine = 20);
	void Render();
};

