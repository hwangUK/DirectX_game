#pragma once
#include <d3d9.h>
class Axis
{
private:
	LPDIRECT3DDEVICE9 m_pD3Ddevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;

public:
	void OnInit(LPDIRECT3DDEVICE9 pd3dDevice);
	void OnRender();
	void OnRelease();

};

