#pragma once
#include <d3dx9math.h>

struct SPRITEVERTEX {
	D3DXVECTOR3 vPos;
	float u;
	float v;
};

class Sprite
{
private:
	LPDIRECT3DDEVICE9 m_D3Ddevice;

	LPDIRECT3DVERTEXBUFFER9 m_pVb;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXMATRIX m_matWorld , matScaling, matTranlate, matRotation;
	float m_u;
	float m_v;
	wchar_t strFilename;

public:
	void OnInit(LPDIRECT3DDEVICE9 device);
	void CreateImage(LPCWSTR fileLocation);
	void OnRender();
	void OnRelease();
	void SetRatation(float x, float y, float z);
	void SetTransform(float x, float y, float z);
	void SetScale(float x, float y, float z);
};

