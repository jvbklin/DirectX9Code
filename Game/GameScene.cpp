//=================================================================================
//
//    GameScene cpp
//    Author : Lin He                                        作成日 : 2018/11/15
//
//=================================================================================

#include "GameScene.h"

#include "../main.h"
#include "../Base/DirectX9.h"
#include "../Base/Camera.h"


#include "TextureManager.h"


#include "Character.h"
#include "PlayerCharacter.h"
#include "Enemy.h"

#include "Background.h"

#include "BattleUI.h"

#include "Element.h"

#include "CommandUI.h"

#include "Animation.h"

#include "BattleSkill.h"

void GameScene::Init()
{
	camera_ = new Camera;
	camera_->Init();

	background_ = new Background;
	background_->Init();

	element_ui_ = new ElementUI;
	element_ui_->Init();

	battle_ui_ = new BattleUI;
	battle_ui_->Init();

	command_ui_ = new CommandUI;
	command_ui_->Init(this);

	animation_manager_ = new AnimationManager;
	animation_manager_->Init();

	TextureManager::LoadAllTexture();

	AddPlayerCharacter(-6.0f, 0.0f, (int)PLAYER_ONE);

	AddEnemy(3.5f, 2.1f, (int)ENEMY_GREEN_BIRD);
	AddEnemy(4.0f, -2.0f, (int)ENEMY_BAT_BIRD);
	AddEnemy(7.5f, 1.0f, (int)ENEMY_BROWN_BIRD);

	battle_state_ = GameScene::START_BATTLE;
	turn_state_   = GameScene::START_TURN;

}

void GameScene::Uninit()
{

	for (auto const& pCharacter : character_list_) {
		pCharacter->Uninit();
	}

	player_id_list_.clear();
	enemy_id_list_.clear();
	actor_list_.clear();

	TextureManager::ReleaseAllTexture();

	animation_manager_->Uninit();
	delete animation_manager_;

	command_ui_->Uninit();
	delete command_ui_;

	battle_ui_->Uninit();
	delete battle_ui_;

	element_ui_->Uninit();
	delete 	element_ui_;

	background_->Uninit();
	delete 	background_;

	delete camera_;
}

void GameScene::Update()
{
	//ゲームシーンの更新
	switch (battle_state_)
	{
		case GameScene::START_BATTLE:
		{
			StartBattle();
			break;
		}
		case GameScene::PROCESS_BATTLE:
		{
			ProcessBattle();
			break;
		}
		case GameScene::END_BATTLE:
		{
			EndBattle();
			break;
		}
		default:
			break;
	}
}

void GameScene::Draw()
{
	//背景の描画
	background_->Draw();

	//敵キャラの描画
	for (auto const& enemy_id : enemy_id_list_) 
	{
		character_list_[enemy_id]->Draw();
	}

	//プレイヤーキャラの描画
	for (auto const& player_id : player_id_list_)
	{
		character_list_[player_id]->Draw();
	}

	//ターンの描画
	switch (turn_state_)
	{
		case GameScene::START_TURN:
		{
			//Nothing
			break;
		}
		case GameScene::PLAYER_CHOOSE_ACTION:
		{
			command_ui_->Draw();
			break;
		}
		case GameScene::PROCESS_TURN:
		{
			animation_manager_->Draw();
			break;
		}
		default:
			break;
	}

	//元素の描画
	element_ui_->Draw(battle_element_);

	//キャラクターのステータスの描画
	PlayerCharacter* player = static_cast<PlayerCharacter*> (character_list_[0]);
	battle_ui_->DrawHp(200.0f,600.0f, player->GetHp(), player->GetHpMax());
	battle_ui_->DrawSp(200.0f,650.0f, player->GetSp(), player->GetSpMax());

	//敵キャラのHP描画
	for (auto const& enemy_id : enemy_id_list_) 
	{
		auto const& pEnemy = character_list_[enemy_id];
		battle_ui_->DrawEnemyHp(pEnemy->GetPos().x - 2.0f, pEnemy->GetPos().y - 1.5f, pEnemy->GetHp(), pEnemy->GetHpMax());
	}
	
	//行動順番のアバターリストの描画
	battle_ui_->DrawActorList(actor_list_);
}

void GameScene::StartBattle()
{
	//今はなにもない
	//SortActors();
	//SpendAllActorsTime();
	//Character& actor = actor_list_.begin();

	//バトルの初期元素値
	battle_element_ = { 1,1,1,1 };

	//デフォルト行動
	actor_action_.id = 0;
	actor_action_.target_id = 0;


	//全キャラの初期Action Timeを決定する
	int action_cool_down = 60;
	for (auto const& character : character_list_)
	{
		character->UpdateActionCoolDown(action_cool_down);
	}

	//行動リストをソートする
	SortActorList();

	//行動するキャラを決定する
	current_actor_ = actor_list_.front();

	battle_state_ = GameScene::PROCESS_BATTLE;
}

void GameScene::ProcessBattle()
{
	//敵キャラの更新（現在はただアニメーションを付けるだけ）
	for (auto const& enemy_id : enemy_id_list_) {
		character_list_[enemy_id]->Update();
	}

	switch (turn_state_)
	{
		case GameScene::START_TURN :
		{
			StartTurn();
			break;
		}
		case GameScene::PLAYER_CHOOSE_ACTION : 
		{
			PlayerChooseAction();
			break;
		}
		case GameScene::PROCESS_TURN :
		{
			ProcessTurn();
			break;
		}
	}
}

void GameScene::EndBattle()
{
	//今はなにもない
}

void GameScene::StartTurn()
{
	DecreaseAllActorsTime();


	current_actor_ = actor_list_.front();

	//if (actor is in abnormal state)
	//{
	//	actor choose action with abnormal state();
	//	turn_state = ProcessAction;
	//	break;
	//}

	if (current_actor_->GetType() == Character::PLAYER)
	{
		turn_state_ = GameScene::PLAYER_CHOOSE_ACTION;
	}
	else// actor is enemy, so just choose an action and process it
	{
		//enemy choose action and target()
		//action_code = enemy action;
		//target_id = enemy choose player;
		//turn_state = ProcessAction;


		//エネミーが行動を選択する
		ActorUseAttack(1);
		//エネミーがターゲットを選択する
		ActorChooseTarget( *(player_id_list_.begin()) );

		turn_state_ = GameScene::PROCESS_TURN;
	}
}

void GameScene::PlayerChooseAction()
{
	//if (player has chosen action and target())
	//{
	//	action_code = player choose action;
	//	target_id = player choose enemy;
	//	turn_state = ProcessAction;
	//}

	if (command_ui_->Update() == true)
	{
		turn_state_ = GameScene::PROCESS_TURN;
	}
}

void GameScene::ProcessTurn()
{
	//if (!current_action->AnimationIsDone())
	//{
	//	ProcessActionAnimation()
	//		break;
	//}

	//target get damage
	//DealWithActionDamage();

	//if (target is dead)
	//{
	//	DealWithDeath();
	//	break;
	//}

	//target get debuff, get at delay,etc
	//DealWithActionEffect();

	//SortActors();

	Character*& target = character_list_[actor_action_.target_id];

	switch (actor_action_.type)
	{
		case BattleAction::STANDBY :
		{
			//do nothing
			break;
		}
		case BattleAction::ATTACK :
		{
			current_actor_->MoveToPos(target->GetContactPos());

			//アニメーション中、まだダメージ処理とかに進まない
			if (! animation_manager_->PlayAnimation(actor_action_.anim_enum, target->GetPos().x, target->GetPos().y))
				break;

			current_actor_->MoveToPos(current_actor_->GetPosOld());

			target->GetDamage(current_actor_->GetAtk());
			CheckTargetIsDied(target);

			current_actor_->IncreaseSp(1);

			//actor_list_.splice(actor_list_.end(), actor_list_, actor_list_.begin());

			current_actor_->UpdateActionCoolDown(60);
			//InsertCharacterToActorList(current_actor_);
			//actor_list_.pop_front();
			
			MoveCurrentActorToNext(current_actor_);

			turn_state_ = GameScene::START_TURN;

			break;
		}
		case BattleAction::SKILL :
		{
			current_actor_->MoveToPos(target->GetContactPos());

			//アニメーション中、まだダメージ処理とかに進まない
			if (! animation_manager_->PlayAnimation(actor_action_.anim_enum, target->GetPos().x, target->GetPos().y))
				break;

			current_actor_->MoveToPos(current_actor_->GetPosOld());

			SKILL_ENUM id = static_cast<SKILL_ENUM>(actor_action_.id);
			const Skill& skill = GetSkill(id);

			target->GetDamage(current_actor_->GetAtk() + skill.damage_);
			CheckTargetIsDied(target);

			current_actor_->IncreaseSp(-skill.sp_cost_);
			battle_element_.IncreaseElement(skill.element_type_, skill.element_earn_);

			current_actor_->UpdateActionCoolDown(skill.cool_down_);
			//actor_list_.splice(actor_list_.end(), actor_list_, actor_list_.begin());
			//InsertCharacterToActorList(current_actor_);

			MoveCurrentActorToNext(current_actor_);

			turn_state_ = GameScene::START_TURN;

			break;
		}
		case BattleAction::ALCHEMY :
		{
			//アニメーション中、まだダメージ処理とかに進まない
			if (! animation_manager_->PlayAnimation(actor_action_.anim_enum, target->GetPos().x, target->GetPos().y))
				break;

			ALCHEMY_ENUM id = static_cast<ALCHEMY_ENUM>(actor_action_.id);
			const Alchemy& alchemy = GetAlchemy(id);

			target->GetDamage(alchemy.damage_);
			CheckTargetIsDied(target);

			battle_element_.IncreaseElement(alchemy.element_type_, -alchemy.element_cost_);

			current_actor_->UpdateActionCoolDown(alchemy.cool_down_);
			//actor_list_.splice(actor_list_.end(), actor_list_, actor_list_.begin());
			//InsertCharacterToActorList(current_actor_);

			MoveCurrentActorToNext(current_actor_);

			turn_state_ = GameScene::START_TURN;
			break;
		}
		default:
			break;
	}
}

std::vector<Character*>& GameScene::GetCharacterList()
{
	return character_list_;
}

std::set<int>& GameScene::GetEnemyIdList()
{
	return enemy_id_list_;
}

std::set<int>& GameScene::GetPlayerIdList()
{
	return player_id_list_;
}

std::list<Character*>& GameScene::GetActorList()
{
	return actor_list_;
}

void GameScene::CheckTargetIsDied(Character* target)
{
	if (target->IsDead())
	{
		if (target->GetType() == Character::PLAYER)
		{
			//今は何もしない
		}
		else if(target->GetType() == Character::ENEMY)
		{
			auto iterator = enemy_id_list_.find(target->GetId());
			enemy_id_list_.erase(iterator);

			actor_list_.remove(target);
		}
	}
}

void GameScene::AddPlayerCharacter(float posX, float posY, int player_data_id)
{
	Character* pPlayer = new PlayerCharacter;
	pPlayer->Init(posX, posY, player_data_id);

	character_list_.push_back(pPlayer);

	player_id_list_.insert(pPlayer->GetId());

	actor_list_.push_back(pPlayer);

}

void GameScene::AddEnemy(float posX, float posY, int enemy_data_id)
{
	Character* pEnemy = new Enemy;
	pEnemy->Init(posX,posY,enemy_data_id);

	character_list_.push_back(pEnemy);

	enemy_id_list_.insert(pEnemy->GetId());

	actor_list_.push_back(pEnemy);
}

void GameScene::ActorChooseTarget(int target_id)
{
	actor_action_.target_id = target_id;
}

void GameScene::ActorUseAttack(int attack_id)
{
	actor_action_.type = BattleAction::ATTACK;

	actor_action_.id = 0;

	actor_action_.anim_enum = static_cast<ANIM_ENUM>(attack_id);
}

void GameScene::ActorUseSkill(SKILL_ENUM skill_id)
{
	actor_action_.type = BattleAction::SKILL;

	actor_action_.id = skill_id;

	const Skill& actor_skill = GetSkill(skill_id);
	actor_action_.anim_enum = actor_skill.anim_enum_;
}

void GameScene::ActorUseAlchemy(ALCHEMY_ENUM alchemy_id)
{
	actor_action_.type = BattleAction::ALCHEMY;

	actor_action_.id = alchemy_id;

	const Alchemy& actor_alchemy = GetAlchemy(alchemy_id);
	actor_action_.anim_enum = actor_alchemy.anim_enum_;
}

void GameScene::SortActorList()
{
	actor_list_.sort([](const Character* const character1, const Character* const character2)
	{
		return character1->GetActionTime() < character2->GetActionTime();
	});
}

void GameScene::MoveCurrentActorToNext(Character* actor)
{
	auto iter = ++actor_list_.begin();

	while (iter != actor_list_.end())
	{
		if (actor->GetActionTime() < (*iter)->GetActionTime())
			break;

		++iter;
	}

	actor_list_.splice(iter, actor_list_, actor_list_.begin());
}

void GameScene::InsertCharacterToActorList(Character* actor)
{
	auto iter = ++actor_list_.begin();

	while (iter != actor_list_.end())
	{
		if (actor->GetActionTime() < (*iter)->GetActionTime())
			break;

		++iter;
	}

	actor_list_.insert(iter, actor);
}

void GameScene::DecreaseAllActorsTime()
{
	int action_time_delta = actor_list_.front()->GetActionTime();

	for (auto const& actor : actor_list_)
	{
		actor->IncreaseActionTime(-action_time_delta);
	}
}