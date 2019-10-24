//=================================================================================
//
//    TextureManager cpp
//    Author : Lin He                                        �쐬�� : 2019/01/10
//
//=================================================================================

#include "TextureManager.h"

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************

//����Resource Manager�����\��Ȃ񂾂��A�����static�̃e�N�X�`���[���g��
LPDIRECT3DTEXTURE9 TextureManager::player_textures[PLAYER_TEX_MAX];
LPDIRECT3DTEXTURE9 TextureManager::enemy_textures[ENEMY_TEX_MAX];

LPDIRECT3DTEXTURE9 TextureManager::player_avatar_textures[PLAYER_TEX_MAX];
LPDIRECT3DTEXTURE9 TextureManager::enemy_avatar_textures[ENEMY_TEX_MAX];

void TextureManager::LoadAllTexture()
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
	//Player�̃e�N�X�`���[
	//-----------------------------------------------------------------------------
	for (int n = 0; n < PLAYER_TEX_MAX; n++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, player_texture_data[n].file_path, &(player_textures[n]));
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
			return;
		}

		hr = D3DXCreateTextureFromFile(pDevice, player_avatar_texture_data[n].file_path, &(player_avatar_textures[n]));
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
			return;
		}
	}

	//-----------------------------------------------------------------------------
	//Enemy�̃e�N�X�`���[
	//-----------------------------------------------------------------------------
	for (int n = 0; n < ENEMY_TEX_MAX; n++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, enemy_texture_data[n].file_path, &(enemy_textures[n]));
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
			return;
		}

		hr = D3DXCreateTextureFromFile(pDevice, enemy_avatar_texture_data[n].file_path, &(enemy_avatar_textures[n]));
		if (FAILED(hr))
		{
			MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
			return;
		}
	}
}

void TextureManager::ReleaseAllTexture()
{
	for (int n = 0; n < PLAYER_TEX_MAX; n++)
	{
		SAFE_RELEASE(player_textures[n]);
	}

	for (int n = 0; n < ENEMY_TEX_MAX; n++)
	{
		SAFE_RELEASE(enemy_textures[n]);
	}
}