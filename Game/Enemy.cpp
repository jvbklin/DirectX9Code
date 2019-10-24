//=================================================================================
//
//    Enemy cpp
//    Author : Lin He                                        作成日 : 2018/11/15
//
//=================================================================================

#include "Enemy.h"

#include "../Base/Polygon2D.h"
#include "../Base/PolygonUI.h"

#include "../Base/DirectX9.h"
#include "../Game/TextureManager.h"

void Enemy::Init(float pos_x, float pos_y, int data_id)
{
	type_ = ENEMY;

	pos_.x	   = 
	pos_old_.x = pos_x;
	pos_.y =
	pos_old_.y = pos_y;

	is_enabled_ = true;
	is_dead_ = false;

	hp_		= 
	hp_max_ = EnemyDataList[data_id].hp;
	sp_ =
	sp_max_ = 0;			//EnemyはSkillを使うときsp消耗が不要なので、spを0に
	atk_	= EnemyDataList[data_id].atk;
	spd_	= EnemyDataList[data_id].spd;

	action_time_ = 0;

	texture_	  = TextureManager::enemy_textures[EnemyDataList[data_id].texture_enum];
	avatar_texture_ = TextureManager::enemy_avatar_textures[EnemyDataList[data_id].texture_enum];

	animation_count_ = 0;
	animation_count_max_ = 10;
	animation_index_ = 0;
}

void Enemy::Uninit()
{

}

void Enemy::Update()
{
	if (!is_enabled_)
		return;

	animation_count_++;
	if (animation_count_ >= animation_count_max_)
	{
		animation_count_ = 0;

		animation_index_++;
		if (animation_index_ >= 3)
		{
			animation_index_ = 0;
		}
	}
}

void Enemy::Draw()
{
	if (!is_enabled_)
		return;

	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawPolygon2D(pos_.x, pos_.y, 1.0f, 1.0f, 256, 128, animation_index_ * 64, 0, 64, 64);
}

void Enemy::Die()
{
	is_dead_ = true;
	is_enabled_ = false;
}

Vector2 Enemy::GetContactPos()
{
	return Vector2(pos_.x - 1.5f, pos_.y);
}