#pragma once
#include <d3dx9math.h>
//법선벡터
struct CROSSVERTEX
{
	D3DXVECTOR3 vPos;
};
//삼각뿔 객체
struct CUSTOMVERTEX2
{
	D3DXVECTOR3 position;
	D3DXVECTOR3 vNomalVector;
};
class Figure
{
private:
	LPDIRECT3DDEVICE9 m_pD3Ddevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DVERTEXBUFFER9 m_pCrossVB;

	D3DXVECTOR3 m_nomal[4];
	
	D3DXMATRIX m_matTranslateFire;
	D3DXMATRIX m_matScaleFire;
	LPD3DXMESH m_pBulletMesh;

	D3DXVECTOR3 m_vBulletPos;
	D3DXVECTOR3 m_vTargetPos;
	int m_life = 0;

public:	
	void OnInit(LPDIRECT3DDEVICE9 D3Ddevice);
	void OnRender();
	void OnRelease();
	
	////bullet
	void InitMakeFire(float Radius, float Scale);
	void Fire(int index, float speed);
	void RenderFire();

	void SetLife(int life);
	int GetLife();	
	
	void SetBulletPos(D3DXVECTOR3 vbulletpos);
	float m_BulletRadius;
	float m_BulletScale;
	D3DXVECTOR3 GetBulletPos();

};

