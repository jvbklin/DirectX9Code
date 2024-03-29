//=================================================================================
//
//    Background cpp
//    Author : Lin He                                        作成日 : 2018/11/21
//
//=================================================================================

#include "Background.h"

#include "../Base/Polygon2D.h"

#include "../Base/DirectX9.h"

//=====================================================================
// [ 背景初期化関数 ]
//=====================================================================
void Background::Init()
{

	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//EnemyStraight Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/background.png", &texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
}

//=====================================================================
// [ 背景終了化関数 ]
//=====================================================================
void Background::Uninit()
{
	SAFE_RELEASE(texture_);
}

//=====================================================================
// [ 背景更新関数 ]
//=====================================================================
void Background::Update()
{

}

//=====================================================================
// [ 背景描画関数 ]
//=====================================================================
void Background::Draw()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawPolygon2D(0.0f, 0.0f, 16.0f, 9.0f, 700, 490, 0, 0, 700, 490);
}