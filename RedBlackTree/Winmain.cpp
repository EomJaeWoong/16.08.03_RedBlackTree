// RedBlackTree.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Winmain.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
HWND g_hWnd;
HDC g_hMemDC;
HBITMAP g_hMemBitmap;
HBITMAP g_hMemBitmapold;
RECT rWinSize;
CRedBlackTree g_Tree;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_REDBLACKTREE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_REDBLACKTREE);
	wcex.lpszClassName = L"RedBlackTree";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	g_hWnd = CreateWindow(L"RedBlackTree", L"RedBlackTree", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	GetClientRect(g_hWnd, &rWinSize);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_LBUTTONDOWN :
		g_Tree.InsertNode(rand() % 5000);
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
		GetClientRect(g_hWnd, &rWinSize);
		//-------------------------------------------------------------------------------------------------------
		// MemDC 만들기
		//-------------------------------------------------------------------------------------------------------
		hdc = GetDC(hWnd);
		g_hMemDC = CreateCompatibleDC(hdc);
		g_hMemBitmap = CreateCompatibleBitmap(hdc, rWinSize.right, rWinSize.bottom);
		g_hMemBitmapold = (HBITMAP)SelectObject(g_hMemDC, g_hMemBitmap);
		ReleaseDC(hWnd, hdc);

		//-------------------------------------------------------------------------------------------------------
		// MemDC 리셋
		//-------------------------------------------------------------------------------------------------------
		PatBlt(g_hMemDC, 0, 0, rWinSize.right, rWinSize.bottom, WHITENESS);

		g_Tree.PrintNode(g_hMemDC, rWinSize);
		g_Tree.PrintCount(g_hMemDC);
		hdc = BeginPaint(hWnd, &ps);
	
		//-------------------------------------------------------------------------------------------------------
		// 실제 윈도우에 그림
		//-------------------------------------------------------------------------------------------------------
		BitBlt(hdc, 0, 0, rWinSize.right, rWinSize.bottom, g_hMemDC, 0, 0, SRCCOPY);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}