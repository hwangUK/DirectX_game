#pragma once
#include <d3dx9math.h>

class OBJ_Cube
{
private:
	LPDIRECT3DDEVICE9 m_pD3Ddevice;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	LPDIRECT3DTEXTURE9 tex;

	D3DXMATRIX m_matTranslate;
	D3DXMATRIX m_matScale;
	D3DXMATRIX m_matRotate;

	D3DXVECTOR3 m_nomal[6];
public:
	void OnInit(LPDIRECT3DDEVICE9 D3Ddevice);
	void OnRender();
	void OnRelease();

	void SetMatrixTranslate(float x, float y, float z);
	void SetMatrixScale(float x, float y, float z);
	void SetMatrixRotate(float x, float y, float z);

	

};

