//=================================================================================
//
//    Command UI header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/11/22
//
//=================================================================================

#ifndef _COMMAND_UI_H_
#define _COMMAND_UI_H_

#include <set>

#include "../Base/DirectX9.h"

#include "GameScene.h"


class GameScene;

class CommandUI
{
public:

	enum COMMAND_UI_STATE
	{
		COMMAND_ROOT,
		COMMAND_SKILL,
		COMMAND_ALCHEMY,
		COMMAND_CHOOSE_TARGET
	};


	void Init(GameScene* scene);
	void Uninit();

	bool Update();
	void Draw();

	void UpdateRootMenu();
	void UpdateSkillMenu();
	void UpdateAlchemyMenu();
	bool UpdateTargetSelection();

	void AddActorListTempAvatar(int cool_down);

	void DrawRootMenu();
	void DrawSkillMenu();
	void DrawAlchemyMenu();
	void DrawTargetSelection();

private:

	GameScene* game_scene_;

	COMMAND_UI_STATE command_ui_state_;
	COMMAND_UI_STATE command_ui_state_back_;

	int menu_root_selector_;
	int menu_skill_selector_;

	std::set<int>::iterator target_iterator_;
	std::set<int>* ptr_target_id_list_;
	std::list<Character*>::iterator temp_actor_iterator_;

	LPDIRECT3DTEXTURE9 ui_attack_texture_;
	LPDIRECT3DTEXTURE9 ui_skill_texture_;
	LPDIRECT3DTEXTURE9 ui_alchemy_texture_;
	LPDIRECT3DTEXTURE9 ui_selection_texture_;

	LPDIRECT3DTEXTURE9 ui_sankake_tex_;
	LPDIRECT3DTEXTURE9 ui_target_selection_tex_;
};

#endif