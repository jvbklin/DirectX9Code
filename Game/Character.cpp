//=================================================================================
//
//    Character cpp
//    Author : Lin He                                        ì¬“ú : 2018/12/18
//
//=================================================================================

#include "Character.h"

#include "../Base/Polygon2D.h"
#include "../Base/PolygonUI.h"

#include "../Base/DirectX9.h"

unsigned int Character::id_counter_ = 0;

Character::Character()
{
	id_ = id_counter_;
	++id_counter_;
}

Character::Type Character::GetType()
{
	return type_;
}

int Character::GetId()
{
	return id_;
}

int Character::GetHp()
{
	return hp_;
}

int Character::GetHpMax()
{
	return hp_max_;
}

int Character::GetSp()
{
	return sp_;
}

int Character::GetSpMax()
{
	return sp_max_;
}

int Character::GetAtk()
{
	return atk_;
}

int Character::GetSpd()
{
	return spd_;
}

int Character::GetActionTime() const
{
	return action_time_;
}

Vector2 Character::GetPos()
{
	return pos_;
}

Vector2 Character::GetPosOld()
{
	return pos_old_;
}

bool Character::IsEnabled()
{
	return is_enabled_;
}

bool Character::IsDead()
{
	return is_dead_;
}

LPDIRECT3DTEXTURE9 Character::GetAvatarTexture()
{
	return avatar_texture_;
}

void Character::IncreaseHp(int value)
{
	hp_ += value;

	if (hp_ >= hp_max_)
		hp_ = hp_max_;
}
void Character::IncreaseSp(int value)
{
	sp_ += value;

	if (sp_ >= sp_max_)
		sp_ = sp_max_;
}

void Character::IncreaseActionTime(int value)
{
	action_time_ += value;
}

int Character::GetCoolDownTime(int action_cool_down) const
{
	return static_cast<int>(100.0f * action_cool_down / spd_);
}

int Character::GetActionTimeAfterCoolDown(int action_cool_down) const
{
	return action_time_ + static_cast<int>(100.0f * action_cool_down / spd_);
}


void Character::UpdateActionCoolDown(int action_cool_down)
{
	//int cool_down_time = static_cast<int>(100.0f * action_cool_down / spd_);
	action_time_ += GetCoolDownTime(action_cool_down);
}

void Character::GetDamage(int value)
{
	hp_ -= value;

	if (hp_ <= 0)
	{
		hp_ = 0;
		Die();
		return;
	}

	if (hp_ >= hp_max_)
		hp_ = hp_max_;
}

void Character::MoveToPos(Vector2 pos)
{
	pos_.x = pos.x;
	pos_.y = pos.y;
}

Vector2 Character::GetContactPos()
{
	return Vector2(pos_.x + 1.5f, pos_.y);
}