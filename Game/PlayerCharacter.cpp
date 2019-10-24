//=================================================================================
//
//    Character cpp
//    Author : Lin He                                        作成日 : 2018/11/15
//
//=================================================================================

#include "PlayerCharacter.h"

#include "../Base/DirectX9.h"
#include "../Base/Polygon2D.h"
#include "../Base/PolygonUI.h"

#include "../Game/TextureManager.h"


void PlayerCharacter::Init(float pos_x, float pos_y, int data_id)
{
	type_ = PLAYER;

	hp_ = 20;
	hp_max_ = 20;
	sp_ = 5;
	sp_max_ = 10;

	atk_ = 10;
	spd_ = 40;

	pos_.x     =
	pos_old_.x = pos_x;
	pos_.y     =
	pos_old_.y = pos_y;

	is_enabled_ = true;
	is_dead_ = false;

	action_time_ = 0;

	data_id;
	texture_ = TextureManager::player_textures[PLAYER_ONE];
	avatar_texture_ = TextureManager::player_avatar_textures[PLAYER_ONE];
}

void PlayerCharacter::Uninit()
{
}

void PlayerCharacter::Update()
{
}

void PlayerCharacter::Die()
{
	is_dead_ = true;
}

void PlayerCharacter::Draw()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawPolygon2D(pos_.x, pos_.y, 1.0f, 1.0f, 74, 59, 0, 0, 74, 59);
}

Vector2 PlayerCharacter::GetContactPos()
{
	return Vector2(pos_.x + 1.5f, pos_.y);
}