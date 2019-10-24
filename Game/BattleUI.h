//=================================================================================
//
//    Battle UI header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/11/17
//
//=================================================================================

#ifndef _BATTLE_UI_H_
#define _BATTLE_UI_H_

#include <list>

#include "../Base/DirectX9.h"

class Character;

class BattleUI
{
public:
	void Init();
	void Uninit();

	//void Update();
	//void Draw();

	void DrawHp(float x, float y, int hp_current, int hp_max);
	void DrawSp(float x, float y, int sp_current, int sp_max);

	void DrawEnemyHp(float x, float y, int hp_current, int hp_max);

	void DrawElement(int num_earth, int num_fire, int num_wind, int num_water);

	void DrawActorList(std::list<Character*> actor_list);

private:

	LPDIRECT3DTEXTURE9 bar_null_texture_;
	LPDIRECT3DTEXTURE9 bar_hp_texture_;
	LPDIRECT3DTEXTURE9 bar_sp_texture_;

	LPDIRECT3DTEXTURE9 element_null_tex_;
	LPDIRECT3DTEXTURE9 element_earth_tex_;
	LPDIRECT3DTEXTURE9 element_fire_tex_;
	LPDIRECT3DTEXTURE9 element_wind_tex_;
	LPDIRECT3DTEXTURE9 element_water_tex_;

	LPDIRECT3DTEXTURE9 temp_actor_avatar_tex_;
};

#endif