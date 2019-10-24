//=================================================================================
//
//    TextureManager header
//    Author : Lin He                                        作成日 : 2019/01/10
//
//	  現在TextureManagerはPlayerとEnemyのテクスチャーだけに使う
//=================================================================================
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// Struct Definition
//*****************************************************************************
typedef struct
{
	wchar_t file_path[256];
	int width;
	int height;
}Texture;

typedef struct
{
	wchar_t file_path[256];
	int width;
	int height;
	int row;
	int col;
}SpriteSheet;

//-----------------------------------------------------------------------------
//Playerのテクスチャー
//-----------------------------------------------------------------------------
enum PLAYER_TEX_ENUM
{
	PLAYER_TEX_NULL = -1,
	PLAYER_TEX_ONE = 0,
	PLAYER_TEX_MAX,
};

static const Texture player_texture_data[PLAYER_TEX_MAX] = {
	 L"Resource/Texture/player.png", 74, 59,
};

static const Texture player_avatar_texture_data[PLAYER_TEX_MAX] = {
	 L"Resource/Texture/avatar_player.png", 64, 64,
};
//-----------------------------------------------------------------------------
//Enemyのテクスチャー
//-----------------------------------------------------------------------------
enum ENEMY_TEX_ENUM
{
	ENEMY_TEX_NULL = -1,
	ENEMY_TEX_GREEN_BIRD = 0,
	ENEMY_TEX_BAT_BIRD,
	ENEMY_TEX_BROWN_BIRD,
	ENEMY_TEX_MAX,
};

static const Texture enemy_texture_data[ENEMY_TEX_MAX] = {
	L"Resource/Texture/green_bird.png", 256, 128,
	L"Resource/Texture/bat_bird.png", 256, 128,
	L"Resource/Texture/brown_bird.png", 256, 128,
};

static const Texture enemy_avatar_texture_data[ENEMY_TEX_MAX] = {
	L"Resource/Texture/avatar_green_bird.png", 64, 64,
	L"Resource/Texture/avatar_bat_bird.png", 64, 64,
	L"Resource/Texture/avatar_brown_bird.png", 64, 64,
};
//-----------------------------------------------------------------------------

class TextureManager
{
public:
	static void LoadAllTexture();
	static void ReleaseAllTexture();

	//今後Resource Managerを作る予定、現状staticのテクスチャーを使う
	static LPDIRECT3DTEXTURE9 player_textures[PLAYER_TEX_MAX];
	static LPDIRECT3DTEXTURE9 enemy_textures[ENEMY_TEX_MAX];

	static LPDIRECT3DTEXTURE9 player_avatar_textures[PLAYER_TEX_MAX];
	static LPDIRECT3DTEXTURE9 enemy_avatar_textures[ENEMY_TEX_MAX];
};

#endif