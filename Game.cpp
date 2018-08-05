#include "stdafx.h"
#include "Game.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>

void Game::OnInit() {

///Game 클래스 내 전역 초기화
	m_rt = { 250, 250, 0, 0 };
	RECT rect;
	GetClientRect(m_hwnd, &rect);

	//Camera Set
	m_Camera.SetInit(m_pD3Ddevice);
	m_Camera.SetViewPort(0, 0, rect.right - rect.left, rect.bottom - rect.top, 0.0f, 1.0f);
	m_Camera.SetCameraPos(-10.f, 30.f, 0.f);
	m_Camera.SetTargetPos(0.f, 0.f, 0.f);
	m_Camera.SetViewUp(0.f, 1.f, 0.f);
	//카메라 줌 및 화면전환 효과 시간 간격값 설정
	m_m_CamZoomSectionCount = 13;
	m_CamZoomSection = new int[m_m_CamZoomSectionCount]{ 2000,8000,10000,29000,33000,50000,51000,53000,55000,70000,80000,110000,130000 };
	//Material SET
	SetMaterial(1.0f, 1.0f, 1.0f);

	//Light SET
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Diffuse.r = m_Light.Diffuse.g = m_Light.Diffuse.b = m_Light.Diffuse.a = 1.0f;
	m_Light.Specular = m_Light.Diffuse;
	m_Light.Ambient.a = m_Light.Ambient.r = m_Light.Ambient.g = m_Light.Ambient.b = 0.0f;
	m_Light.Direction.x = 55.4f;
	m_Light.Direction.y = -55.4f;
	m_Light.Direction.z = 55.5f;

	SetDirectionalLight();

	//메인 플레이어 초기화
	m_NumofPlayerBullet = 4;
	m_player.OnInit(m_pD3Ddevice, 10, 0.05f, m_pMesh,TRUE, m_NumofPlayerBullet);
	m_player.SetScale(1.0f);
	
	m_vStartPos = m_player.GetPos();	

	// 타겟 객체 초기화 및 위치 / 리스폰시간 간격 설정
		// 4방면에서 내려오는 타겟의 시간 지연을 위한 변수
	DWORD spawntimeL = 1500;
	DWORD spawntimeR = 3333;
	DWORD spawntimeU = 3333;
	DWORD spawntimeD = 1000;
	for (int i = 0; i < 1000; i++) {
		m_Target_VerticalLEFT[i].OnInit(m_pD3Ddevice, 0, 0.013f, m_pMesh, FALSE,0);
		m_Target_VerticalRIGHT[i].OnInit(m_pD3Ddevice, 0, 0.017f, m_pMesh, FALSE,0);
		m_Target_HorizontalUP[i].OnInit(m_pD3Ddevice, 0, 0.008f, m_pMesh, FALSE,0);
		m_Target_HorizontalDOWN[i].OnInit(m_pD3Ddevice, 0, 0.008f, m_pMesh, FALSE,0);
	}
	for (int i = 0; i < 1000; i++) {
		m_Target_VerticalLEFT[i].SetTransform(m_vStartPos.x - 2, 0.0f, 20.0f);
		m_Target_VerticalLEFT[i].SetScale(1.5f);
		if (i < 200)spawntimeL += 1000;
		else spawntimeL += 877;
		m_Target_VerticalLEFT[i].SetSpawnTime(spawntimeL);
	}
	for (int i = 0; i < 1000; i++) {
		m_Target_VerticalRIGHT[i].SetTransform(m_vStartPos.x + 2, 0.0f, 20.0f);
		m_Target_VerticalRIGHT[i].SetScale(1.5f);
		if (i < 5)spawntimeR += 5667;
		else if (i > 5 && i < 15)spawntimeR += 20;
		else spawntimeR += 1837;
		m_Target_VerticalRIGHT[i].SetSpawnTime(spawntimeR);
	}
	for (int i = 0; i < 1000; i++) {
		m_Target_HorizontalUP[i].SetTransform(-20.0f, 0.0f, m_vStartPos.z + 2);
		m_Target_HorizontalUP[i].SetScale(1.5f);
		if (i < 80)spawntimeU += 1132;
		else spawntimeU += 3333;
		m_Target_HorizontalUP[i].SetSpawnTime(spawntimeU);
	}
	for (int i = 0; i < 1000; i++) {
		m_Target_HorizontalDOWN[i].SetTransform(-20.0f, 0.0f, m_vStartPos.z - 2);
		m_Target_HorizontalDOWN[i].SetScale(1.5f);
		if (i < 42)spawntimeD += 2351;
		else spawntimeD += 1132;
		m_Target_HorizontalDOWN[i].SetSpawnTime(spawntimeD);
	}

	// 기타 객체 초기화
	m_Axis.OnInit(m_pD3Ddevice);
	m_ground.OnCreate(m_pD3Ddevice, 40, 40, 1.0f);
	m_CUBE.OnInit(m_pD3Ddevice);
	sound.OnInit(2, 1);
	sound.CreateBGsound();
	sound.CreateEffectSound();

	//텍스처 폰트 초기화
	m_sprite01.OnInit(m_pD3Ddevice);
	m_sprite01.CreateImage(TEXT("image\\Texture2.bmp"));
	D3DXCreateTextureFromFile(m_pD3Ddevice, TEXT("image\\banana.bmp"), &m_pTexture);
	for(int i=0; i<5;i++) D3DXCreateFont(m_pD3Ddevice, 15 + (i*4), 0, FW_NORMAL, 1, true, 1, 1, 1, 1, TEXT(" "), &m_pFont[i]);


///씬 별로 추가 지역 초기화 작업
	SceneSet();
}

void Game::SceneSet()
{
	switch (m_gameSceneState)
	{
	case INIT_START:
	{
		m_Timer.ReSetTimer();
		m_sprite01.SetScale(10.f, 10.f, 10.f);
	}
	break;
	case LOADING_LOBBY:
		ShowWindow(m_hMenuwnd, SW_HIDE);
		m_Timer.ReSetTimer();
		break;
	case LOBBY:
		m_Timer.ReSetTimer();
		break;
	case LOADING_SELECT_CUSTOM:
		m_Timer.ReSetTimer();
		break;
	case SELECT_CUSTOM: {

		ShowWindow(m_hMenuwnd, SW_SHOW);
		SetMaterial(1.0f, 1.0f, 1.0f);
		m_player.SetTransform(0.0f, 0.0f, 0.0f);
		m_player.InitModelLoad(m_player.CHECKMODEL);

		m_Camera.SetCameraPos(0.f, 30.f, -25.f);
		m_Camera.SetTargetPos(0.f, 0.f, 0.f);
		m_Camera.SetViewUp(0.f, 1.f, 0.f);
		
		m_CUBE.SetMatrixTranslate(0.0f, 0.0f, 0.0f);
		m_CUBE.SetMatrixScale(1.0f, 1.0f, 1.0f);

		m_Timer.ReSetTimer();
	}
	break;

	case LOADING_SELECT_SONG:
		m_Timer.ReSetTimer();
		break;
	case SELECT_SONG:
		m_Timer.ReSetTimer();
		break;

	case LOADING_GAME_SONG1:
		m_Timer.ReSetTimer();
		break;
	case GAME_SONG1: {

		m_Timer.ReSetTimer();
		m_player.SetLife(10);
		m_Camera.SetCameraPos(-13.f, 75.f, -15.f);
		m_Camera.SetTargetPos(8.f, 0.f, -10.f);
		m_Camera.SetViewUp(0.f, 1.f, 0.f);

		SetMaterial(1.0f, 1.0f, 1.0f);
		m_player.SetTransform(15.0f, 0.0f, -15.0f);
		m_player.InitModelLoad(m_player.CHECKMODEL);
		m_vStartPos = m_player.GetPos();

		ShowWindow(m_hMenuwnd, SW_HIDE);

		m_sprite01.SetScale(8.f, 8.f, 8.f);

		sound.PlaySoundBG(0);
		
		m_CUBE.SetMatrixTranslate(15.0f, 0.0f, -15.5f);
		m_CUBE.SetMatrixScale(1.0f, 1.0f, 1.0f);
		//타겟 구슬 객체 리스폰 인덱스 / 위치 세팅
		for (int i = 0; i < 4; i++) m_TargetIndex[i] = i;
		for (int i = 0; i < 1000; i++) {
			m_Target_VerticalLEFT[i].SetTransform(m_vStartPos.x - 2, 0.0f, 20.0f);
			m_Target_VerticalRIGHT[i].SetTransform(m_vStartPos.x + 2, 0.0f, 20.0f);
			m_Target_HorizontalUP[i].SetTransform(-20.0f, 0.0f, m_vStartPos.z + 2);
			m_Target_HorizontalDOWN[i].SetTransform(-20.0f, 0.0f, m_vStartPos.z - 2);
		}
		//재시작시 다시 0으로 만들어야함  [시간순서대로 살리기 위해]
		for (int i = 0; i < 1000; i++) {
			m_Target_VerticalLEFT[i].SetLife(0);
			m_Target_VerticalRIGHT[i].SetLife(0);
			m_Target_HorizontalUP[i].SetLife(0);
			m_Target_HorizontalDOWN[i].SetLife(0);
		}
		//--------------------		
		m_Timer.ReSetTimer();
	}
		break;
	case GAMEOVER_CLEAR:
		m_Timer.ReSetTimer();
		break;
	case GAMEOVER_FAIL:
		m_Timer.ReSetTimer();
		break;
	case GAMEPAUSE:
		m_Timer.ReSetTimer();
		break;
	}
}

void Game::OnRender() {

	switch (m_gameSceneState) {
	case INIT_START: {
		m_sprite01.OnRender();
		SetDrawingText(4, TEXT("MAIN SCENE \n\n Press SpaceBar"), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 0, 0);
		break;
	}		
	case LOADING_LOBBY:
		SetDrawingText(3, TEXT("LOADING...."), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case LOBBY:
		SetDrawingText(3, TEXT("LOBBY SCENE \n\n[ 1.CUSTOMIZE ] \n\n[ 2.PLAYGAME ]"), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case LOADING_SELECT_CUSTOM:
		SetDrawingText(3, TEXT("LOADING...."), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case SELECT_CUSTOM: 
	{
		m_sprite01.OnRender();
		m_Axis.OnRender();
		m_ground.OnRender();
		m_player.OnRender();
		m_CUBE.OnRender();

		SetDrawingText(3, TEXT("THIS IS CUSTOMIZE SCENE"), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	}		
	case LOADING_SELECT_SONG:
		SetDrawingText(3, TEXT("LOADING...."), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case SELECT_SONG: // 곡선택화면
		SetDrawingText(3, TEXT("select SONG at List  Press Song Number \n\n[ 1 .DarfPunk  ]\n\n[ 2. Twise - What is Love ]\n\n[ 3. Coming Soon ]\n\n[ 4. Coming Soon ]"), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case LOADING_GAME_SONG1:
		SetDrawingText(3, TEXT("LOADING...."), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case GAME_SONG1: {
		 m_CUBE.OnRender();
	     m_sprite01.OnRender(); 
		 m_nFPSCount++;	
		 if (m_player.GetLife() > 0)  m_player.OnRender();
		 else {
			 m_gameSceneState = GAMEOVER_FAIL;
			 SceneSet();
		 }
		for(int i = 0; i < 1000; i++) {
			if (m_Target_VerticalLEFT[i].GetLife() > 0) {
				SetMaterial(1.0f, 0.0f, 0.0f);
				m_Target_VerticalLEFT[i].OnRender();
			}				
			if (m_Target_VerticalRIGHT[i].GetLife() > 0) {
				SetMaterial(1.0f, 1.0f, 0.0f);
				m_Target_VerticalRIGHT[i].OnRender();
			} 
			if (m_Target_HorizontalUP[i].GetLife() > 0) {
				SetMaterial(0.8f, 0.3f, 0.1f);
				m_Target_HorizontalUP[i].OnRender();
			} 
			if (m_Target_HorizontalDOWN[i].GetLife() > 0) {
				SetMaterial(0.0f, 0.8f, 0.4f);
				m_Target_HorizontalDOWN[i].OnRender();
			} 
		}
		wchar_t str_FPS[100];
		wchar_t str_Timer[100];
		wchar_t str_Life[100];
		wchar_t wchar_fpos[100];
		char char_fpos[100];		
		size_t size;

		wsprintfW(str_FPS, TEXT("FPS : %d"), m_nFPS);
		SetDrawingText(2, str_FPS, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 10, 10, 0, 0);
		wsprintfW(str_Timer, TEXT("Time : %d"), m_Timer.GetTimer());
		SetDrawingText(2, str_Timer, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 10, 0, 0);
		wsprintfW(str_Life, TEXT("LIFE : %d"), m_player.GetLife());
		SetDrawingText(3, str_Life, D3DXCOLOR(0.5f, 1.0f, 0.0f, 0.8f), 350, 10, 0, 0);
		//float값을 받아오기위해 LPWSTR을 변환
		sprintf_s(char_fpos, "%f %f.%f", m_player.GetPos().x, m_player.GetPos().y, m_player.GetPos().z);
		mbstowcs_s(&size, wchar_fpos, char_fpos, strlen(char_fpos)+1);
		SetDrawingText(1, wchar_fpos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), 10, 40, 0, 0);		
	}		
		break;
	case GAMEOVER_CLEAR:
		SetDrawingText(3, TEXT("STAGE CLEAR"), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case GAMEOVER_FAIL:
		SetDrawingText(3, TEXT("MISSION FAIL"), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), 50, 50, 0, 0);
		break;
	case GAMEPAUSE:
		break;
	}
}

void Game::OnUpdate() {
	
	switch (m_gameSceneState)
	{
	case INIT_START:
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			m_gameSceneState = LOADING_LOBBY;
			SceneSet();
		}
		break;
	case LOADING_LOBBY:
			m_gameSceneState = LOBBY;
			SceneSet();
		break;
	case LOBBY:
		if (GetAsyncKeyState('1') < 0) {
			m_gameSceneState = LOADING_SELECT_CUSTOM;
			SceneSet();
		}
		if (GetAsyncKeyState('2') < 0) {
			m_gameSceneState = LOADING_SELECT_SONG;
			SceneSet();
		}
		break;

	case LOADING_SELECT_CUSTOM:
		m_gameSceneState = SELECT_CUSTOM;
		SceneSet();
		break;

	case SELECT_CUSTOM:	{
		m_Timer.StartTimer();
		m_player.OnUpdate();		
		m_CUBE.SetMatrixRotate(0.0f, 0.0f, 0.0f);
		if (GetAsyncKeyState('D') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x + 0.2f, m_Camera.GetCameraPos().y, m_Camera.GetCameraPos().z);
			m_Camera.SetTargetPos(m_Camera.GetTargetPos().x + 0.2f, m_Camera.GetTargetPos().y, m_Camera.GetTargetPos().z);
		}
		if (GetAsyncKeyState('A') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x - 0.2f, m_Camera.GetCameraPos().y, m_Camera.GetCameraPos().z);
			m_Camera.SetTargetPos(m_Camera.GetTargetPos().x - 0.2f, m_Camera.GetTargetPos().y, m_Camera.GetTargetPos().z);
		}
		if (GetAsyncKeyState('W') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x, m_Camera.GetCameraPos().y + 0.2f, m_Camera.GetCameraPos().z);
		}
		if (GetAsyncKeyState('S') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x, m_Camera.GetCameraPos().y - 0.2f, m_Camera.GetCameraPos().z);
		}
	}
		break;

	case LOADING_SELECT_SONG:
		m_gameSceneState = SELECT_SONG; 
		SceneSet();
		break;	
	case SELECT_SONG: // 곡선택화면
		if (GetAsyncKeyState('1') < 0) m_gameSceneState = LOADING_GAME_SONG1; //1번곡을 선택하셨습니다.		
		SceneSet();
		break;

	case LOADING_GAME_SONG1: 
		m_gameSceneState = GAME_SONG1; 	
		SceneSet();
		break;
	case GAME_SONG1:
	 {
		m_Timer.StartTimer();
		static DWORD dwAccumulateTime = 0;		
		dwAccumulateTime += m_Timer.GetElapsedTimer();		
		if (dwAccumulateTime >= 1000) {
			dwAccumulateTime = 0;
			m_nFPS = m_nFPSCount;
			m_nFPSCount = 0;
		}
		//CUSTOM------------------------------------
		sound.Update();
		m_player.OnUpdate();
		m_CUBE.SetMatrixRotate(m_player.GetPos().x, m_player.GetPos().x, m_player.GetPos().z);

		if (m_Timer.GetTimer() > 180000) {
			m_gameSceneState = GAMEOVER_CLEAR;
			SceneSet();
		}
		// CAMERA ZOOM IN		
		m_Camera.ZoomFunc(m_Timer.GetTimer(), m_m_CamZoomSectionCount, m_CamZoomSection);
	
		for (int i = 0; i < 1000; i++) {
			m_Target_VerticalLEFT[i].OnUpdate();
			m_Target_VerticalRIGHT[i].OnUpdate();
			m_Target_HorizontalUP[i].OnUpdate();
			m_Target_HorizontalDOWN[i].OnUpdate();
		}

		//살면 움직여라 moving when live
		for (int k = 0; k < 1000; k++) {
			if (m_Target_VerticalLEFT[k].GetLife() > 0) m_Target_VerticalLEFT[k].SetTransform(m_Target_VerticalLEFT[k].GetPos().x, m_Target_VerticalLEFT[k].GetPos().y, m_Target_VerticalLEFT[k].GetPos().z - m_Timer.GetElapsedTimer() * m_Target_VerticalLEFT[k].GetSpeed());
			if (m_Target_VerticalRIGHT[k].GetLife() > 0) m_Target_VerticalRIGHT[k].SetTransform(m_Target_VerticalRIGHT[k].GetPos().x, m_Target_VerticalRIGHT[k].GetPos().y, m_Target_VerticalRIGHT[k].GetPos().z - m_Timer.GetElapsedTimer() * m_Target_VerticalRIGHT[k].GetSpeed());
			if (m_Target_HorizontalUP[k].GetLife() > 0) m_Target_HorizontalUP[k].SetTransform(m_Target_HorizontalUP[k].GetPos().x + m_Timer.GetElapsedTimer() * m_Target_HorizontalUP[k].GetSpeed() * 0.5f, m_Target_HorizontalUP[k].GetPos().y, m_Target_HorizontalUP[k].GetPos().z);
			if (m_Target_HorizontalDOWN[k].GetLife() > 0) m_Target_HorizontalDOWN[k].SetTransform(m_Target_HorizontalDOWN[k].GetPos().x + m_Timer.GetElapsedTimer() * m_Target_HorizontalDOWN[k].GetSpeed() * 0.5f, m_Target_HorizontalDOWN[k].GetPos().y, m_Target_HorizontalDOWN[k].GetPos().z);
		}

		//사는 경우 Case of live = respawn time is done
		for (int j = m_TargetIndex[0]; j < 1000; j++) {
			if (m_Timer.GetTimer() > m_Target_VerticalLEFT[j].GetSpawnTime()) {
				m_Target_VerticalLEFT[j].SetLife(1);
				m_TargetIndex[0]++;
				break;
			}
		}
		for (int i = m_TargetIndex[1]; i < 1000; i++) {
			if (m_Timer.GetTimer() > m_Target_VerticalRIGHT[i].GetSpawnTime()) {
				m_Target_VerticalRIGHT[i].SetLife(1);
				m_TargetIndex[1]++;
				break;
			}
		}
		for (int j = m_TargetIndex[2]; j < 1000; j++) {
			if (m_Timer.GetTimer() > m_Target_HorizontalUP[j].GetSpawnTime()) {
				m_Target_HorizontalUP[j].SetLife(1);
				m_TargetIndex[2]++;
				break;
			}
		}
		for (int j = m_TargetIndex[3]; j < 1000; j++) {
			if (m_Timer.GetTimer() > m_Target_HorizontalDOWN[j].GetSpawnTime()) {
				m_Target_HorizontalDOWN[j].SetLife(1);
				m_TargetIndex[3]++;
				break;
			}
		}
		//죽는경우	Case of die
		for (int j = 0; j < 1000; j++)	{
			if (CheckTrigger(m_player, m_Target_VerticalLEFT[j])) {
				SetMaterial(1.0f, 0.0f, 0.0f);
				m_Target_VerticalLEFT[j].SetLife(0);
				//sound.PlaySoundEF(0);
			}
			if (CheckTrigger(m_player, m_Target_VerticalRIGHT[j])) {
				SetMaterial(1.0f, 1.0f, 0.0f);
				m_Target_VerticalRIGHT[j].SetLife(0);
				//sound.PlaySoundEF(0);
			}
			if (CheckTrigger(m_player, m_Target_HorizontalUP[j])) {
				SetMaterial(0.8f, 0.3f, 0.1f);
				m_Target_HorizontalUP[j].SetLife(0);
				//sound.PlaySoundEF(0);
			}
			if (CheckTrigger(m_player, m_Target_HorizontalDOWN[j])) {
				SetMaterial(0.0f, 0.8f, 0.4f);
				m_Target_HorizontalDOWN[j].SetLife(0);
				//sound.PlaySoundEF(0);				
			}

			if (m_player.FireOn) {
				for (int i = 0; i < m_NumofPlayerBullet; i++)
				{
					if (CheckTrigger(m_player.GetBulletFigure(i), m_Target_VerticalLEFT[j])) {
						m_Target_VerticalLEFT[j].SetLife(0);
						m_player.SetBulletLife(0, i);
						m_player.FireOn[i] = FALSE;
					}
					if (CheckTrigger(m_player.GetBulletFigure(i), m_Target_VerticalRIGHT[j])) {
						m_Target_VerticalRIGHT[j].SetLife(0);
						m_player.SetBulletLife(0, 0);
						m_player.FireOn[i] = FALSE;
					}
					if (CheckTrigger(m_player.GetBulletFigure(i), m_Target_HorizontalUP[j])) {
						m_Target_HorizontalUP[j].SetLife(0);
						m_player.SetBulletLife(0, i);
						m_player.FireOn[i] = FALSE;
					}
					if (CheckTrigger(m_player.GetBulletFigure(i), m_Target_HorizontalDOWN[j])) {
						m_Target_HorizontalDOWN[j].SetLife(0);
						m_player.SetBulletLife(0, i);
						m_player.FireOn[i] = FALSE;
					}
				}			
			}
	
			//밖으로 벗어나는경우			
			if (m_Target_VerticalLEFT[j].GetPos().z < -20.0f && m_Target_VerticalLEFT[j].GetLife() > 0) {
				m_Target_VerticalLEFT[j].SetLife(0);
				m_player.SetLife(m_player.GetLife() - 1);
			} 
			if (m_Target_VerticalRIGHT[j].GetPos().z < -20.0f && m_Target_VerticalRIGHT[j].GetLife() > 0) {
				m_Target_VerticalRIGHT[j].SetLife(0);
				m_player.SetLife(m_player.GetLife() - 1);
			}
			if (m_Target_HorizontalUP[j].GetPos().x > 20.0f && m_Target_HorizontalUP[j].GetLife() > 0) {
				m_Target_HorizontalUP[j].SetLife(0);
				m_player.SetLife(m_player.GetLife() - 1);
			}
			if (m_Target_HorizontalDOWN[j].GetPos().x > 20.0f && m_Target_HorizontalDOWN[j].GetLife() > 0) {
				m_Target_HorizontalDOWN[j].SetLife(0);
				m_player.SetLife(m_player.GetLife() - 1);
			}
		}

		//Key_____________________________________________________________
	

		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			if (m_player.GetPos().x > m_vStartPos.x -1.5f) 
				m_player.SetTransform(m_player.GetPos().x - m_Timer.GetElapsedTimer()* m_player.GetSpeed(), m_player.GetPos().y, m_player.GetPos().z);							
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			if (m_player.GetPos().x <= m_vStartPos.x + 1.5f)
				m_player.SetTransform(m_player.GetPos().x + m_Timer.GetElapsedTimer()* m_player.GetSpeed(), m_player.GetPos().y, m_player.GetPos().z);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			if (m_player.GetPos().z < m_vStartPos.z + 1.5f)
				m_player.SetTransform(m_player.GetPos().x, m_player.GetPos().y, m_player.GetPos().z + m_Timer.GetElapsedTimer() * m_player.GetSpeed());
		}

		if (GetAsyncKeyState(VK_DOWN)) {
			if (m_player.GetPos().z >=  m_vStartPos.z - 1.5f)
				m_player.SetTransform(m_player.GetPos().x, m_player.GetPos().y, m_player.GetPos().z - m_Timer.GetElapsedTimer() * m_player.GetSpeed());
		}	

		if (GetAsyncKeyState(VK_SPACE)) {	
			for (int i = 0; i < m_NumofPlayerBullet; i++) {
				m_player.FireOn[i] = TRUE;
				m_player.SetBulletLife(1, i);
			}
		}

		if (GetAsyncKeyState('D') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x + 0.2f, m_Camera.GetCameraPos().y, m_Camera.GetCameraPos().z);
			m_Camera.SetTargetPos(m_Camera.GetTargetPos().x + 0.2f, m_Camera.GetTargetPos().y, m_Camera.GetTargetPos().z);
		}

		if (GetAsyncKeyState('A') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x - 0.2f, m_Camera.GetCameraPos().y, m_Camera.GetCameraPos().z);
			m_Camera.SetTargetPos(m_Camera.GetTargetPos().x - 0.2f, m_Camera.GetTargetPos().y, m_Camera.GetTargetPos().z);
		}
		if (GetAsyncKeyState('W') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x , m_Camera.GetCameraPos().y + 0.2f, m_Camera.GetCameraPos().z);
		}
		if (GetAsyncKeyState('S') < 0) {
			m_Camera.SetCameraPos(m_Camera.GetCameraPos().x, m_Camera.GetCameraPos().y - 0.2f, m_Camera.GetCameraPos().z);
		}	
	}
		break;

	case GAMEOVER_CLEAR: {		
		sound.StopSoundBG(0);
		m_Timer.StartTimer();
		if (m_Timer.GetTimer() > 2500) {
			m_gameSceneState = LOBBY;
			SceneSet();
			//다시 모두 해제
		}
	}
		break;
	case GAMEOVER_FAIL: {
		sound.StopSoundBG(0);
		m_Timer.StartTimer();
		if (m_Timer.GetTimer() > 2500) {
			m_gameSceneState = LOBBY;
			SceneSet();
		}
	}
		break;
	case GAMEPAUSE:
		break;
	}	
}

void Game:: OnRelease() {

	switch (m_gameSceneState) {
	case INIT_START:
		break;
	case LOADING_LOBBY:
		break;
	case LOBBY:
		break;
	case LOADING_SELECT_CUSTOM:
		break;
	case SELECT_CUSTOM:	{
		m_player.OnRelease();
		m_Camera.OnRelease();
		m_CUBE.OnRelease();
	}
		break;
	case LOADING_SELECT_SONG:
		break;
	case SELECT_SONG: // 곡선택화면
		break;
	case GAME_SONG1: {
		sound.ReleaseSound();
		m_Axis.OnRelease();
		m_CUBE.OnRelease();
		m_Camera.OnRelease();
		m_sprite01.OnRelease();
		m_player.OnRelease();
		for (int i = 0; i < 1000; i++) {
			m_Target_VerticalLEFT[i].OnRelease();
			m_Target_VerticalRIGHT[i].OnRelease();
			m_Target_HorizontalUP[i].OnRelease();
			m_Target_HorizontalDOWN[i].OnRelease();
		}			
		for (int i = 0; i < 5; i++)	m_pFont[i]->Release();		
		if (m_pTexture != NULL) m_pTexture->Release();
		if (m_pMesh != NULL) m_pMesh->Release();
	}		
		break;
	case GAMEOVER_CLEAR:
		break;
	case GAMEOVER_FAIL:
		break;
	case GAMEPAUSE:
		break;
	}
}
//트리거 메서드 오버로딩
bool Game::CheckTrigger(OBJ_ACTOR col1, OBJ_ACTOR col2){

	float fDistance = 0.0f;
	D3DXVECTOR3 vc;

	vc = col1.GetPos() - col2.GetPos();
	fDistance = D3DXVec3Length(&vc);

	if (fDistance <= col1.GetRadius() * col1.GetScale() + col2.GetRadius() * col2.GetScale()) return TRUE;
	return FALSE;
}
bool Game::CheckTrigger(Figure col1, OBJ_ACTOR col2) {

	float fDistance = 0.0f;
	D3DXVECTOR3 vc;

	vc = col1.GetBulletPos() - col2.GetPos();
	fDistance = D3DXVec3Length(&vc);

	if (fDistance <= col1.m_BulletRadius * col1.m_BulletScale + col2.GetRadius() * col2.GetScale()) return TRUE;
	return FALSE;
}

void Game::SetMaterial(float r, float g, float b)
{
	D3DCOLORVALUE Diffuse;
	Diffuse.r = r;
	Diffuse.g = g;
	Diffuse.b = b;
	ZeroMemory(&m_Material, sizeof(D3DCOLORVALUE));
	m_Material.Ambient = Diffuse;
	m_Material.Diffuse = Diffuse;
	m_pD3Ddevice->SetMaterial(&m_Material);
}

D3DCOLORVALUE Game::GetMaterial()
{
	return m_Material.Diffuse;
}

void Game::SetDirectionalLight()
{
	m_pD3Ddevice->SetLight(0, &m_Light);
	m_pD3Ddevice->LightEnable(0, TRUE);
}

void Game::SetModel(CHK_MODEL cm)
{
	m_player.CHECKMODEL = cm;
	m_player.InitModelLoad(cm);
}

float Game::GetModelSize()
{
	return m_player.GetScale();
}
void Game::SetModelSize(float input)
{	
	m_player.SetScale(input);
}

void Game::SetDrawingText(int fontSizeIndex, LPWSTR str, D3DXCOLOR color, int leftRect,int uprect, int rightRect,int downRect)
{
	SetRect(&m_rt, leftRect, uprect, rightRect, downRect);
	m_pFont[fontSizeIndex]->DrawTextW(NULL, str, -1, &m_rt, DT_NOCLIP, color);
}