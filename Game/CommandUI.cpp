//=================================================================================
//
//    Command UI cpp
//    Author : Lin He                                        �쐬�� : 2018/11/22
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
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_attack.png", &ui_attack_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_skill.png", &ui_skill_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_alchemy.png", &ui_alchemy_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/ui_skill_selection.png", &ui_selection_texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/sankake.png", &ui_sankake_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/target_selection.png", &ui_target_selection_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
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

	//���{�^������������J�[�\�������Ɉړ�����
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_root_selector_;
		if (menu_root_selector_ > 2)
			menu_root_selector_ = 2;
	}
	//��{�^������������J�[�\������Ɉړ�����
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_root_selector_;
		if (menu_root_selector_ < 0)
			menu_root_selector_ = 0;
	}

	//�m��{�^���������ꂽ
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		switch (menu_root_selector_)
		{
		case 0:
			//�u�U���v�A�N�V�������I�����ꂽ
			game_scene_->ActorUseAttack(0);

			//�s�����X�g�Ɉꎞ�I�ȃA�o�^�[��ǉ�����
			AddActorListTempAvatar(60);

			//�^�[�Q�b�g�I�����X�g��G���X�g�ɐݒ肷��
			ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

			//�^�[�Q�b�g�I���J�[�\����ݒ肷��
			target_iterator_ = (*ptr_target_id_list_).begin();

			command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;

			break;
		case 1:
			//�u�X�L���v�A�N�V�������I�����ꂽ
			menu_skill_selector_ = 0;

			command_ui_state_		= 
			command_ui_state_back_	= CommandUI::COMMAND_SKILL;
			break;
		case 2:
			//�u�B���p�v�A�N�V�������I�����ꂽ
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

	//���{�^������������J�[�\�������Ɉړ�����
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_skill_selector_;
		if (menu_skill_selector_ >= SKILL_MAX)
			menu_skill_selector_ = SKILL_MAX - 1;
	}
	//��{�^������������J�[�\������Ɉړ�����
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_skill_selector_;
		if (menu_skill_selector_ < 0)
			menu_skill_selector_ = 0;
	}

	//�m��{�^���������ꂽ
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		SKILL_ENUM id = static_cast<SKILL_ENUM>(menu_skill_selector_);
		const Skill& selected_skill = GetSkill(id);

		const int sp_cost = selected_skill.sp_cost_;

		// �u�X�L���v�𔭓����邽�߂�SP������Ȃ�
		if (game_scene_->current_actor_->GetSp() < sp_cost)
		{
			//nothing happen
			return;

			//�R�}���h�I���͂܂��I����ĂȂ�
		}

		//�u�X�L���v���I�����ꂽ
		game_scene_->ActorUseSkill(id);

		//�s�����X�g�Ɉꎞ�I�ȃA�o�^�[��ǉ�����
		AddActorListTempAvatar(selected_skill.cool_down_);

		//�^�[�Q�b�g�I�����X�g��G���X�g�ɐݒ肷��
		ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

		//�^�[�Q�b�g�I���J�[�\����ݒ肷��
		target_iterator_ = (*ptr_target_id_list_).begin();

		command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;
	}
	//�L�����Z���{�^���������ꂽ
	else if (input_keyboard->GetKeyTrigger(DIK_K))
	{
		command_ui_state_ = CommandUI::COMMAND_ROOT;
	}

	//�R�}���h�I���͂܂��I����ĂȂ�

}

void CommandUI::UpdateAlchemyMenu()
{
	CInputKeyboard* input_keyboard = GetKeyboard();

	//���{�^������������J�[�\�������Ɉړ�����
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		++menu_skill_selector_;
		if (menu_skill_selector_ >= ALCHEMY_MAX)
			menu_skill_selector_ = ALCHEMY_MAX - 1;
	}
	//��{�^������������J�[�\������Ɉړ�����
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		--menu_skill_selector_;
		if (menu_skill_selector_ < 0)
			menu_skill_selector_ = 0;
	}

	//�m��{�^���������ꂽ
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		ALCHEMY_ENUM id = static_cast<ALCHEMY_ENUM>(menu_skill_selector_);
		const Alchemy& selected_alchemy = GetAlchemy(id);

		const int element_cost = selected_alchemy.element_cost_;

		//�u�B���p�v�𔭓����邽�߂̃G�������g������Ȃ�
		if (game_scene_->battle_element_.GetElementValue(selected_alchemy.element_type_) < element_cost)
		{
			//nothing happen
			return;

			//�R�}���h�I���͂܂��I����ĂȂ�
		}

		//�u�B���p�v���I�����ꂽ
		game_scene_->ActorUseAlchemy(id);

		//�s�����X�g�Ɉꎞ�I�ȃA�o�^�[��ǉ�����
		AddActorListTempAvatar(selected_alchemy.cool_down_);

		//�s���̃^�[�Q�b�g�^�C�v�ɉ����ă^�[�Q�b�g�I������
		if (selected_alchemy.target_type_ == TARGET_ALLY_SINGLE)
		{
			//�^�[�Q�b�g�I�����X�g��G���X�g�ɐݒ肷��
			ptr_target_id_list_ = &(game_scene_->GetPlayerIdList());

			//�^�[�Q�b�g�I���J�[�\����ݒ肷��
			target_iterator_ = (*ptr_target_id_list_).begin();
		}
		else
		{
			//�^�[�Q�b�g�I�����X�g��G���X�g�ɐݒ肷��
			ptr_target_id_list_ = &(game_scene_->GetEnemyIdList());

			//�^�[�Q�b�g�I���J�[�\����ݒ肷��
			target_iterator_ = (*ptr_target_id_list_).begin();
		}

		command_ui_state_ = CommandUI::COMMAND_CHOOSE_TARGET;

		//�R�}���h�I���͂܂��I����ĂȂ�
		return;
	}
	//�L�����Z���{�^���������ꂽ
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

	//���{�^������������J�[�\�������Ɉړ�����
	if (input_keyboard->GetKeyTrigger(DIK_S))
	{
		if (++target_iterator_ == target_id_list.end())
			target_iterator_ = target_id_list.begin();
	}
	//��{�^������������J�[�\������Ɉړ�����
	else if (input_keyboard->GetKeyTrigger(DIK_W))
	{
		if (target_iterator_ == target_id_list.begin())
			target_iterator_ = --target_id_list.end();
		else
			--target_iterator_;
	}

	//�m��{�^���������ꂽ
	if (input_keyboard->GetKeyTrigger(DIK_J))
	{
		//�^�[�Q�b�g���I�����ꂽ
		game_scene_->ActorChooseTarget(*target_iterator_);

		game_scene_->actor_list_.erase(temp_actor_iterator_);

		//�R�}���h�I���͏I�����
		command_ui_state_ = CommandUI::COMMAND_ROOT;

		return true;
	}	
	//�L�����Z���{�^���������ꂽ
	else if (input_keyboard->GetKeyTrigger(DIK_K))
	{
		command_ui_state_ = command_ui_state_back_;

		game_scene_->actor_list_.erase(temp_actor_iterator_);
	}

	//�R�}���h�I���͂܂��I����ĂȂ�
	return false;
}

void CommandUI::DrawRootMenu()
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
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

	//�s�����X�g�ɉ��̃A�o�^�[��ǉ�����
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