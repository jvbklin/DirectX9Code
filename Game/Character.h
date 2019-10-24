//=================================================================================
//
//    Character header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/12/18
//
//=================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "../Base/DirectX9.h"

class Character {
	public:
		enum Type
		{
			PLAYER = 0,
			ENEMY = 1
		};

	public:
		Character();

		int GetId();
		int GetHp();
		int GetSp();
		int GetHpMax();
		int GetSpMax();
		int GetAtk();
		int GetSpd();
		int GetCoolDownTime(int action_cool_down) const;
		int GetActionTimeAfterCoolDown(int action_cool_down) const;
		int GetActionTime() const;

		Vector2 GetPos();
		Vector2 GetPosOld();

		Type GetType();

		LPDIRECT3DTEXTURE9 GetAvatarTexture();

		bool IsEnabled();
		bool IsDead();

		void GetDamage(int value);
		void IncreaseHp(int value);
		void IncreaseSp(int value);
		void IncreaseActionTime(int value);

		void UpdateActionCoolDown(int action_cool_down);

		void MoveToPos(Vector2 pos);

		virtual void Init(float pos_x, float pos_y, int data_id) = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void Die() = 0;

		virtual Vector2 GetContactPos() = 0;

	protected:

		Vector2 pos_;
		Vector2 pos_old_;

		Type type_;

		bool is_enabled_;
		bool is_dead_;

		int hp_;
		int hp_max_;
		int sp_;
		int sp_max_;
		int atk_;
		int spd_;

		int action_time_;

		LPDIRECT3DTEXTURE9 texture_;
		LPDIRECT3DTEXTURE9 avatar_texture_;

	private:

		int id_;
		static unsigned int id_counter_;
};
#endif