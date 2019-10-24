//=================================================================================
//
//    Background header
//    Author : Lin He                                        作成日 : 2018/11/21
//
//=================================================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// Background Class
//
// ゲームシーンの背景を処理するクラス
//*****************************************************************************
class Background
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

	//背景テクスチャー
	LPDIRECT3DTEXTURE9 texture_;
};

#endif // !BACKGROUND_H_