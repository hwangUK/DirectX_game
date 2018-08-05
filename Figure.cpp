#include "stdafx.h"
#include "Figure.h"

void Figure::OnInit(LPDIRECT3DDEVICE9 D3Ddevice){
	m_pD3Ddevice = D3Ddevice;

	//VERTEX BUFFER
	CUSTOMVERTEX2 Vertices[12] =
	{
		
		{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },
		{ D3DXVECTOR3(1.0f,0.0f,1.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },
		{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },
		
		{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },		
		{ D3DXVECTOR3(0.0f,2.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },
		{ D3DXVECTOR3(1.0f,0.0f,1.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },		
		
		{ D3DXVECTOR3(1.0f,0.0f,1.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },		
		{ D3DXVECTOR3(0.0f,2.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },
		{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },			
		
		{ D3DXVECTOR3(-1.0f,0.0f,1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },			
		{ D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DXVECTOR3(0.0f,0.0f,0.0f) },
		{ D3DXVECTOR3(0.0f,2.0f,0.0f), D3DXVECTOR3(0.0f,0.0f,0.0f) },
	};

	//Cross Vector 법선벡터 방향 계산
	D3DXVECTOR3 vS0, vS1;
	vS0 = Vertices[2].position - Vertices[0].position;
	vS1 = Vertices[1].position - Vertices[0].position;
	D3DXVec3Cross(&m_nomal[0], &vS0, &vS1);
	D3DXVec3Normalize(&m_nomal[0], &m_nomal[0]);	

	D3DXVECTOR3 vS2, vS3;
	vS2 = Vertices[4].position - Vertices[3].position;
	vS3 = Vertices[5].position - Vertices[3].position;
	D3DXVec3Cross(&m_nomal[1], &vS3, &vS2);
	D3DXVec3Normalize(&m_nomal[1], &m_nomal[1]);

	D3DXVECTOR3 vS4, vS5;
	vS4 = Vertices[7].position - Vertices[6].position;
	vS5 = Vertices[8].position - Vertices[6].position;
	D3DXVec3Cross(&m_nomal[2], &vS5, &vS4);
	D3DXVec3Normalize(&m_nomal[2], &m_nomal[2]);

	D3DXVECTOR3 vS6, vS7;
	vS6 = Vertices[10].position - Vertices[9].position;
	vS7 = Vertices[11].position - Vertices[9].position;
	D3DXVec3Cross(&m_nomal[3], &vS7, &vS6);
	D3DXVec3Normalize(&m_nomal[3], &m_nomal[3]);

	//CrossVector Line 법선벡터 정점 라인리스트그리기 설정
	CROSSVERTEX vCrossvertices[24];

	vCrossvertices[0].vPos = Vertices[0].position;
	vCrossvertices[1].vPos = Vertices[0].position + m_nomal[0];
	vCrossvertices[2].vPos = Vertices[1].position;
	vCrossvertices[3].vPos = Vertices[1].position + m_nomal[0];
	vCrossvertices[4].vPos = Vertices[2].position;
	vCrossvertices[5].vPos = Vertices[2].position + m_nomal[0];
	//////////////////////////////////////////////////////////////	
	vCrossvertices[6].vPos = Vertices[3].position;
	vCrossvertices[7].vPos = Vertices[3].position + m_nomal[1];	
	vCrossvertices[8].vPos = Vertices[4].position;
	vCrossvertices[9].vPos = Vertices[4].position + m_nomal[1];
	vCrossvertices[10].vPos = Vertices[5].position;
	vCrossvertices[11].vPos = Vertices[5].position + m_nomal[1];
	//////////////////////////////////////////////////////////////	
	vCrossvertices[12].vPos = Vertices[6].position;
	vCrossvertices[13].vPos = Vertices[6].position + m_nomal[2];
	vCrossvertices[14].vPos = Vertices[7].position;
	vCrossvertices[15].vPos = Vertices[7].position + m_nomal[2];
	vCrossvertices[16].vPos = Vertices[8].position;
	vCrossvertices[17].vPos = Vertices[8].position + m_nomal[2];
	//////////////////////////////////////////////////////////////
	vCrossvertices[18].vPos = Vertices[9].position;
	vCrossvertices[19].vPos = Vertices[9].position + m_nomal[3];
	vCrossvertices[20].vPos = Vertices[10].position;
	vCrossvertices[21].vPos = Vertices[10].position + m_nomal[3];
	vCrossvertices[22].vPos = Vertices[11].position;
	vCrossvertices[23].vPos = Vertices[11].position + m_nomal[3];
	//////////////////////////////////////////////////////////////

	//CrossVector Nomal Custom 법선벡터 합성
	Vertices[0].vNomalVector = m_nomal[0] + m_nomal[3];
	Vertices[1].vNomalVector = m_nomal[0] + m_nomal[2]; 
	Vertices[2].vNomalVector = m_nomal[0];

	Vertices[3].vNomalVector = m_nomal[1] + m_nomal[0];
	Vertices[4].vNomalVector = m_nomal[1] + m_nomal[1]; 
	Vertices[5].vNomalVector = m_nomal[1];

	Vertices[6].vNomalVector = m_nomal[2] + m_nomal[1];
	Vertices[7].vNomalVector = m_nomal[2] + m_nomal[2];
	Vertices[8].vNomalVector = m_nomal[2];

	Vertices[9].vNomalVector = m_nomal[0] + m_nomal[2];
	Vertices[10].vNomalVector = m_nomal[0] + m_nomal[3];
	Vertices[11].vNomalVector = m_nomal[3];

	m_pD3Ddevice->CreateVertexBuffer(sizeof(Vertices), 0, D3DFVF_XYZ | D3DFVF_NORMAL, D3DPOOL_DEFAULT, &m_pVB, NULL);
	void* vpVertices;
	m_pVB->Lock(0, sizeof(Vertices), &vpVertices, 0);
	memcpy(vpVertices, Vertices, sizeof(Vertices));
	m_pVB->Unlock();

	m_pD3Ddevice->CreateVertexBuffer(sizeof(vCrossvertices), 0, D3DFVF_XYZ | D3DFVF_NORMAL, D3DPOOL_DEFAULT, &m_pCrossVB, NULL);
	void* vpCross;
	m_pCrossVB->Lock(0, sizeof(vCrossvertices), &vpCross, 0);
	memcpy(vpCross, vCrossvertices, sizeof(vCrossvertices));
	m_pCrossVB->Unlock();

}

void Figure::OnRender(){
	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pD3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pD3Ddevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	m_pD3Ddevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX2));
	m_pD3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pD3Ddevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);

	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//CRE Line
	m_pD3Ddevice->SetStreamSource(0, m_pCrossVB, 0, sizeof(CROSSVERTEX));
	m_pD3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL);
	m_pD3Ddevice->DrawPrimitive(D3DPT_LINELIST, 0, 12);	
}

void Figure::OnRelease(){
	if (m_pVB != NULL) m_pVB->Release();
	if (m_pCrossVB != NULL) m_pCrossVB->Release();
	if (m_pD3Ddevice != NULL) m_pD3Ddevice->Release();
	if (m_pBulletMesh != NULL) m_pBulletMesh->Release();
}


////////////////////////////////////////////////////////////// BULLET

void Figure::InitMakeFire(float Radius, float Scale) {
	D3DXCreateSphere(m_pD3Ddevice, Radius, 3, 2, &m_pBulletMesh, NULL);
	m_BulletRadius = Radius;
	m_BulletScale = Scale;
	//SetLife(1);
}

void Figure::Fire(int index, float speed){
	if (GetLife() > 0) {
		if (index == 0 ) m_vBulletPos.z += speed;	
		else if (index == 1) m_vBulletPos.x -= speed;	
		else if (index == 2) m_vBulletPos.z += speed / 2;
		else if (index == 3) m_vBulletPos.x -= speed / 2;
		D3DXMatrixScaling(&m_matScaleFire, m_BulletScale, m_BulletScale, m_BulletScale);
		D3DXMatrixTranslation(&m_matTranslateFire, m_vBulletPos.x, m_vBulletPos.y, m_vBulletPos.z);
	}	
}

void Figure::RenderFire(){
	if (GetLife() > 0) {
		D3DXMATRIX world;
		world = m_matScaleFire * m_matTranslateFire;
		m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE);		
		m_pD3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_pD3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
		m_pD3Ddevice->SetTransform(D3DTS_WORLD, &world);
		m_pBulletMesh->DrawSubset(0);
	}
}

void Figure::SetBulletPos(D3DXVECTOR3 vbulletpos){
	m_vBulletPos = vbulletpos;
	D3DXMatrixTranslation(&m_matTranslateFire, m_vBulletPos.x, m_vBulletPos.y, m_vBulletPos.z);
}

D3DXVECTOR3 Figure::GetBulletPos(){
	return m_vBulletPos;
}

void Figure::SetLife(int life){
	m_life = life;
}
int Figure::GetLife(){
	return m_life;
}