#include "stdafx.h"
#include "OBJ_Cube.h"
#include <d3dx9math.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ| D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;
	DWORD color;
};

void OBJ_Cube::OnInit(LPDIRECT3DDEVICE9 D3Ddevice)
{
	m_pD3Ddevice = D3Ddevice;

	//VERTEX BUFFER
	//D3DXCreateTextureFromFile(m_pD3Ddevice, TEXT("image\\Texture1.dds"), &tex);

	CUSTOMVERTEX Vertices[] =
	{
		{ D3DXVECTOR3(-1.0f,1.0f,1.0f), D3DCOLOR_RGBA(255,0,255,255)},
		{ D3DXVECTOR3(1.0f,1.0f,1.0f), D3DCOLOR_RGBA(0,255,0,255)},
		{ D3DXVECTOR3(1.0f,1.0f,-1.0f), D3DCOLOR_RGBA(0,0,255,255)},
		{ D3DXVECTOR3(-1.0f,1.0f,-1.0f), D3DCOLOR_RGBA(255,255,0,255)},

		{ D3DXVECTOR3(-1.0f,-1.0f,1.0f), D3DCOLOR_RGBA(255,0,0,255),},
		{ D3DXVECTOR3(1.0f,-1.0f,1.0f), D3DCOLOR_RGBA(0,255,10,255),},
		{ D3DXVECTOR3(1.0f,-1.0f,-1.0f), D3DCOLOR_RGBA(0,0,255,255),},
		{ D3DXVECTOR3(-1.0f,-1.0f,-1.0f), D3DCOLOR_RGBA(255,0,0,255)}
	};	

	m_pD3Ddevice->CreateVertexBuffer(sizeof(Vertices), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);

	void* pVertexBuffer;
	m_pVB->Lock(0, sizeof(Vertices), &pVertexBuffer, 0);
	memcpy(pVertexBuffer, Vertices, sizeof(Vertices));
	m_pVB->Unlock();

	//INDEX BUFFER

	WORD Indices[] =
	{
		0,1,2,
		0,2,3,

		4,6,5,
		4,7,6,

		0,3,7,
		0,7,4,

		1,5,6,
		1,6,2,

		3,2,6,
		3,6,7,

		0,4,5,
		0,5,1
	};

	m_pD3Ddevice->CreateIndexBuffer(sizeof(Indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);

	void* pIndexBuffer;
	m_pIB->Lock(0, sizeof(Indices), &pIndexBuffer, 0);
	memcpy(pIndexBuffer, Indices, sizeof(Indices));
	m_pIB->Unlock();
}

void OBJ_Cube::OnRender()
{
	D3DXMATRIX matrixWorld;
	D3DXMatrixIdentity(&matrixWorld);
	matrixWorld = m_matScale * m_matRotate * m_matTranslate;

	m_pD3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pD3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pD3Ddevice->SetTransform(D3DTS_WORLD, &matrixWorld);
	m_pD3Ddevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3Ddevice->SetIndices(m_pIB);
	m_pD3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_pD3Ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 6*2);
	//
	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

}

void OBJ_Cube::OnRelease()
{
	if (m_pVB != NULL) m_pVB->Release();
	if (m_pIB != NULL) m_pIB->Release();
	if (m_pD3Ddevice != NULL) m_pD3Ddevice->Release();
}

void OBJ_Cube::SetMatrixTranslate(float x, float y, float z)
{
	D3DXMatrixTranslation(&m_matTranslate,x,y,z);
}

void OBJ_Cube::SetMatrixScale(float x, float y, float z)
{
	D3DXMatrixScaling(&m_matScale, x, y, z);
}
void OBJ_Cube::SetMatrixRotate(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(&m_matRotate ,x, y, z);
}