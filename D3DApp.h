#pragma once
#include <d3d9.h>

enum GAME_SCENE
{
	INIT_START,
	LOADING_LOBBY,//
	LOBBY,
	LOADING_SELECT_CUSTOM,//
	SELECT_CUSTOM,
	LOADING_SELECT_SONG,//
	SELECT_SONG,
	LOADING_GAME_SONG1,//
	GAME_SONG1,
	GAMEOVER_CLEAR,
	GAMEOVER_FAIL,
	GAMEPAUSE
};

class D3DApp
{
protected:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3Ddevice;
	HWND m_hwnd;
	HWND m_hMenuwnd;

	

	virtual void OnInit() = 0;
	virtual void OnRender() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRelease() = 0;

public:
	HRESULT InitD3D(HWND hwnd, HWND hmenuwnd);
	void Render();
	void Update();
	void Cleanup();

	GAME_SCENE m_gameSceneState = INIT_START;
};

