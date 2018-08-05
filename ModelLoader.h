#pragma once
#include <d3dx9.h>
#include <string.h>
//x파일 로더
class ModelLoader
{
private:
	LPDIRECT3DDEVICE9 m_pd3ddevice;

	LPD3DXMESH m_pMesh ;

	D3DMATERIAL9 *m_pMeshMaterial ;
	LPDIRECT3DTEXTURE9* m_pMeshTexture  ;

	LPD3DXBUFFER m_pMeshMaterialBuff  ;
	DWORD m_dwNumOfMaterial;

	LPDIRECT3DVERTEXBUFFER9 m_pVb  ;

	D3DXMATRIX m_matScale, m_matTranslate, m_matRotate;
	
public:
	void Oninit(LPDIRECT3DDEVICE9 pd3ddevice, LPCWSTR str);
	void OnRender();
	void OnRelease();

	D3DXVECTOR3 m_vPos, m_vRot, m_vScale;
};

