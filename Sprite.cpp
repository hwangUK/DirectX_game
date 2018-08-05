#include "stdafx.h"
#include "Sprite.h"

void Sprite::OnInit(LPDIRECT3DDEVICE9 device) {
	m_D3Ddevice = device;
}

void Sprite::CreateImage( LPCWSTR fileLocation) {	
	
	SPRITEVERTEX vVertices[4] = {
		{ D3DXVECTOR3(-1.0f,0.0f,1.0f),0.f,0.f},
		{ D3DXVECTOR3(1.0f,0.0f,1.0f),1.f,0.0f},
		{ D3DXVECTOR3(-1.0f,0.0f,-1.0f),0.f,1.f },
		{ D3DXVECTOR3(1.0f,0.0f,-1.0f),1.0f,1.0f},
	};	

	m_D3Ddevice->CreateVertexBuffer(sizeof(vVertices), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1, D3DPOOL_DEFAULT, &m_pVb, NULL);
	VOID* tmpVertex;
	m_pVb->Lock(0, sizeof(vVertices), (VOID**)&tmpVertex, 0);
	memcpy(tmpVertex, vVertices, sizeof(vVertices));
	m_pVb->Unlock();

	if( FAILED(D3DXCreateTextureFromFile(m_D3Ddevice, fileLocation, &m_pTexture)) ) return;
	//

	D3DXMatrixScaling(&matScaling, 2.f, 2.f, 2.f);
	D3DXMatrixTranslation(&matTranlate, 0.f, 0.f, 0.f);	
	D3DXMatrixRotationYawPitchRoll(&matRotation, 1.6f, 0.f, 0.f);
		
}
void Sprite::OnRender()
{
	m_D3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_D3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_D3Ddevice->SetTexture(0, m_pTexture);
	m_D3Ddevice->SetStreamSource(0, m_pVb, 0, sizeof(SPRITEVERTEX));
	m_D3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	m_matWorld = matScaling * matRotation * matTranlate;
	m_D3Ddevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_D3Ddevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	m_D3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
void Sprite::OnRelease(){	
	if (m_pVb != NULL) m_pVb->Release();
	if (m_pTexture != NULL) m_pTexture->Release();
	if (m_D3Ddevice != NULL) m_D3Ddevice->Release();
}

void Sprite::SetRatation(float x, float y, float z)
{
	D3DXMatrixRotationYawPitchRoll(&matRotation, x, y, z);
}

void Sprite::SetTransform(float x, float y, float z)
{
	D3DXMatrixTranslation(&matTranlate, x, y, z);
}

void Sprite::SetScale(float x, float y, float z)
{
	D3DXMatrixScaling(&matScaling, x, y, z);
}