//=================================================================================
//
//    DX game
//    Author : Lin He                                        作成日 : 2018/11/14
//
//=================================================================================

#include "main.h"

#include <stdio.h>

#include "Base/DirectX9.h"

//*****************************************************************************
// Macro Definition
//*****************************************************************************
#define CLASS_NAME		L"DXGame"
#define WINDOW_NAME		L"DXGame"

//=====================================================================
// [ ウィンドウプロシージャ―関数 ]
//
// [ Parameters ]
// hWnd           : ウィンドウハンドル
// uMsg           : 発生したメッセージ
// wParam, lParam : 発生したメッセージの付加情報
//
// [ Return ]
// LRESULT型 : ウィンドウプロシージャから返される32ビットの値
//
// [ Details ]
// 各種メッセージの処理を行う
//=====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=====================================================================
// [ アプリケーションのエントリー関数 ]
//
// [ Parameters ]
// hInstance     : インスタンスハンドル(ここのプログラムを識別する)
// hPrevinstance : Win16の産物(使われないので常にNULL)
// lpCmdLine     : コマンドライン引数(文字列)
// nCmdShow      : アプリケーションの初期表示方法の指定
//
// [ Return値 ]
// int型
//
// [ Details ]
// Win32アプリケーションのメイン関数部分
//=====================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 使っていない引数の処理
	lpCmdLine;
	hPrevinstance;

	// ウィンドウクラスの登録
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm = NULL;

	// WNDCLASSEX型のwcexの中身を登録
	RegisterClassEx(&wcex);

	// クライアントサイズの設定
	DWORD WStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
	RECT wr = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	// 矩形データ

	AdjustWindowRect(&wr, WStyle, FALSE);

	int nWindowWidth = wr.right - wr.left;
	int nWindowHeight = wr.bottom - wr.top;

	// ウィンドウの場所を中央に変更
	RECT DesktopRect;

	GetWindowRect(GetDesktopWindow(), &DesktopRect);		// デスクトップサイズの取得
	int nWindowPosX = (DesktopRect.right - nWindowWidth) / 2;
	int nWindowPosY = (DesktopRect.bottom - nWindowHeight) / 2;

	(DesktopRect.right - DesktopRect.left) < nWindowPosX ? nWindowPosX = 0 : nWindowPosX;
	(DesktopRect.bottom - DesktopRect.top) < nWindowPosY ? nWindowPosY = 0 : nWindowPosY;

	// ウィンドウの作成
	HWND hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WStyle,
		nWindowPosX,
		nWindowPosY,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージ&ゲームループ
	MSG msg;
	DWORD dwTime = timeGetTime();
	DWORD dwOldTime = timeGetTime();

	// タイマーの性能を上げる
	timeBeginPeriod(1);

	//初期化(チェックあり)
	if (!InitDirectX9(hInstance, hWnd, TRUE, SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		MessageBox(hWnd, L"初期化に失敗しました!!", L"警告", MB_OK);

		return -1;
	}

	for (;;)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{// メッセージ処理

			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// ゲーム処理
			dwTime = timeGetTime();

			if ((dwTime - dwOldTime) >= (1000 / 60))
			{
				// 更新
				UpdateDirectX9();

				// 描画
				DrawDirectX9();

				// 前回の時刻の更新
				dwOldTime = dwTime;
			}
		}
	}

	// 終了
	UninitDirectX9();

	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=====================================================================
// [ ウィンドウプロシージャ―関数 ]
//
// [ Parameters ]
// hWnd           : ウィンドウハンドル
// uMsg           : 発生したメッセージ
// wParam, lParam : 発生したメッセージの付加情報
//
// [ Return ]
// LRESULT型 : ウィンドウプロシージャから返される32ビットの値
//
// [ 詳細 ]
// 各種メッセージの処理を行う
//=====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_PAINT: // ウィンドウが描画更新する
		{
			ValidateRect(hWnd, NULL); //ウィンドウを更新
			break;
		}
		case WM_DESTROY: // ウィンドウ破棄メッセージ
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN: 
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{// 終了メッセージ

					int nID = MessageBox(hWnd, L"終了しますか？", L"終了メッセージ", MB_YESNO | MB_DEFBUTTON2);
					if (nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
			break;
		}
		case WM_CLOSE:
		{
			int nID = MessageBox(hWnd, L"終了しますか？", L"終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}
		default:
			break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}