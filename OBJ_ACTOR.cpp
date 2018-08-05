#include "stdafx.h"
#include "OBJ_ACTOR.h"

void OBJ_ACTOR::OnInit(LPDIRECT3DDEVICE9 d3ddevice, int life, float speed, LPD3DXMESH mesh, BOOL ISPLAYER, int NumofHelper) {	

	D3DXCreateTextureFromFile(m_D3Ddevice, TEXT("image\\Texture0.dds"), &tex);
	m_D3Ddevice = d3ddevice;
	m_mesh = mesh;
	m_fRadius = 0.5f;
	D3DXCreateSphere(m_D3Ddevice, m_fRadius, 22, 22, &m_mesh, NULL);

	m_nLife = life;
	m_fSpeed = speed;		
	m_bIsPlayer = ISPLAYER;
	m_dwSpawnTime =0;
	m_theta = 0;	
	CHECKMODEL = DEFAULT;
	m_nNumOfHelpaer = NumofHelper;
	SetTransform(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
	SetScale(1.0f);	
	//Init SubObject"Helper"
	if (m_bIsPlayer) {
		for (int i = 0; i < m_nNumOfHelpaer; i++) {
			m_Helper[i].OnInit(m_D3Ddevice);
			m_Helper[i].InitMakeFire(0.8f, 1.0f);
		}		
	}
}

void OBJ_ACTOR::InitModelLoad(CHK_MODEL ModelENuM) {	
	//Open Actor 3DModel 모델 불러오기
	CHECKMODEL = ModelENuM;
	switch (ModelENuM) {
	case DEFAULT:
		break;
	case AIR:
		SetRotation(1.5f, 0.0f, 0.0f);
		SetScale(1.0f);
		m_modelLoder.Oninit(m_D3Ddevice, TEXT("model\\Air.x"));
		break;
	case TIGER:
		SetRotation(3.0f, 0.0f, 0.0f);
		SetScale(1.0f);
		m_modelLoder.Oninit(m_D3Ddevice, TEXT("model\\Tiger.x"));
		break;
	case FLY:
		SetRotation(0.0f, 0.0f, 0.0f);
		SetScale(0.01f);
		m_modelLoder.Oninit(m_D3Ddevice, TEXT("model\\flying_sparrow.x"));
		break;
	default:
		break;
	}		
}

void OBJ_ACTOR::OnRender() {	
	
	if (CHECKMODEL == DEFAULT) {
		m_D3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		m_D3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		m_D3Ddevice->SetTexture(0, tex);
		m_D3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
		m_D3Ddevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		m_mesh->DrawSubset(0);
	}
	else {
		RenderSetOrigin();
	}
	if (m_bIsPlayer) {
		//총알 초기위치를 현재 오브젝트 위치로 초기화시켜준 후에 발사해야함		
		switch (CHECKMODEL) {
		case DEFAULT:
			RenderSetSubObjTransform(0, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[0].x, m_vSubObjPos[0].y, m_vSubObjPos[0].z);
			RenderSetSubObjTransform(1, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[1].x, m_vSubObjPos[1].y, m_vSubObjPos[1].z);
			for(int i=0; i< 2;i++) m_Helper[i].RenderFire();
			break;
		case AIR:
			RenderSetSubObjTransform(0, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[0].x, m_vSubObjPos[0].y, m_vSubObjPos[0].z);
			RenderSetSubObjTransform(1, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[1].x, m_vSubObjPos[1].y, m_vSubObjPos[1].z);
		    RenderSetSubObjTransform(2, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[2].x, m_vSubObjPos[2].y, m_vSubObjPos[2].z);
			RenderSetSubObjTransform(3, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[3].x, m_vSubObjPos[3].y, m_vSubObjPos[3].z);
			for (int i = 0; i< m_nNumOfHelpaer; i++) m_Helper[i].RenderFire();
			break;
		case TIGER:
			RenderSetSubObjTransform(0, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[0].x, m_vSubObjPos[0].y, m_vSubObjPos[0].z);
			for (int i = 0; i< 1; i++) m_Helper[i].RenderFire();
			break;
		case FLY:
			RenderSetSubObjTransform(0, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[0].x, m_vSubObjPos[0].y, m_vSubObjPos[0].z);
			RenderSetSubObjTransform(1, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[1].x, m_vSubObjPos[1].y, m_vSubObjPos[1].z);
			RenderSetSubObjTransform(2, 0.4f, 0.4f, 0.4f, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z, m_vSubObjPos[2].x, m_vSubObjPos[2].y, m_vSubObjPos[2].z);
			for (int i = 0; i< m_nNumOfHelpaer-1; i++) m_Helper[i].RenderFire();
			break;
		default:
			break;
		}		
	}
}
	
void OBJ_ACTOR::OnUpdate() {
	//update Actor 
	UpdateMatrixOrigin();
	if (m_bIsPlayer) {
		//update "Helper" CycleRotate 궤도 회전값 업데이트
		m_theta += 0.8f;
		if (m_theta >= 1080.f) m_theta = 0.f;
		//update Actor LocalRotate 오브젝트 자체회전값 업데이트
		m_fSubObjRotation.x += 0.05f;
		m_fSubObjRotation.y += 0.05f;
		m_fSubObjRotation.z += 0.05f;
		SetCycleRotationX(1.5f, 0.05f, m_theta);
		SetCycleRotationZ(1.5f, 0.1f, m_theta);
		SetCycleRotationY(1.0f, 0.03f, m_theta);
		switch (CHECKMODEL) {
		case DEFAULT:
			m_vSubObjPos[0] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosZ.x, m_vPos.y + m_vCycleRotationPosZ.y, m_vPos.z + m_vCycleRotationPosZ.z);
			m_vSubObjPos[1] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosX.x, m_vPos.y + m_vCycleRotationPosX.y, m_vPos.z + m_vCycleRotationPosX.z);	
			break;
		case AIR:	
		    m_vSubObjPos[0] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosZ.x, m_vPos.y + m_vCycleRotationPosZ.y, m_vPos.z + m_vCycleRotationPosZ.z);
		    m_vSubObjPos[1] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosX.x, m_vPos.y + m_vCycleRotationPosX.y, m_vPos.z + m_vCycleRotationPosX.z);
		    m_vSubObjPos[2] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosY.x, m_vPos.y + m_vCycleRotationPosY.y, m_vPos.z + m_vCycleRotationPosY.z);//m_vSubObjPos[3] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosX.x * m_vCycleRotationPosZ.x, m_vPos.y + m_vCycleRotationPosX.y * m_vCycleRotationPosZ.y, m_vPos.z + m_vCycleRotationPosX.z * m_vCycleRotationPosZ.z);
			m_vSubObjPos[3] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosY.x+ 1.f, m_vPos.y + m_vCycleRotationPosY.y+1.f, m_vPos.z + m_vCycleRotationPosY.z+1.f);		
			break;
		case TIGER: 
			m_vSubObjPos[0] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosZ.x, m_vPos.y + m_vCycleRotationPosZ.y, m_vPos.z + m_vCycleRotationPosZ.z);			
			break;
		case FLY: 
			m_vSubObjPos[0] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosZ.x, m_vPos.y + m_vCycleRotationPosZ.y, m_vPos.z + m_vCycleRotationPosZ.z);
			m_vSubObjPos[1] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosX.x, m_vPos.y + m_vCycleRotationPosX.y, m_vPos.z + m_vCycleRotationPosX.z);
			m_vSubObjPos[2] = D3DXVECTOR3(m_vPos.x + m_vCycleRotationPosY.x, m_vPos.y + m_vCycleRotationPosY.y, m_vPos.z + m_vCycleRotationPosY.z);		
			break;
		default:
			break;
		}
		//위치에서 발사
		if (FireOn[0] == TRUE) {
			m_Helper[0].Fire(0, 0.3f);
			if (m_Helper[0].GetBulletPos().z > m_vSubObjPos[0].z + 35.f) FireOn[0] = FALSE;
		}
		else {
			//총알을 헬퍼위치에 Update
			m_Helper[0].SetBulletPos(m_vSubObjPos[0]);
			SetBulletLife(1, 0);
		}
		if (FireOn[1] == TRUE) {
			m_Helper[1].Fire(1, 0.3f);
			if (m_Helper[1].GetBulletPos().x < m_vSubObjPos[1].x - 35.f) FireOn[1] = FALSE;
		}
		else {			
			m_Helper[1].SetBulletPos(m_vSubObjPos[1]);
			SetBulletLife(1, 1);
		}
		if (FireOn[2] == TRUE) {
			m_Helper[2].Fire(2, 0.4f);
			if (m_Helper[2].GetBulletPos().z > m_vSubObjPos[2].z + 35.f) FireOn[2] = FALSE;
		}
		else {
			m_Helper[2].SetBulletPos(m_vSubObjPos[2]);
			SetBulletLife(1, 2);
		}
		if (FireOn[3] == TRUE) {
			m_Helper[3].Fire(3, 0.5f);
			if (m_Helper[3].GetBulletPos().x < m_vSubObjPos[3].x - 35.f) FireOn[3] = FALSE;
		}
		else {
			m_Helper[3].SetBulletPos(m_vSubObjPos[3]);
			SetBulletLife(1, 3);
		}
	}
}

void OBJ_ACTOR::OnRelease() {	
	
	for(int i=0; i< m_nNumOfHelpaer;i++) m_Helper[i].OnRelease();
	if (tex != NULL) tex->Release();
	//m_modelLoder.OnRelease();
	if (m_D3Ddevice != NULL)m_D3Ddevice->Release();
}

// Function of Using in this class
 //Update Actor
void OBJ_ACTOR::UpdateMatrixOrigin() {
	D3DXMatrixScaling(&m_matScale, m_fScale, m_fScale, m_fScale);
	D3DXMatrixRotationYawPitchRoll(&m_matRotation, m_fRotation.x, m_fRotation.y, m_fRotation.z);
	D3DXMatrixTranslation(&m_matTranslation, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = m_matScale * m_matRotation * m_matTranslation;
}
//Render Actor
void OBJ_ACTOR::RenderSetOrigin() {
	m_D3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_D3Ddevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_modelLoder.OnRender();
	m_D3Ddevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
 //Render & Update SubObject"Helper"
void OBJ_ACTOR::RenderSetSubObjTransform(int index, float sx, float sy, float sz, float rx, float ry, float rz, float tx, float ty, float tz) {
	m_fSubObjRotation = D3DXVECTOR3(rx, ry, rz);
	m_fSubObjScale = sx;

	D3DXMatrixScaling(&m_SubObjmatScale, m_fSubObjScale, m_fSubObjScale, m_fSubObjScale);
	D3DXMatrixRotationYawPitchRoll(&m_SubObjmatRotation, m_fSubObjRotation.x, m_fSubObjRotation.y, m_fSubObjRotation.z);
	D3DXMatrixTranslation(&m_SubObjmatTranslation, tx, ty, tz);

	m_SubObjmatWorld = m_SubObjmatScale * m_SubObjmatRotation * m_SubObjmatTranslation;
	m_D3Ddevice->SetTransform(D3DTS_WORLD, &m_SubObjmatWorld);
	m_Helper[index].OnRender();
}

//SET -------------------------
  //Actor function
void OBJ_ACTOR::SetLife(int life) {
	m_nLife = life;
}

void OBJ_ACTOR::SetTransform(float posX, float posY, float posZ) {
	m_vPos.x = posX;
	m_vPos.y = posY;
	m_vPos.z = posZ;
}

void OBJ_ACTOR::SetRotation(float rX, float rY, float rZ) {
	m_fRotation.x = rX;
	m_fRotation.y = rY;
	m_fRotation.z = rZ;
}
void OBJ_ACTOR::SetScale(float scale) {
	m_fScale = scale;
}
void OBJ_ACTOR::SetSpawnTime(DWORD time) {
	m_dwSpawnTime = time;
}
  //subobject function
void OBJ_ACTOR::SetCycleRotationX(float Radius, float Speed, double theta) {
	theta *= Speed;
	m_vCycleRotationPosX.x = 0.f;
	m_vCycleRotationPosX.y = (Radius *  cos(theta));// +(-Radius * sin(theta));
	m_vCycleRotationPosX.z = (Radius *  sin(theta));// +(Radius * sin(theta));
}

void OBJ_ACTOR::SetCycleRotationY(float Radius, float Speed, double theta) {
	theta *= Speed ;
	m_vCycleRotationPosY.x = (Radius *  cos(theta));// +(-Radius * sin(theta));
	m_vCycleRotationPosY.y = 0.f;
	m_vCycleRotationPosY.z = (Radius *  sin(theta));// +(Radius * sin(theta));
}

void OBJ_ACTOR::SetCycleRotationZ(float Radius, float Speed, double theta) { 
	theta *= Speed;
	m_vCycleRotationPosZ.x = (Radius *  cos(theta));// +(-Radius * sin(theta));
	m_vCycleRotationPosZ.y = (Radius *  sin(theta));// +(Radius * sin(theta));
	m_vCycleRotationPosZ.z = 0.f;
}

void OBJ_ACTOR::SetBulletLife(int life, int index) {
	m_Helper[index].SetLife(life);
}
//GET -------------------------


int OBJ_ACTOR::GetLife() {
	return m_nLife;
}
float OBJ_ACTOR::GetScale() {
	return m_fScale;
}
float OBJ_ACTOR::GetSpeed() {
	return m_fSpeed;
}

D3DXVECTOR3 OBJ_ACTOR::GetPos() {
	return m_vPos;
}

float OBJ_ACTOR::GetRadius() {
	return m_fRadius;
}

DWORD OBJ_ACTOR::GetSpawnTime() {
	return m_dwSpawnTime;
}

LPD3DXMESH OBJ_ACTOR::GetMesh() {
	return m_mesh;
}

Figure OBJ_ACTOR::GetBulletFigure(int index) {
	return m_Helper[index];
}

int OBJ_ACTOR::GetBulletLife(int index) {
	return m_Helper[index].GetLife();
}
