#pragma once
#include <d3dx9math.h>
#include "D3DApp.h"
#include "Sound.h"
#include "Camera.h"
#include "Sprite.h"
#include "CustomTimer.h"
#include "Axis.h"

#include "OBJ_Cube.h"
#include "OBJ_Ground.h"
#include "OBJ_ACTOR.h"

class Game : public D3DApp
{
private:
	virtual void OnInit() override;
	virtual void OnRender() override;
	virtual void OnUpdate() override;
	virtual void OnRelease() override;
	void SceneSet();

private:
	CustomTimer m_Timer;
	Camera m_Camera;	
	Sprite m_sprite01;	
	//FONT & FPS	
	LPD3DXFONT m_pFont[5];
	LPD3DXFONT m_pfFPS;
	RECT m_rt;
	int m_nFPS;
	int m_nFPSCount;

	//CUSTOM OBJECT
	OBJ_ACTOR m_player;
	OBJ_ACTOR m_Target_VerticalLEFT[600];
	OBJ_ACTOR m_Target_VerticalRIGHT[600];
	OBJ_ACTOR m_Target_HorizontalUP[600];
	OBJ_ACTOR m_Target_HorizontalDOWN[600];	
	int m_TargetIndex[4];
	D3DXVECTOR3 m_vStartPos;
	Sound sound;
	Axis m_Axis;
	OBJ_Ground m_ground;
	OBJ_Cube m_CUBE;

	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;	
	int m_m_CamZoomSectionCount;
	int *m_CamZoomSection;
	int m_NumofPlayerBullet;

private:
	//COLLIDER
	bool CheckTrigger(OBJ_ACTOR col1, OBJ_ACTOR col2);
	bool CheckTrigger(Figure col1, OBJ_ACTOR col2);
	void SetDrawingText(int fontSizeIndex, LPWSTR str, D3DXCOLOR color, int leftRect, int uprect, int rightRect, int downRect);

public:
	//Dialog 창으로 로드와 세팅을 하기 위한 공개변수
	D3DMATERIAL9 m_Material;
	D3DLIGHT9 m_Light;

public:
	//Dialog 창으로 로드와 세팅을 하기 위한 공개함수
	void SetMaterial(float r, float g, float b);
	D3DCOLORVALUE GetMaterial();	
	void SetDirectionalLight();
	void SetModel(CHK_MODEL cm);
	void SetModelSize(float input);
	float GetModelSize();
};

