// RedBlackTree.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Winmain.h"

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
HWND g_hWnd;
HDC g_hMemDC;
HBITMAP g_hMemBitmap;
HBITMAP g_hMemBitmapold;
RECT rWinSize;
CRedBlackTree g_Tree;

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
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

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

	g_hWnd = CreateWindow(L"RedBlackTree", L"RedBlackTree", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	GetClientRect(g_hWnd, &rWinSize);

	if (!g_hWnd)
	{
		return FALSE;
	}

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	// �⺻ �޽��� �����Դϴ�.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
		// MemDC �����
		//-------------------------------------------------------------------------------------------------------
		hdc = GetDC(hWnd);
		g_hMemDC = CreateCompatibleDC(hdc);
		g_hMemBitmap = CreateCompatibleBitmap(hdc, rWinSize.right, rWinSize.bottom);
		g_hMemBitmapold = (HBITMAP)SelectObject(g_hMemDC, g_hMemBitmap);
		ReleaseDC(hWnd, hdc);

		//-------------------------------------------------------------------------------------------------------
		// MemDC ����
		//-------------------------------------------------------------------------------------------------------
		PatBlt(g_hMemDC, 0, 0, rWinSize.right, rWinSize.bottom, WHITENESS);

		g_Tree.PrintNode(g_hMemDC, rWinSize);
		g_Tree.PrintCount(g_hMemDC);
		hdc = BeginPaint(hWnd, &ps);
	
		//-------------------------------------------------------------------------------------------------------
		// ���� �����쿡 �׸�
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