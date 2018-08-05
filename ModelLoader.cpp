#include "stdafx.h"
#include "ModelLoader.h"


void ModelLoader::Oninit(LPDIRECT3DDEVICE9 pd3ddevice , LPCWSTR str) {

	m_pd3ddevice = pd3ddevice;
	LPD3DXBUFFER ptmpMaterialBuffer;

	if(FAILED(D3DXLoadMeshFromX(str, D3DXMESH_SYSTEMMEM, m_pd3ddevice, NULL, &m_pMeshMaterialBuff, NULL, &m_dwNumOfMaterial, &m_pMesh))) MessageBeep(1);
	
	
	D3DXMATERIAL* d3dxMaterial = (D3DXMATERIAL*)m_pMeshMaterialBuff->GetBufferPointer();
	
	m_pMeshMaterial = new D3DMATERIAL9[m_dwNumOfMaterial];
	m_pMeshTexture = new LPDIRECT3DTEXTURE9[m_dwNumOfMaterial];

	for (int i = 0; i < m_dwNumOfMaterial; i++)
	{
		m_pMeshMaterial[i] = d3dxMaterial[i].MatD3D;
		m_pMeshMaterial[i].Ambient = m_pMeshMaterial[i].Diffuse;

		m_pMeshTexture[i] = NULL;
		if (d3dxMaterial[i].pTextureFilename != NULL && strlen(d3dxMaterial[i].pTextureFilename) > 0)
			D3DXCreateTextureFromFile(m_pd3ddevice, (LPCWSTR)d3dxMaterial[i].pTextureFilename, &m_pMeshTexture[i]);
	}
}
void ModelLoader::OnRender()
{
	m_pd3ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pd3ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);
	for (int i = 0; i < m_dwNumOfMaterial; i++)
	{
		m_pd3ddevice->SetMaterial(&m_pMeshMaterial[i]);
		m_pd3ddevice->SetTexture(0, m_pMeshTexture[i]);
		m_pMesh->DrawSubset(i);
	}	
}

void ModelLoader::OnRelease()
{
	if (m_pMeshMaterial != NULL) delete[] m_pMeshMaterial;
	if (m_pMeshTexture != NULL) {
		for(int i=0; i < m_dwNumOfMaterial;i++) m_pMeshTexture[i]->Release();
		delete[] m_pMeshTexture;
	}
	if (m_pMesh != NULL) {
		m_pMeshMaterialBuff->Release();
		delete[] m_pMeshMaterialBuff;
	}
	if (m_pMesh != NULL) {
		m_pMesh->Release();
		delete m_pMesh;
	};
	if (m_pVb != NULL) {
		m_pVb->Release();
		delete m_pVb;
	}
}