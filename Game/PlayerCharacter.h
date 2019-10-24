//=================================================================================
//
//    PlayerCharacter header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/11/15
//
//=================================================================================
#ifndef _PLAYER_CHARACTER_H_
#define _PLAYER_CHARACTER_H_

#include "../Base/DirectX9.h"
#include "../Game/Character.h"

typedef enum PLAYER_ENUM
{
	PLAYER_ONE = 0,
	PLAYER_MAX,
}PLAYER_ENUM;

class PlayerCharacter : public Character
{
public:
	void Init(float pos_x, float pos_y, int data_id);
	void Uninit();
	void Update();
	void Draw();
	void Die();

	Vector2 GetContactPos();
};

#endif // !PLAYER_CHARACTER_H_