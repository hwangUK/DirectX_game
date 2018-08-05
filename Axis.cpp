#include "stdafx.h"
#include "Axis.h"
#include <d3dx9math.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	float X, Y, Z;
	DWORD Color;
};

void Axis::OnInit(LPDIRECT3DDEVICE9 pd3dDevice) {

	m_pD3Ddevice = pd3dDevice;

	CUSTOMVERTEX vertices[] =
	{
		{ -30.0f,0.0f,0.0f, D3DCOLOR_RGBA(255,0,0,255) },
		{ 30.0f,0.0f,0.0f, D3DCOLOR_RGBA(255,0,0,255) },

		{ 0.0f,-30.0f,0.0f, D3DCOLOR_RGBA(0,255,0,255) },
		{ 0.0f,30.0f,0.0f, D3DCOLOR_RGBA(0,255,0,255) },

		{ 0.0f,0.0f,-30.0f, D3DCOLOR_RGBA(0,255,255,255) },
		{ 0.0f,0.0f,30.0f, D3DCOLOR_RGBA(0,255,255,255) }
	};
	//create vertexbuffer
	m_pD3Ddevice->CreateVertexBuffer(6 * sizeof(CUSTOMVERTEX),0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT,&m_pVB,NULL);

	//copy array vertices to vertexbuffer through pVertices pointer
	void *pVertices;
	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

}

void Axis::OnRender() {

	//@-World Transform / Axis fixing on world
	D3DXMATRIX matrixWorld;
	D3DXMatrixIdentity(&matrixWorld);	
	m_pD3Ddevice->SetTransform(D3DTS_WORLD, &matrixWorld);
	//------

	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pD3Ddevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pD3Ddevice->SetFVF(D3DFVF_CUSTOMVERTEX);	
	m_pD3Ddevice->DrawPrimitive(D3DPT_LINELIST, 0, 3);
	
	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}

void Axis::OnRelease() {
	
	if (m_pVB != NULL) m_pVB->Release();
	//if (m_pD3Ddevice != NULL) m_pD3Ddevice->Release();
}