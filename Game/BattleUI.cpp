//=================================================================================
//
//    Battle UI cpp
//    Author : Lin He                                        作成日 : 2018/11/17
//
//=================================================================================

#include "BattleUI.h"

#include "../Base/PolygonUI.h"
#include "../Base/Polygon2D.h"

#include "Character.h"

void BattleUI::Init()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bar_null.png", &bar_null_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bar_hp.png", &bar_hp_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/bar_sp.png", &bar_sp_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_null.png", &element_null_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_earth.png", &element_earth_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_fire.png", &element_fire_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_wind.png", &element_wind_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_water.png", &element_water_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/avatar_temp.png", &temp_actor_avatar_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
}

void BattleUI::Uninit()
{
	SAFE_RELEASE(bar_null_texture_);
	SAFE_RELEASE(bar_hp_texture_);
	SAFE_RELEASE(bar_sp_texture_);


	SAFE_RELEASE(element_null_tex_);
	SAFE_RELEASE(element_earth_tex_);
	SAFE_RELEASE(element_fire_tex_);
	SAFE_RELEASE(element_wind_tex_);
	SAFE_RELEASE(element_water_tex_);

	SAFE_RELEASE(temp_actor_avatar_tex_);
}

void BattleUI::DrawHp(float x, float y, int hp_current, int hp_max)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, bar_null_texture_);

	DrawPolygonUI(x, y, 256, 32, 0, 0, 256, 32);

	pDevice->SetTexture(0, bar_hp_texture_);

	int hp_cut_x = static_cast<int>( 256.0f * hp_current / hp_max );

	DrawPolygonUI(x, y, 256, 32, 0, 0, hp_cut_x, 32);
}

void BattleUI::DrawSp(float x, float y, int sp_current, int sp_max)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, bar_null_texture_);

	DrawPolygonUI(x, y, 256, 32, 0, 0, 256, 32);

	pDevice->SetTexture(0, bar_sp_texture_);

	int sp_cut_x = static_cast<int>( 256.0f * sp_current / sp_max );

	DrawPolygonUI(x, y, 256, 32, 0, 0, sp_cut_x, 32);
}

void BattleUI::DrawElement(int num_earth, int num_fire, int num_wind, int num_water)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, element_null_tex_);
	for (int i = 0; i < 10; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 10.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 45.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 80.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 115.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_earth_tex_);
	for (int i = 0; i < num_earth; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 10.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_fire_tex_);
	for (int i = 0; i < num_fire; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 45.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_wind_tex_);
	for (int i = 0; i < num_wind; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 80.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_water_tex_);
	for (int i = 0; i < num_water; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 115.0f, 32, 32, 0, 0, 32, 32);
	}
}

void BattleUI::DrawActorList(std::list<Character*> actor_list)
{	
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	int order_num = 0;
	auto itr = actor_list.begin();

	Character* current_actor = *itr;

	while (itr != actor_list.end())
	{
		LPDIRECT3DTEXTURE9 texture = (*itr)->GetAvatarTexture();
		
		pDevice->SetTexture(0, texture);

		DrawPolygonUI(700.0f + order_num * 80, 20.0f, 64, 64, 0, 0, 64, 64);

		//temp_avaterの外枠描画
		if (itr != actor_list.begin())
		{
			if ((*itr) == current_actor)
			{
				pDevice->SetTexture(0, temp_actor_avatar_tex_);

				DrawPolygonUI(700.0f + order_num * 80, 20.0f, 64, 64, 0, 0, 64, 64);
			}
		}

		order_num++;
		++itr;
	}
}

void BattleUI::DrawEnemyHp(float x, float y, int hp_current, int hp_max)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, bar_null_texture_);

	DrawRect2D(x, y, 4.0f, 0.5f);

	pDevice->SetTexture(0, bar_hp_texture_);

	float hp_percent = (float)hp_current / hp_max;

	DrawRect2D(x, y, 4.0f * hp_percent, 0.5f, 0.0f, hp_percent, 0.0f, 1.0f);
}