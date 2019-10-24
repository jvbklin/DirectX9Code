//=================================================================================
//
//    Background cpp
//    Author : Lin He                                        �쐬�� : 2018/11/21
//
//=================================================================================

#include "Background.h"

#include "../Base/Polygon2D.h"

#include "../Base/DirectX9.h"

//=====================================================================
// [ �w�i�������֐� ]
//=====================================================================
void Background::Init()
{

	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	//EnemyStraight Texture
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/background.png", &texture_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�e�N�X�`���[���ǂݍ��݂Ȃ�����", L"error", MB_OK);
		return;
	}
}

//=====================================================================
// [ �w�i�I�����֐� ]
//=====================================================================
void Background::Uninit()
{
	SAFE_RELEASE(texture_);
}

//=====================================================================
// [ �w�i�X�V�֐� ]
//=====================================================================
void Background::Update()
{

}

//=====================================================================
// [ �w�i�`��֐� ]
//=====================================================================
void Background::Draw()
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, texture_);

	DrawPolygon2D(0.0f, 0.0f, 16.0f, 9.0f, 700, 490, 0, 0, 700, 490);
}