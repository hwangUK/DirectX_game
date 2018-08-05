#pragma once
#include <d3dx9math.h>
#include <math.h>
#include "ModelLoader.h"
#include "Figure.h"
//3D Model enum
enum CHK_MODEL
{
	DEFAULT, AIR, TIGER, FLY
};

class OBJ_ACTOR
{
private:
	LPDIRECT3DDEVICE9 m_D3Ddevice;
	LPDIRECT3DTEXTURE9 tex;	
	//Origin
	float m_fScale;
	float m_fRadius;
	float m_fSpeed;
	int m_nLife;
	double m_theta;
	BOOL m_bIsPlayer;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_fRotation;
	DWORD m_dwSpawnTime;

	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matRotation;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matTranslation;

	LPD3DXMESH m_mesh;	
	ModelLoader m_modelLoder; 

	float m_fSubObjScale;
	D3DXVECTOR3 m_vSubObjPos[4];
	D3DXVECTOR3 m_fSubObjRotation;
	D3DXMATRIX m_SubObjmatWorld;
	D3DXMATRIX m_SubObjmatScale;
	D3DXMATRIX m_SubObjmatTranslation;
	D3DXMATRIX m_SubObjmatRotation;
	
	D3DXVECTOR3 m_vCycleRotationPosX;
	D3DXVECTOR3 m_vCycleRotationPosY;
	D3DXVECTOR3 m_vCycleRotationPosZ;
	
private:	
	void RenderSetSubObjTransform(int index, float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz);
	void RenderSetOrigin();
	void UpdateMatrixOrigin();

	void SetCycleRotationX(float Radius, float Speed, double theta);
	void SetCycleRotationY(float Radius, float Speed, double theta);
	void SetCycleRotationZ(float Radius, float Speed, double theta);	

	void BulletFire(int i);

public:
	CHK_MODEL CHECKMODEL = DEFAULT;
	Figure m_Helper[4];
	BOOL bFireOn[4] = { FALSE };
	BOOL bBulletGoToStartPos[4] = { TRUE };
	int m_nNumOfHelpaer;
	void BulletResetStartPos(int index);

public:
	void OnInit(LPDIRECT3DDEVICE9 d3ddevice, int life, float speed, LPD3DXMESH mesh, BOOL ISPLAYER, int NumofHelper);
	void InitModelLoad(CHK_MODEL ModelENuM);
	void OnRender();
	void OnUpdate();
	void OnRelease();

	void SetLife(int life);
	void SetTransform(float posX, float posY, float posZ);
	void SetRotation(float rX,float rY,float rZ);
	void SetScale(float scale);
	void SetSpawnTime(DWORD time);
	DWORD GetSpawnTime();
	void SetBulletLife(int life, int index);


	int GetLife();
	float GetScale();
	float GetSpeed();	
	float GetRadius();
	D3DXVECTOR3 GetPos();
	LPD3DXMESH GetMesh();		
	D3DXVECTOR3 GetSubObjHelperPos(int index);
	int GetBulletLife(int index);	
	Figure GetBulletFigure(int index);
};

