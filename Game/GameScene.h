//=================================================================================
//
//    GameScene header
//    Author : Lin He                                        �쐬�� : 2018/11/15
//
//=================================================================================

#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include <vector>
#include <list>
#include <set>

#include "../Base/DirectX9.h"
#include "BattleAction.h"
#include "BattleSkill.h"

class Camera;
class Background;

class BattleUI;
class CommandUI;
class ElementUI;

class Character;
class PlayerCharacter;
class Enemy;

class AnimationManager;

class GameScene
{

public:
	enum BATTLE_STATE
	{
		START_BATTLE,
		PROCESS_BATTLE,
		END_BATTLE
	};

	BATTLE_STATE battle_state_;

	enum TURN_STATE
	{
		START_TURN,
		PLAYER_CHOOSE_ACTION,
		PROCESS_TURN
	};

	TURN_STATE turn_state_;

//---------------------------------------------------------------------------------

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void StartBattle();
	void ProcessBattle();
	void EndBattle();

	void StartTurn();
	void PlayerChooseAction();
	void ProcessTurn();

	void DecreaseAllActorsTime();

	void AddPlayerCharacter(float posX, float posY, int player_data_id);
	void AddEnemy(float posX, float posY, int enemy_data_id);

	void CheckTargetIsDied(Character* target);

	void ActorChooseTarget(int target_id);
	void ActorUseAttack(int attack_id);
	void ActorUseSkill(SKILL_ENUM skill_id);
	void ActorUseAlchemy(ALCHEMY_ENUM alchemy_id);

	void SortActorList();
	void MoveCurrentActorToNext(Character* actor);
	void InsertCharacterToActorList(Character* actor);

	std::vector<Character*>& GetCharacterList();
	std::set<int>& GetEnemyIdList();
	std::set<int>& GetPlayerIdList();

	std::list<Character*>& GetActorList();

//---------------------------------------------------------------------------------

public:

	Camera* camera_;
	Background* background_;

	ElementUI* element_ui_;
	BattleUI* battle_ui_;
	CommandUI* command_ui_;

	AnimationManager* animation_manager_;


	//�o�g�����g�����f�Z�b�g
	ElementSet battle_element_;

	//�o�g�������ׂẴL�������Ǘ����郊�X�g
	std::vector<Character*> character_list_;

	//�v���C���[�L�������Ǘ����郊�X�g�Aid�Ńv���C���[�̃|�C���^�������Ɍ���
	std::set<int> player_id_list_;

	//�G�L�������Ǘ����郊�X�g�Aid�œG�̃|�C���^�������Ɍ���
	std::set<int> enemy_id_list_;

	//�L�����̍s�����Ԃ��Ǘ����郊�X�g
	std::list<Character*> actor_list_;

	//���ݍs�����Ă���L����
	Character* current_actor_;

	//���ݍs�����Ă���L�����̍s��
	BattleAction actor_action_;

};

#endif