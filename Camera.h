#pragma once
#include <d3dx9.h>

class Camera
{
private:
	LPDIRECT3DDEVICE9 m_D3Ddevice;

	D3DXVECTOR3 m_Eye, m_At, m_Up;

	D3DXMATRIX m_matrixView;
	D3DXMATRIX m_matrixProjection;

	D3DVIEWPORT9 m_vp;

private:
	void TransformCameraMatrix();
public:
	void SetInit(LPDIRECT3DDEVICE9 d3ddevice);
	void SetViewPort(DWORD x, DWORD  y, DWORD  width, DWORD  height,float minZ, float maxZ);
	void SetCameraPos(float x, float y, float z);
	void SetTargetPos(float x, float y, float z);
	void SetViewUp(float x, float y, float z);
	void ZoomFunc(int timer, int sectionCount, int* Section);
	void OnRelease();
	D3DXVECTOR3 GetCameraPos();
	D3DXVECTOR3 GetTargetPos();
	D3DXVECTOR3 GetViewUpPos();
};

