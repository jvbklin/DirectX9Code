//=================================================================================
//
//    Animation cpp
//    Author : Lin He                                        �쐬�� : 2018/01/14
//
//=================================================================================

#include "Animation.h"

#include "../Base/DirectX9.h"
#include "../Base/Polygon2D.h"

//=================================================================
// [ �A�j���[�V�����������֐� ]
//=================================================================
void Animation::Init()
{
	texture_ = NULL;
	pos_x_ = 0.0f;
	pos_y_ = 0.0f;

	state_ = ANIM_STATE_NULL;
}

//=================================================================
// [ �A�j���[�V�����v���C�������֐� ]
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
// [ �A�j���[�V�����v���C�֐� ]
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
// [ �A�j���[�V�����`��֐� ]
//=================================================================
void Animation::Draw()
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawSprite2D(pos_x_, pos_y_, 1.5f, 1.5f, anim_index_ * uv_coord_delta_x_, (anim_index_ + 1) * uv_coord_delta_x_,
											 0.0f							, 1.0f);
}

//=================================================================
// [ �A�j���[�V�����X�e�[�g�擾�֐� ]
//=================================================================
Animation::ANIM_STATE Animation::GetState()
{
	return state_;
}

//=================================================================
// [ AnimationManager�������֐� ]
//=================================================================
void AnimationManager::Init()
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}
	HRESULT hr;

	//-----------------------------------------------------------------------------
	//�U���A�j���[�V�����̃e�N�X�`���[�̓ǂݍ���
	//-----------------------------------------------------------------------------
	for (int n = 0; n < ANIM_MAX; n++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, anim_texture_data[n].file_path, &(anim_textures[n]) );
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
			return;
		}
	}

	//-----------------------------------------------------------------------------
	//��������A�j���[�V����������������
	//-----------------------------------------------------------------------------
	anim_.Init();
}

//=================================================================
// [ AnimationManager�I�����֐� ]
//=================================================================
void AnimationManager::Uninit()
{
	for (int n = 0; n < ANIM_MAX; n++)
	{
		SAFE_RELEASE(anim_textures[n]);
	}
}

//=================================================================
// [ ����̃A�j���[�V�������v���C����֐� ]
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
// [ AnimationManager�`��֐� ]
//=================================================================
void AnimationManager::Draw()
{
	if (anim_.GetState() == Animation::ANIM_STATE_PLAY)
	{
		anim_.Draw();
	}
}