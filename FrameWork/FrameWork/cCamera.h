#pragma once
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	float			m_fCamRotX;
	float			m_fCamRotY;
	float			m_fCamDist;

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(D3DXVECTOR3* pTarget = NULL);
	void CameraMove();

	//
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

