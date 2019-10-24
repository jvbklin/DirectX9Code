//=================================================================================
//
//    Command UI cpp
//    Author : Lin He                                        作成日 : 2018/11/22
//
//=================================================================================

#include "CommandUI.h"

#include <stdio.h>

#include "../Base/PolygonUI.h"
#include "../Base/Polygon2D.h"
#include "../Base/Text.h"
#include "../Base/input.h"

#include "GameScene.h"
#include "BattleSkill.h"

#include "Element.h"

#include "Character.h"
#include "PlayerCharacter.h"
#include "Enemy.h"

static const float UI_SELECTION_POS_X = 380;

static const float UI_SELECTION_ONE_POS_Y = 200;
static const float UI_SELECTION_TWO_POS_Y = 250;
static const float UI_SELECTION_THREE_POS_Y = 300;

static const float UI_SELECTOR_POS_X = 340;
static const float UI_SELECTOR_POS_Y = 209;

static const int UI_SELECTION_WIDTH  = 100;
static const int UI_SELECTION_HEIGHT = 50;

static const int UI_SKILL_SELECTION_WIDTH = 200;
static const int UI_SKILL_SELECTION_HEIGHT = 50;

static const int UI_SELECTOR_WIDTH  = 32;
static const int UI_SELECTOR_HEIGHT = 32;


void CommandUI::Init(GameScene* scene)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_attack.png", &ui_attack_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_skill.png", &ui_skill_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_alchemy.png", &ui_alchemy_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_skill_selection.png", &ui_selection_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/sankake.png", &ui_sankake_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/target_selection.png", &ui_target_selection_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}

	menu_root_selector_  = 0;
	menu_skill_selector_ = 0;

	command_ui_state_ = 
	command_ui_state_back_ = CommandUI::COMMAND_ROOT;

	game_scene_ = scene;

}

void CommandUI::Uninit()
{
	SAFE_RELEASE(ui_attack_texture_);
	SAFE_RELEASE(ui_skill_texture_);
	SAFE_RELEASE(ui_alchemy_texture_);

	SAFE_RELEASE(ui_selection_texture_);
	SAFE_RELEASE(ui_sankake_tex_);
}

bool CommandUI::Update()
{
	switch (command_ui_state_)
	{
		case CommandUI::COMMAND_ROOT:
		{
			UpdateRootMenu();
			return false;
		}
		case CommandUI::COMMAND_SKILL:
		{
			UpdateSkillMenu();
			return false;
		}

		case CommandUI::COMMAND_ALCHEMY: 
		{
			UpdateAlchemyMenu();
			return false;
		}

		case CommandUI::COMMAND_CHOOSE_TARGET:
		{
			return UpdateTargetSelection();
		}
	}
	return false;
}

void CommandUI::Draw()
{
	switch (command_ui_state_)
	{
		case CommandUI::COMMAND_ROOT:
		{
			DrawRootMenu();
			break;
		}
		case CommandUI::COMMAND_SKILL:
		{
			DrawSkillMenu();
			break;
		}
		case CommandUI::COMMAND_ALCHEMY:
		{
			DrawAlchemyMenu();
			break;
		}
		case CommandUI::COMMAND_CHOOSE_TARGET:
		{
			DrawTargetSelection();
			break;
		}
	}
}

void CommandUI::UpdateRootMenu()
{
	CInputKeyboard* input_keyboard = GetKeyboard();

	//下ボタンを押したらカーソルを下に移動する
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_root_selector_;
		if (menu_root_selector_ > 2)
			menu_root_selector_ = 2;
	}
	//上ボタンを押したらカーソルを上に移動する
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_root_selector_;
		if (menu_root_selector_ < 0)
			menu_root_selector_ = 0;
	}

	//確定ボタンが押された
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		switch (menu_root_selector_)
		{
		case 0:
			//「攻撃」アクションが選択された
			game_scene_->ActorUseAttack(0);

			//行動リストに一時的なアバターを追加する
			AddActorListTempAvatar(60);

			//ターゲット選択リストを敵リストに設定する
			ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

			//ターゲット選択カーソルを設定する
			target_iterator_ = (*ptr_target_id_list_).begin();

			command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;

			break;
		case 1:
			//「スキル」アクションが選択された
			menu_skill_selector_ = 0;

			command_ui_state_		= 
			command_ui_state_back_	= CommandUI::COMMAND_SKILL;
			break;
		case 2:
			//「錬金術」アクションが選択された
			menu_skill_selector_ = 0;

			command_ui_state_ = 
			command_ui_state_back_ = CommandUI::COMMAND_ALCHEMY;
			break;
		default:
			break;
		}
	}
}

void CommandUI::UpdateSkillMenu()
{
	CInputKeyboard* input_keyboard = GetKeyboard();

	//下ボタンを押したらカーソルを下に移動する
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_skill_selector_;
		if (menu_skill_selector_ >= SKILL_MAX)
			menu_skill_selector_ = SKILL_MAX - 1;
	}
	//上ボタンを押したらカーソルを上に移動する
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_skill_selector_;
		if (menu_skill_selector_ < 0)
			menu_skill_selector_ = 0;
	}

	//確定ボタンが押された
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		SKILL_ENUM id = static_cast<SKILL_ENUM>(menu_skill_selector_);
		const Skill& selected_skill = GetSkill(id);

		const int sp_cost = selected_skill.sp_cost_;

		// 「スキル」を発動するためのSPが足りない
		if (game_scene_->current_actor_->GetSp() < sp_cost)
		{
			//nothing happen
			return;

			//コマンド選択はまだ終わってない
		}

		//「スキル」が選択された
		game_scene_->ActorUseSkill(id);

		//行動リストに一時的なアバターを追加する
		AddActorListTempAvatar(selected_skill.cool_down_);

		//ターゲット選択リストを敵リストに設定する
		ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

		//ターゲット選択カーソルを設定する
		target_iterator_ = (*ptr_target_id_list_).begin();

		command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;
	}
	//キャンセルボタンが押された
	else if (input_keyboard->GetKeyTrigger(DIK_K))
	{
		command_ui_state_ = CommandUI::COMMAND_ROOT;
	}

	//コマンド選択はまだ終わってない

}

void CommandUI::UpdateAlchemyMenu()
{
	CInputKeyboard* input_keyboard = GetKeyboard();

	//下ボタンを押したらカーソルを下に移動する
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_skill_selector_;
		if (menu_skill_selector_ >= ALCHEMY_MAX)
			menu_skill_selector_ = ALCHEMY_MAX - 1;
	}
	//上ボタンを押したらカーソルを上に移動する
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_skill_selector_;
		if (menu_skill_selector_ < 0)
			menu_skill_selector_ = 0;
	}

	//確定ボタンが押された
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		ALCHEMY_ENUM id = static_cast<ALCHEMY_ENUM>(menu_skill_selector_);
		const Alchemy& selected_alchemy = GetAlchemy(id);

		const int element_cost = selected_alchemy.element_cost_;

		//「錬金術」を発動するためのエレメントが足りない
		if (game_scene_->battle_element_.GetElementValue(selected_alchemy.element_type_) < element_cost)
		{
			//nothing happen
			return;

			//コマンド選択はまだ終わってない
		}

		//「錬金術」が選択された
		game_scene_->ActorUseAlchemy(id);

		//行動リストに一時的なアバターを追加する
		AddActorListTempAvatar(selected_alchemy.cool_down_);

		//行動のターゲットタイプに応じてターゲット選択する
		if (selected_alchemy.target_type_ == TARGET_ALLY_SINGLE)
		{
			//ターゲット選択リストを敵リストに設定する
			ptr_target_id_list_ = &(game_scene_->GetPlayerIdList());

			//ターゲット選択カーソルを設定する
			target_iterator_ = (*ptr_target_id_list_).begin();
		}
		else
		{
			//ターゲット選択リストを敵リストに設定する
			ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

			//ターゲット選択カーソルを設定する
			target_iterator_ = (*ptr_target_id_list_).begin();
		}

		command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;

		//コマンド選択はまだ終わってない
		return;
	}
	//キャンセルボタンが押された
	else if (input_keyboard->GetKeyTrigger(DIK_K))
	{
		command_ui_state_ = CommandUI::COMMAND_ROOT;
	}
}

bool CommandUI::UpdateTargetSelection()
{
	CInputKeyboard* input_keyboard = GetKeyboard();

	std::set<int>& target_id_list = *ptr_target_id_list_;

	//c++ stl containter's end() function returns an iterator referring to the past-the-end element
	//so the target_iterator can never be container's end()

	//下ボタンを押したらカーソルを下に移動する
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		if (++target_iterator_ == target_id_list.end())
			target_iterator_ = target_id_list.begin();
	}
	//上ボタンを押したらカーソルを上に移動する
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		if (target_iterator_ == target_id_list.begin())
			target_iterator_ = --target_id_list.end();
		else
			--target_iterator_;
	}

	//確定ボタンが押された
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		//ターゲットが選択された
		game_scene_->ActorChooseTarget(*target_iterator_);

		game_scene_->actor_list_.erase(temp_actor_iterator_);

		//コマンド選択は終わった
		command_ui_state_ = CommandUI::COMMAND_ROOT;

		return true;
	}	
	//キャンセルボタンが押された
	else if (input_keyboard->GetKeyTrigger(DIK_K))
	{
		command_ui_state_ = command_ui_state_back_;

		game_scene_->actor_list_.erase(temp_actor_iterator_);
	}

	//コマンド選択はまだ終わってない
	return false;
}

void CommandUI::DrawRootMenu()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, ui_attack_texture_);

	DrawPolygonUI(UI_SELECTION_POS_X, UI_SELECTION_ONE_POS_Y,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT,
		0, 0,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT);

	pDevice->SetTexture(0, ui_skill_texture_);
	DrawPolygonUI(UI_SELECTION_POS_X, UI_SELECTION_TWO_POS_Y,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT,
		0, 0,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT);

	pDevice->SetTexture(0, ui_alchemy_texture_);
	DrawPolygonUI(UI_SELECTION_POS_X, UI_SELECTION_THREE_POS_Y,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT,
		0, 0,
		UI_SELECTION_WIDTH, UI_SELECTION_HEIGHT);

	pDevice->SetTexture(0, ui_sankake_tex_);

	DrawPolygonUI(UI_SELECTOR_POS_X, UI_SELECTOR_POS_Y + menu_root_selector_ * 50,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT,
		0, 0,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT);
}

void CommandUI::DrawSkillMenu()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, ui_selection_texture_);

	for (int n = 0; n < SKILL_MAX; n++)
	{
		DrawPolygonUI(UI_SELECTION_POS_X, UI_SELECTION_ONE_POS_Y + n * 50,
			UI_SKILL_SELECTION_WIDTH, UI_SKILL_SELECTION_HEIGHT,
			0, 0,
			UI_SKILL_SELECTION_WIDTH, UI_SKILL_SELECTION_HEIGHT);

		SKILL_ENUM id = static_cast<SKILL_ENUM> (n);

		const Skill& skill = GetSkill(id);
		const wchar_t* skill_name = skill.name_;

		int text_pos_x = static_cast<int>(UI_SELECTION_POS_X) + 5;
		int text_pos_y = static_cast<int>(UI_SELECTION_ONE_POS_Y) + n * 50;

		DrawCustomText(text_pos_x, text_pos_y,
			UI_SKILL_SELECTION_WIDTH - 5, UI_SKILL_SELECTION_HEIGHT,
			skill_name);

	}

	pDevice->SetTexture(0, ui_sankake_tex_);

	DrawPolygonUI(UI_SELECTOR_POS_X, UI_SELECTOR_POS_Y + menu_skill_selector_ * 50,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT,
		0, 0,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT);

}

void CommandUI::DrawAlchemyMenu()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, ui_selection_texture_);

	for (int n = 0; n < ALCHEMY_MAX; n++)
	{
		DrawPolygonUI(UI_SELECTION_POS_X, UI_SELECTION_ONE_POS_Y + n * 50,
			UI_SKILL_SELECTION_WIDTH, UI_SKILL_SELECTION_HEIGHT,
			0, 0,
			UI_SKILL_SELECTION_WIDTH, UI_SKILL_SELECTION_HEIGHT);

		ALCHEMY_ENUM id = static_cast<ALCHEMY_ENUM> (n);

		const Alchemy& alchemy = GetAlchemy(id);
		const wchar_t* alchemy_name = alchemy.name_;

		int text_pos_x = static_cast<int>(UI_SELECTION_POS_X) + 5;
		int text_pos_y = static_cast<int>(UI_SELECTION_ONE_POS_Y) + n * 50;

		DrawCustomText(text_pos_x, text_pos_y,
			UI_SKILL_SELECTION_WIDTH - 5, UI_SKILL_SELECTION_HEIGHT,
			alchemy_name);
	}

	pDevice->SetTexture(0, ui_sankake_tex_);

	DrawPolygonUI(UI_SELECTOR_POS_X, UI_SELECTOR_POS_Y + menu_skill_selector_ * 50,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT,
		0, 0,
		UI_SELECTOR_WIDTH, UI_SELECTOR_HEIGHT);
}

void CommandUI::DrawTargetSelection()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	std::vector<Character*>& character_list = game_scene_->GetCharacterList();

	int target_id = *target_iterator_;
	Character*& pTarget = character_list[target_id];

	pDevice->SetTexture(0, ui_target_selection_tex_);
	DrawSprite2D(pTarget->GetPos().x, pTarget->GetPos().y + 1.5f, 0.2f, 0.2f);

}

void CommandUI::AddActorListTempAvatar(int cool_down)
{
	std::list<Character*>& actor_list_ = game_scene_->GetActorList();
	int temp_actor_action_time;

	//行動リストに仮のアバターを追加する
	temp_actor_action_time = game_scene_->current_actor_->GetActionTimeAfterCoolDown(cool_down);
	temp_actor_iterator_ = ++(actor_list_.begin());
	while (temp_actor_iterator_ != actor_list_.end())
	{
		if (temp_actor_action_time < (*temp_actor_iterator_)->GetActionTime())
			break;

		++temp_actor_iterator_;
	}
	temp_actor_iterator_ = actor_list_.insert(temp_actor_iterator_, game_scene_->current_actor_);

}