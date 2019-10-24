//=================================================================================
//
//    Text cpp
//    Author : Lin He                                        作成日 : 2010/01/17
//
//=================================================================================
#include "Text.h"
#include <stdio.h>

#include "../main.h"
#include "DirectX9.h"

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************
static LPD3DXFONT g_pFont;

//=====================================================================
// [ テキスト初期化関数 ]
//=====================================================================
void InitText()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		return;
	}

	D3DXCreateFont(pDevice,
		28, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		L"Terminal",
		&g_pFont);
}

//=====================================================================
// [ テキスト終了化関数 ]
//=====================================================================
void UninitText()
{
	SAFE_RELEASE(g_pFont);
}

//=====================================================================
// [ テキスト描画関数 ]
//=====================================================================
void DrawCustomText(int x, int y, int width, int height, LPCWSTR pText)
{
	RECT rect = { x, y, x + width, y + height };

	g_pFont->DrawText(NULL,
		pText,
		-1,
		&rect,
		DT_VCENTER,
		D3DCOLOR_RGBA(0, 0, 0, 255));
}