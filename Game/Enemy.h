//=================================================================================
//
//    Enemy header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/11/21
//
//=================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../Base/DirectX9.h"

#include "../Game/Character.h"

#include "../Game/TextureManager.h"

typedef enum ENEMY_ENUM
{
	ENEMY_NULL = -1,
	ENEMY_GREEN_BIRD = 0,
	ENEMY_BAT_BIRD = 1,
	ENEMY_BROWN_BIRD = 2,
	ENEMY_MAX = 3,
}ENEMY_ENUM;

struct EnemyData
{
	int hp;
	int atk;
	int spd;
	int texture_enum;
};

static const EnemyData EnemyDataList[ENEMY_MAX] = {
	30,2,30,ENEMY_TEX_GREEN_BIRD,
	60,4,20,ENEMY_TEX_BAT_BIRD,
	90,6,10,ENEMY_TEX_BROWN_BIRD,
};

class Enemy : public Character
{
public:
	void Init(float pos_x, float pos_y, int data_id);

	void Uninit();
	void Update();
	void Draw();
	void Die();

	Vector2 GetContactPos();

private:

	int animation_count_;
	int animation_count_max_;
	int animation_index_;
};

#endif // !ENEMY_H_