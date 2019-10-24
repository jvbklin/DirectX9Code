//=================================================================================
//
//    Battle Skill header
//    Author : Lin He                                        作成日 : 2019/01/13
//
//=================================================================================

#ifndef _BATTLE_SKILL_H_
#define _BATTLE_SKILL_H_

#include "Element.h"
#include "Animation.h"

//ターゲットタイプ
enum TARGET_TYPE
{
	TARGET_SELF,
	TARGET_ALLY_SINGLE,
	TARGET_ALLY_ALL,
	TARGET_ENEMY_SINGLE,
	TARGET_ENEMY_ALL
};

//*****************************************************************************
// SkillBase Class
//*****************************************************************************
class SkillBase {
public:
	SkillBase(const wchar_t* name, TARGET_TYPE target_type, Element::Type element_type, ANIM_ENUM anim_enum, int cool_down)
		: name_(name), target_type_(target_type), element_type_(element_type), anim_enum_(anim_enum), cool_down_(cool_down)
	{}

	//スキルの名前
	const wchar_t* name_;
	
	//スキルのターゲットタイプ
	TARGET_TYPE target_type_;

	//スキルのエレメント属性
	Element::Type element_type_;

	//スキルのアニメーションID
	ANIM_ENUM anim_enum_;

	//CD、スキルのクールダウン値
	int cool_down_;
};

//*****************************************************************************
// Skill Class
//*****************************************************************************
class Skill : public SkillBase
{
public:
	Skill(const wchar_t* name, TARGET_TYPE target_type,Element::Type element_type, ANIM_ENUM anim_enum, int cool_down,
				int sp_cost, int element_earn, int damage)
		:SkillBase(name, target_type, element_type,anim_enum, cool_down), 
				sp_cost_(sp_cost), element_earn_(element_earn),damage_(damage)
	{}

	//スキルのSPコスト
	int sp_cost_;
	//スキルを通して得られるエレメント値
	int element_earn_;
	//スキルの基礎ダメージ
	int damage_;
};

//スキルENUM
enum SKILL_ENUM
{
	SKILL_EARTH_ATTACK = 0,
	SKILL_FIRE_ATTACK,
	SKILL_WIND_ATTACK,
	SKILL_WATER_ATTACK,
	SKILL_MAX
};

//スキルデータテーブル
static const Skill skill_data[SKILL_MAX] = {
	//名前　		 ターゲットタイプ　     エレメント属性　  アニメーションID　         CD	　SPコスト　得るエレメント値	基礎ダメージ
	{L"地の攻撃", TARGET_ENEMY_SINGLE, Element::EATRTH, ANIM_SKILL_EARTH_ATTACK, 120,	3,		1,				20},
	{L"火の攻撃", TARGET_ENEMY_SINGLE, Element::FIRE,   ANIM_SKILL_FIRE_ATTACK,  120,	3,		1,				20},
	{L"風の攻撃", TARGET_ENEMY_SINGLE, Element::WIND,   ANIM_SKILL_WIND_ATTACK,  120,	3,		1,				30},
	{L"水の攻撃", TARGET_ENEMY_SINGLE, Element::WATER,  ANIM_SKILL_WATER_ATTACK, 120,	3,		1,				40}
};

//=================================================================
// [ スキルデータ取得関数 ]
//
// [ Parameter ]
// [ SKILL_ENUM ] skill_id	: スキルID
//
// [ Return ]
//	 Skill&					: スキルデータ
//=================================================================
const Skill& GetSkill(SKILL_ENUM skill_id);


//---------------------------------------------------------------------------------------------
// Alchemy
//---------------------------------------------------------------------------------------------
class Alchemy : public SkillBase
{
public:
	Alchemy(const wchar_t* name, TARGET_TYPE target_type, Element::Type element_type, ANIM_ENUM anim_enum, int cool_down_time,
		int element_cost, int element_bonus, int damage)
		:SkillBase(name, target_type, element_type, anim_enum, cool_down_time), element_cost_(element_cost), element_bonus_(element_bonus), damage_(damage)
	{}

	int element_cost_;
	int element_bonus_;
	int damage_;
};

enum ALCHEMY_ENUM
{
	ALCHEMY_EARTH_STRIKE = 0,
	ALCHEMY_FIRE_EXPLOSION,
	ALCHEMY_WIND_TEMPEST,
	ALCHEMY_WATER_HEAL,
	ALCHEMY_MAX
};

static const Alchemy alchemy_data[ALCHEMY_MAX] = {
	{L"Earth Strike",	TARGET_ENEMY_SINGLE, Element::EATRTH, ANIM_ALCHEMY_EARTH_STRIKE, 150, 1, 50, 10},
	{L"Fire Explosion", TARGET_ENEMY_SINGLE, Element::FIRE,   ANIM_ALCHEMY_EARTH_STRIKE, 150, 1, 50, 10},
	{L"Wind Tempest",	TARGET_ENEMY_SINGLE, Element::WIND,   ANIM_ALCHEMY_EARTH_STRIKE, 150, 1, 50, 10},
	{L"Water Heal",		TARGET_ALLY_SINGLE,  Element::WATER,  ANIM_ALCHEMY_WATER_HEAL,	 150, 1, 50, -15},
};

const Alchemy& GetAlchemy(ALCHEMY_ENUM alchemy_id);

#endif