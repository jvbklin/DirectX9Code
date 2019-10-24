//=================================================================================
//
//    Battle Action header
//    Author : Lin He                                        �쐬�� : 2019/01/13
//
//=================================================================================

#ifndef _BATTLE_ACTION_H_
#define _BATTLE_ACTION_H_

#include "Animation.h"

//*****************************************************************************
//	BattleAction
//
//�@�퓬���L�����N�^�[���s���s����\���\����
//	�s���́AType��Id�������āAType����ǂ��������ȍs�����Ƃ邩�i�ǂ̃e�[�u���f�[�^���g�����j�����߂āA
//	Id�����̓I�ɍs�������߂�
//	��: type=SKILL,id = 0�̍s���́ASKILL�e�[�u����0�Ԃ̃f�[�^���g���s���ł���
//*****************************************************************************
struct BattleAction
{
	//�s���̎��enum
	enum Type
	{
		STANDBY,
		ATTACK,
		SKILL,
		ALCHEMY
	};

	//�s���̎��
	Type type;

	//�s��ID
	int id;
	//�s���̃^�[�Q�b�g��ID
	int target_id;
	//�s���̃A�j���[�V����ID
	ANIM_ENUM anim_enum;
};

#endif