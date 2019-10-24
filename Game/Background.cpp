//=================================================================================
//
//    Background cpp
//    Author : Lin He                                        ì¬“ú : 2018/11/21
//
//=================================================================================

#include "Background.h"

#include "../Base/Polygon2D.h"

#include "../Base/DirectX9.h"

//=====================================================================
// [ ”wŒi‰Šú‰»ŠÖ” ]
//=====================================================================
void Background::Init()
{

	// D3DDevice‚ÌŽæ“¾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXƒfƒoƒCƒXŽæ“¾Ž¸”s‚µ‚½", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//EnemyStraight Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/background.png", &texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"ƒeƒNƒXƒ`ƒƒ[‚ª“Ç‚Ýž‚Ý‚È‚©‚Á‚½", L"error", MB_OK);
		return;
	}
}

//=====================================================================
// [ ”wŒiI—¹‰»ŠÖ” ]
//=====================================================================
void Background::Uninit()
{
	SAFE_RELEASE(texture_);
}

//=====================================================================
// [ ”wŒiXVŠÖ” ]
//=====================================================================
void Background::Update()
{

}

//=====================================================================
// [ ”wŒi•`‰æŠÖ” ]
//=====================================================================
void Background::Draw()
{
	// D3DDevice‚ÌŽæ“¾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXƒfƒoƒCƒXŽæ“¾Ž¸”s‚µ‚½", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawPolygon2D(0.0f, 0.0f, 16.0f, 9.0f, 700, 490, 0, 0, 700, 490);
}