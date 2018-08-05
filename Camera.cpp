#include "stdafx.h"
#include "Camera.h"


void Camera::SetInit(LPDIRECT3DDEVICE9 d3ddevice)
{
	m_D3Ddevice = d3ddevice;
	m_vp.X = 0;
	m_vp.Y = 0;;
	m_vp.Width = 600;
	m_vp.Height = 600;
	m_vp.MinZ = 0.0f;
	m_vp.MaxZ = 1.0f;

	m_Eye.x = 0.0f;
	m_Eye.y = 0.0f;
	m_Eye.z = 0.0f;

	m_At.x = 0.0f;
	m_At.y = 0.0f;
	m_At.z = 0.0f;

	m_Up.x = 0.0f;
	m_Up.y = 1.0f;
	m_Up.z = 0.0f;
}
void Camera::SetViewPort(DWORD x, DWORD  y, DWORD  width, DWORD  height, float minZ, float maxZ)
{
	m_vp.X = x;
	m_vp.Y = y;
	m_vp.Width = width;
	m_vp.Height = height;
	m_vp.MinZ = minZ;
	m_vp.MaxZ = maxZ;
	TransformCameraMatrix();
}
void Camera::SetCameraPos(float x, float y, float z)
{
	m_Eye.x = x;
	m_Eye.y = y;
	m_Eye.z = z;
	TransformCameraMatrix();	
}

void Camera::SetTargetPos(float x, float y, float z)
{
	m_At.x = x;
	m_At.y = y;
	m_At.z = z;
	TransformCameraMatrix();	
}
void Camera::SetViewUp(float x, float y, float z)
{
	m_Up.x = x;
	m_Up.y = y;
	m_Up.z = z;
	TransformCameraMatrix();
}

void Camera::TransformCameraMatrix()
{
	D3DXMatrixLookAtLH(&m_matrixView, &m_Eye, &m_At, &m_Up);
	m_D3Ddevice->SetTransform(D3DTS_VIEW, &m_matrixView);

	D3DXMatrixPerspectiveFovLH(&m_matrixProjection, D3DX_PI / 4, 1.0f, 0.0f, 1.0f);
	m_D3Ddevice->SetTransform(D3DTS_PROJECTION, &m_matrixProjection);

	m_D3Ddevice->SetViewport(&m_vp);	
}
void Camera::ZoomFunc(int timer, int sectionCount, int* Section)
{	
		if (timer < Section[0]) SetCameraPos(GetCameraPos().x + 0.18f, GetCameraPos().y - 0.3f, GetCameraPos().z);
		else if (timer > Section[1] && timer < Section[2]) SetCameraPos(GetCameraPos().x + 0.01f, GetCameraPos().y + 0.1f, GetCameraPos().z);
		else if (timer > Section[3] && timer < Section[4]) SetCameraPos(GetCameraPos().x - 0.013f, GetCameraPos().y + 0.01f, GetCameraPos().z);
		else if (timer > Section[5] && timer < Section[6]) SetCameraPos(GetCameraPos().x + 0.2f, GetCameraPos().y - 0.33f, GetCameraPos().z);
		else if (timer > Section[7] && timer < Section[8]) SetCameraPos(GetCameraPos().x - 0.07f, GetCameraPos().y + 0.15f, GetCameraPos().z);
		else if (timer > Section[9] && timer < Section[10]) SetCameraPos(GetCameraPos().x - 0.003f, GetCameraPos().y + 0.05f, GetCameraPos().z);
		else if (timer > Section[11] && timer < Section[12]) SetCameraPos(GetCameraPos().x, GetCameraPos().y - 0.002f, GetCameraPos().z - 0.003f);
}

D3DXVECTOR3 Camera::GetCameraPos()
{
	return m_Eye;
}
D3DXVECTOR3 Camera::GetTargetPos()
{
	return m_At;
}
D3DXVECTOR3 Camera::GetViewUpPos()
{
	return m_Up;
}

void Camera::OnRelease()
{
	if(m_D3Ddevice!= NULL)m_D3Ddevice->Release();
}