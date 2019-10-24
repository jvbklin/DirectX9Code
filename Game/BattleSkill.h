//=================================================================================
//
//    Battle Skill header
//    Author : Lin He                                        �쐬�� : 2019/01/13
//
//=================================================================================

#ifndef _BATTLE_SKILL_H_
#define _BATTLE_SKILL_H_

#include "Element.h"
#include "Animation.h"

//�^�[�Q�b�g�^�C�v
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

	//�X�L���̖��O
	const wchar_t* name_;
	
	//�X�L���̃^�[�Q�b�g�^�C�v
	TARGET_TYPE target_type_;

	//�X�L���̃G�������g����
	Element::Type element_type_;

	//�X�L���̃A�j���[�V����ID
	ANIM_ENUM anim_enum_;

	//CD�A�X�L���̃N�[���_�E���l
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

	//�X�L����SP�R�X�g
	int sp_cost_;
	//�X�L����ʂ��ē�����G�������g�l
	int element_earn_;
	//�X�L���̊�b�_���[�W
	int damage_;
};

//�X�L��ENUM
enum SKILL_ENUM
{
	SKILL_EARTH_ATTACK = 0,
	SKILL_FIRE_ATTACK,
	SKILL_WIND_ATTACK,
	SKILL_WATER_ATTACK,
	SKILL_MAX
};

//�X�L���f�[�^�e�[�u��
static const Skill skill_data[SKILL_MAX] = {
	//���O�@		 �^�[�Q�b�g�^�C�v�@     �G�������g�����@  �A�j���[�V����ID�@         CD	�@SP�R�X�g�@����G�������g�l	��b�_���[�W
	{L"�n�̍U��", TARGET_ENEMY_SINGLE, Element::EATRTH, ANIM_SKILL_EARTH_ATTACK, 120,	3,		1,				20},
	{L"�΂̍U��", TARGET_ENEMY_SINGLE, Element::FIRE,   ANIM_SKILL_FIRE_ATTACK,  120,	3,		1,				20},
	{L"���̍U��", TARGET_ENEMY_SINGLE, Element::WIND,   ANIM_SKILL_WIND_ATTACK,  120,	3,		1,				30},
	{L"���̍U��", TARGET_ENEMY_SINGLE, Element::WATER,  ANIM_SKILL_WATER_ATTACK, 120,	3,		1,				40}
};

//=================================================================
// [ �X�L���f�[�^�擾�֐� ]
//
// [ Parameter ]
// [ SKILL_ENUM ] skill_id	: �X�L��ID
//
// [ Return ]
//	 Skill&					: �X�L���f�[�^
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