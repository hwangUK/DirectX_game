#include "stdafx.h"
#include "D3DApp.h"
#include "resource.h"


HRESULT D3DApp::InitD3D(HWND hwnd, HWND hmenuwnd) {

	m_hwnd = hwnd;
	m_hMenuwnd = hmenuwnd;
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) ) return E_FAIL;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//------Z buffer------------
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3Ddevice))) return E_FAIL;
	
	m_pD3Ddevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	//virtual method
	OnInit();

	return S_OK;
}


void D3DApp::Render() {

	if (NULL == m_pD3Ddevice) return;

	m_pD3Ddevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 50), 1.0f, 0);

	if (SUCCEEDED(m_pD3Ddevice->BeginScene())) {

		//virtual method
		OnRender();

		m_pD3Ddevice->EndScene();
	}
	m_pD3Ddevice->Present(NULL, NULL, NULL, NULL);
}


void D3DApp::Update() {
	//virtual method
	OnUpdate();
}

void D3DApp::Cleanup() {
	//virtual method
	OnRelease();

	if (m_pD3Ddevice != NULL) m_pD3Ddevice->Release();
	if (m_pD3Ddevice != NULL) m_pD3D->Release();

}

