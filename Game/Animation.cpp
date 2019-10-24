//=================================================================================
//
//    Animation cpp
//    Author : Lin He                                        作成日 : 2018/01/14
//
//=================================================================================

#include "Animation.h"

#include "../Base/DirectX9.h"
#include "../Base/Polygon2D.h"

//=================================================================
// [ アニメーション初期化関数 ]
//=================================================================
void Animation::Init()
{
	texture_ = NULL;
	pos_x_ = 0.0f;
	pos_y_ = 0.0f;

	state_ = ANIM_STATE_NULL;
}

//=================================================================
// [ アニメーションプレイ初期化関数 ]
//=================================================================
void Animation::InitPlay(LPDIRECT3DTEXTURE9 texture, int anim_index_max, float pos_x, float pos_y)
{
	texture_ = texture;
	pos_x_ = pos_x;
	pos_y_ = pos_y;

	count_ = 0;
	//Which measn all attack animation updates in every 7 frames
	count_max_ = 7;

	anim_index_ = 0;
	anim_index_max_ = anim_index_max;

	uv_coord_delta_x_ = 1.0f / anim_index_max_;

	state_ = ANIM_STATE_PLAY;
}

//=================================================================
// [ アニメーションプレイ関数 ]
//=================================================================
void Animation::Play()
{
	++count_;
	if (count_ >= count_max_)
	{
		count_ = 0;

		++anim_index_;
		if (anim_index_ >= anim_index_max_)
		{
			state_ = ANIM_STATE_STOP;
		}
	}
}

//=================================================================
// [ アニメーション描画関数 ]
//=================================================================
void Animation::Draw()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawSprite2D(pos_x_, pos_y_, 1.5f, 1.5f, anim_index_ * uv_coord_delta_x_, (anim_index_ + 1) * uv_coord_delta_x_,
											 0.0f							, 1.0f);
}

//=================================================================
// [ アニメーションステート取得関数 ]
//=================================================================
Animation::ANIM_STATE Animation::GetState()
{
	return state_;
}

//=================================================================
// [ AnimationManager初期化関数 ]
//=================================================================
void AnimationManager::Init()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}
	HRESULT hr;

	//-----------------------------------------------------------------------------
	//攻撃アニメーションのテクスチャーの読み込み
	//-----------------------------------------------------------------------------
	for (int n = 0; n < ANIM_MAX; n++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, anim_texture_data[n].file_path, &(anim_textures[n]) );
		if (FAILED(hr))
		{
			MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
			return;
		}
	}

	//-----------------------------------------------------------------------------
	//処理するアニメーションを初期化する
	//-----------------------------------------------------------------------------
	anim_.Init();
}

//=================================================================
// [ AnimationManager終了化関数 ]
//=================================================================
void AnimationManager::Uninit()
{
	for (int n = 0; n < ANIM_MAX; n++)
	{
		SAFE_RELEASE(anim_textures[n]);
	}
}

//=================================================================
// [ 特定のアニメーションをプレイする関数 ]
//=================================================================
bool AnimationManager::PlayAnimation(int id, float pos_x, float pos_y)
{
	switch (anim_.GetState())
	{
	case Animation::ANIM_STATE_NULL:
	{
		int anim_index_max = anim_texture_data[id].col;
		anim_.InitPlay(anim_textures[id], anim_index_max, pos_x, pos_y);
		return false;
	}
	case Animation::ANIM_STATE_PLAY:
	{
		anim_.Play();
		return false;
	}
	case Animation::ANIM_STATE_STOP:
	{
		anim_.Init();
		return true;
	}
	}
	return false;
}

//=================================================================
// [ AnimationManager描画関数 ]
//=================================================================
void AnimationManager::Draw()
{
	if (anim_.GetState() == Animation::ANIM_STATE_PLAY)
	{
		anim_.Draw();
	}
}