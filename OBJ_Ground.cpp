#include "stdafx.h"
#include "OBJ_Ground.h"


void OBJ_Ground::OnCreate(LPDIRECT3DDEVICE9 pd3ddevice, int nRow, int nCol, float fsize) {

	m_pD3Ddevice = pd3ddevice;
	m_Row = nRow;
	m_Col = nCol;
	m_totalSize = m_Row * m_Col -1;

	m_dwNumVertices = (m_Row+1) * (m_Col+1);
	m_dwNumIndices = m_Row * m_Col * 6; //vertex count is 6 on one Rectangle

	//VERTEX SET
	GROUNDVERTEX *gVertexbuffer = new GROUNDVERTEX[m_dwNumVertices];

	//strat_vertex setting
	int nVertexIndex = 0;
	D3DXVECTOR3 startPos (-1.0f * m_Col * fsize * 0.5f,0.0f,m_Row * fsize * 0.5f);
	//
	for (int z = 0; z <= m_Row; z++) {
		for (int x = 0; x <= m_Col; x++)
		{
			gVertexbuffer[nVertexIndex].vPos.x = startPos.x + (fsize * x);
			gVertexbuffer[nVertexIndex].vPos.y = 0.0f;
			gVertexbuffer[nVertexIndex].vPos.z = startPos.z + -1.0f * (fsize * z);
			gVertexbuffer[nVertexIndex].dwColor = D3DCOLOR_RGBA(0, 0, 0, 255);
			nVertexIndex++;
		}
	}
	m_pD3Ddevice->CreateVertexBuffer(m_dwNumVertices * sizeof(GROUNDVERTEX), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL);
	
	void *pVertices;
	m_pVB->Lock(0, 0, &pVertices, 0);
	memcpy(pVertices, gVertexbuffer, m_dwNumVertices * sizeof(GROUNDVERTEX));
	m_pVB->Unlock();

	//INDEX SET
	WORD *pIndex = new WORD[m_dwNumIndices];
	int nIndexOfIndex = 0;
	for (int z = 0; z < m_Row; z++)
	{
		for (int x = 0; x < m_Col; x++)
		{
			pIndex[nIndexOfIndex++] = z * (m_Col + 1) + x;
			pIndex[nIndexOfIndex++] = (z + 1) * (m_Col + 1)+ x + 1;
			pIndex[nIndexOfIndex++] = (z + 1) * (m_Col + 1)+ x;

			pIndex[nIndexOfIndex++] = z * (m_Col + 1) + x;
			pIndex[nIndexOfIndex++] = z * (m_Col + 1) + x + 1;
			pIndex[nIndexOfIndex++] = (z + 1) * (m_Col + 1) + x + 1;
		}
	}
		
	m_pD3Ddevice->CreateIndexBuffer(sizeof(WORD) * m_dwNumIndices, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
	void *pIndexBuffer;
	m_pIB->Lock(0, sizeof(WORD) * m_dwNumIndices, &pIndexBuffer, NULL);
	memcpy(pIndexBuffer, pIndex, sizeof(WORD) * m_dwNumIndices);
	m_pIB->Unlock();

	delete[] pIndex;
	delete[] gVertexbuffer;

}

void OBJ_Ground::OnRender()
{
	D3DXMATRIX matrixWORLD;
	D3DXMatrixIdentity(&matrixWORLD);

	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3Ddevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pD3Ddevice->SetTransform(D3DTS_WORLD, &matrixWORLD);
	m_pD3Ddevice->SetStreamSource(0, m_pVB, 0, sizeof(GROUNDVERTEX));	
	m_pD3Ddevice->SetIndices(m_pIB);
	m_pD3Ddevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	m_pD3Ddevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwNumVertices, 0,( m_Col * m_Row) * 2);	

	m_pD3Ddevice->SetRenderState(D3DRS_LIGHTING, TRUE);


}
void OBJ_Ground::OnRelease()
{
	if (m_pIB != NULL) delete[] m_pIB;
	if (m_pVB != NULL) delete[] m_pVB;
}
