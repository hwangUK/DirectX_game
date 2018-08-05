// D3DUKH9.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "resource.h"
#include "D3DUKH9.h"
#include "D3DApp.h"
#include "Game.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;   // 현재 인스턴스입니다.


WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;

HWND g_hMenuWnd;
HWND g_hComboBox;
HWND g_hCheckBox;
Game myApp;

int g_nMenuWidth, g_nMenuHeight;
TCHAR *items[4] = { TEXT("DEFAULT"),TEXT("AIR"),TEXT("TIGER"),TEXT("FLY") };

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
int CALLBACK MenuDlgProc(HWND hwnd, UINT nMsg, WPARAM wparam, LPARAM lparam);
//winmain

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_D3DUKH9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	
	// 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	MSG msg;
    
	myApp.InitD3D(g_hWnd,g_hMenuWnd);

	//컨트롤값
	char string[10];
	//string st = "IDC_EDIT2";
	sprintf_s(string, "%.1f", myApp.m_Material.Diffuse.r);
	SetDlgItemTextA(g_hMenuWnd, 1004, string);

	sprintf_s(string, "%.1f", myApp.m_Material.Diffuse.r);
	SetDlgItemTextA(g_hMenuWnd, 1005, string);
	sprintf_s(string, "%.1f", myApp.m_Material.Diffuse.g);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT3, string);
	sprintf_s(string, "%.1f", myApp.m_Material.Diffuse.b);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT4, string);

	sprintf_s(string, "%.1f", myApp.m_Light.Diffuse.r);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT5, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Diffuse.g);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT6, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Diffuse.b);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT7, string);

	sprintf_s(string, "%.1f", myApp.m_Light.Ambient.r);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT8, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Ambient.g);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT9, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Ambient.b);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT10, string);

	sprintf_s(string, "%.1f", myApp.m_Light.Specular.r);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT11, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Specular.g);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT12, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Specular.b);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT13, string);

	sprintf_s(string, "%.1f", myApp.m_Light.Direction.x);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT14, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Direction.y);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT15, string);
	sprintf_s(string, "%.1f", myApp.m_Light.Direction.z);
	SetDlgItemTextA(g_hMenuWnd, IDC_EDIT16, string);	
	
    // 기본 메시지 루프입니다.
    while (true)
    { 
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} 
		else {			
			myApp.Update();
			myApp.Render();			
			//render 게임은 계속되어야한다 [윈도우 메세지와별개]
		}
    }
    return (int) msg.wParam;
}


//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DUKH9));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_D3DUKH9);
    wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hwnd;
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT rt = { 0, 0, 780, 780 };
   AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

   g_hWnd = hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      200, 0, rt.right - rt.left, rt.bottom - rt.top, NULL, NULL, hInstance, NULL);

   if (!hwnd)
   {
      return FALSE;
   }

   ShowWindow(hwnd, nCmdShow);
   UpdateWindow(hwnd);

   RECT rtWin, rtDlg;
   GetWindowRect(g_hWnd, &rtWin);
   
   g_hMenuWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, MenuDlgProc);
   //ShowWindow(g_hMenuWnd, SW_SHOW);
   

   GetWindowRect(g_hMenuWnd, &rtDlg);
   g_nMenuWidth = rtDlg.right - rtDlg.left;
   g_nMenuHeight = rtDlg.bottom - rtDlg.top;

   MoveWindow(g_hMenuWnd, rtWin.right, rtWin.top, g_nMenuWidth, g_nMenuHeight, TRUE);

   return TRUE;
}  

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rectWINDOW;

    switch (message)
    {
	case WM_MOVE:
		{
		GetWindowRect(hWnd, &rectWINDOW);
		MoveWindow(g_hMenuWnd, rectWINDOW.right, rectWINDOW.top, g_nMenuWidth, g_nMenuHeight, TRUE);
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_EXIT:				
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }			
        }
        break;
    case WM_PAINT:
		myApp.Update();
		myApp.Render();
        break;
    case WM_DESTROY:
		myApp.Cleanup();
        PostQuitMessage(0); // WM_QUIT
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK MenuDlgProc(HWND hDlg, UINT nMsg, WPARAM wparam, LPARAM lparam) {

	char ch[10];
	float fRed, fGreen, fBlue;
	switch (nMsg)
	{
	case WM_INITDIALOG: 	
	{
		g_hComboBox = GetDlgItem(hDlg, IDC_COMBO1);
		SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)items[0]);		
		SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)items[1]);
		SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)items[2]);
		SendMessage(g_hComboBox, CB_ADDSTRING, 0, (LPARAM)items[3]);
		SetWindowText(GetDlgItem(hDlg, IDC_EDIT17), TEXT("1.0"));
	}
	break;
	case WM_COMMAND:
		if (wparam == IDC_BUTTON1) 
		{
			
			GetDlgItemTextA(hDlg,IDC_EDIT2,ch,9);
			fRed = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT3, ch, 9);
			fGreen = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT4, ch, 9);
			fBlue = atof(ch);

			myApp.SetMaterial(fRed, fGreen, fBlue);
		}
		if (wparam == IDC_BUTTON2)
		{
			GetDlgItemTextA(hDlg, IDC_EDIT5, ch, 9);
			myApp.m_Light.Diffuse.r = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT6, ch, 9);
			myApp.m_Light.Diffuse.g = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT7, ch, 9);
			myApp.m_Light.Diffuse.b = atof(ch);

			GetDlgItemTextA(hDlg, IDC_EDIT8, ch, 9);
			myApp.m_Light.Ambient.r = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT9, ch, 9);
			myApp.m_Light.Ambient.g = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT10, ch, 9);
			myApp.m_Light.Ambient.b = atof(ch);

			GetDlgItemTextA(hDlg, IDC_EDIT11, ch, 9);
			myApp.m_Light.Specular.r = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT12, ch, 9);
			myApp.m_Light.Specular.g = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT13, ch, 9);
			myApp.m_Light.Specular.b = atof(ch);

			GetDlgItemTextA(hDlg, IDC_EDIT14, ch, 9);
			myApp.m_Light.Direction.x = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT15, ch, 9);
			myApp.m_Light.Direction.y = atof(ch);
			GetDlgItemTextA(hDlg, IDC_EDIT16, ch, 9);
			myApp.m_Light.Direction.z = atof(ch);			

			myApp.SetDirectionalLight();
		}
		if (wparam == IDC_BUTTON3)
		{			
			GetDlgItemTextA(hDlg, IDC_EDIT17, ch, 9);
			myApp.SetModelSize(atof(ch));
		}
		if (LOWORD(wparam) == IDC_COMBO1)
		{

			switch (HIWORD(wparam)) 
			{
			case CBN_SELCHANGE:	{
				CHAR str[255];
				int i = SendMessage(g_hComboBox, CB_GETCURSEL, 0, 0);
				SendMessage(g_hComboBox, CB_GETLBTEXT, i, (LPARAM)str);	
				if (str[0] == 'A') 	myApp.SetModel(AIR);
				else if (str[0] == 'T') myApp.SetModel(TIGER);
				else if (str[0] == 'F') myApp.SetModel(FLY);
				else if (str[0] == 'D') myApp.SetModel(DEFAULT);
				break;
				}								
			case CBN_EDITCHANGE:			
				//GetWindowText(g_hComboBox, (LPWSTR)str, 128);
				//SetWindowText(g_hMenuWnd,(LPCWSTR) str);
				break;
			}
		}

		if (wparam == IDCANCEL)
		{
			myApp.m_gameSceneState = LOBBY;
			ShowWindow(g_hMenuWnd,SW_HIDE);
		}

		if (wparam == IDC_SPIN1)
		{
			GetDlgItemTextA(hDlg, IDC_EDIT2, ch, 9);
			fRed = atof(ch) + 0.2f;
			sprintf_s(ch, ("%.1f"), fRed);
			SetDlgItemTextA(hDlg, IDC_EDIT2, ch);

			myApp.SetMaterial(fRed, fGreen, fBlue);
		}
		break;
	}
	return FALSE;
}