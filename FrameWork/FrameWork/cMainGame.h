#pragma once
class cCube;
class cCamera;
class cStaticMesh;
class cDynamicMesh;
class cDynamicObj;
class cStaticObj;
class cPlayer;
class cOrca;
class cGrid;
class cMap;
class cMainGame
{
private:
	cCube*				cube;
	cCamera*			m_pCamera;

	cDynamicObj*		m_pBoss2;

	cMap*				m_pMap;
	cGrid*				m_pGrid;


	//юс╫ц
	int a = 0;
	float b = 0.1;
	void SetLighting();
	//cDynamicMesh*	m_pMesh;
	//cDynamicMesh*	m_pMesh2;

	//	cDynamicObj*	m_pPlayer;
	//	cDynamicObj*	m_pBoss;

public:
	HRESULT		Setup();
	void		Update();
	void		Render();
	void		Release();

public:
	cMainGame();
	~cMainGame();
};

