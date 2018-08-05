#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct  GROUNDVERTEX
{
	D3DXVECTOR3 vPos;
	DWORD dwColor;
};

class OBJ_Ground
{
private:
	DWORD m_dwNumVertices;
	DWORD m_dwNumIndices;

	LPDIRECT3DINDEXBUFFER9 m_pIB;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

	LPDIRECT3DDEVICE9 m_pD3Ddevice;

	int m_Row;
	int m_Col;
	int m_totalSize;

public:

	void OnCreate( LPDIRECT3DDEVICE9 pd3ddevice, int nRow, int nCol, float fsize);
	void OnRender();
	void OnRelease();

};

