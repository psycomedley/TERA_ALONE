#pragma once
class cCube
{
private:
	D3DXMATRIXA16 m_matWorld;

	ST_PC_VERTEX vertex[36];

	D3DXVECTOR3 m_vPosition;

	D3DXVECTOR3 m_vDirection;
	float m_fAngle;
	float m_fSpeed;

public:
	ST_PC_VERTEX* getVertex() { return vertex; }

	D3DXVECTOR3 getPos() { return m_vPosition; }

public:
	void Setup();
	void Update();
	void Render();

public:
	cCube();
	~cCube();
};

