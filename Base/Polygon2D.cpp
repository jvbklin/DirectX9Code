//=================================================================================
//
//    Polygon2D cpp
//    Author : Lin He                                        �쐬�� : 2018/11/16
//
//=================================================================================

#include "DirectX9.h"

#include "Polygon2D.h"

//*****************************************************************************
// Macro Definition
//*****************************************************************************

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)
#define FVF_VERTEX_2D	( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// Struct Declaration
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;		// ���W
	D3DCOLOR    color;		// �J���[
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;

//=====================================================================
// [ 2D�p�|���S���������֐� ]
//=====================================================================
bool InitPolygon2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
		D3DUSAGE_WRITEONLY,									// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
		FVF_VERTEX_2D,										// ���_����
		D3DPOOL_MANAGED,									// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
		&g_pVertexBuffer,									// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
		NULL);												// NULL�ł���

	if (FAILED(hr))
	{
		MessageBox(NULL, L"���_�o�b�t�@�����Ȃ�����", L"error", MB_OK);
		return false;
	}


	return true;
}

//=====================================================================
// [ 2D�p�|���S���I�����֐� ]
//=====================================================================
void UninitPolygon2D()
{
	SAFE_RELEASE(g_pVertexBuffer);
}

//=====================================================================
// [ 2D�p�|���S���`��֐� ]
//=====================================================================
void DrawPolygon2D(float x, float y, float plygon_width_half, float polygon_height_half,
									 int texture_width		, int texture_height,
									 int texture_cut_x		, int texture_cut_y,
									 int texture_cut_width	, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVF�̐ݒ�( �f�o�C�X�̕��ɒ��_�̑����������� )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
		g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

		pV[0].pos = D3DXVECTOR3(-plygon_width_half, polygon_height_half, 0.0f);
		pV[1].pos = D3DXVECTOR3(plygon_width_half, polygon_height_half, 0.0f);
		pV[2].pos = D3DXVECTOR3(-plygon_width_half, -polygon_height_half, 0.0f);
		pV[3].pos = D3DXVECTOR3(plygon_width_half, -polygon_height_half, 0.0f);

		pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = 0xFFFFFFFF;

		float u0 = (float)texture_cut_x / texture_width;
		float v0 = (float)texture_cut_y / texture_height;
		float u1 = (float)(texture_cut_x + texture_cut_width) / texture_width;
		float v1 = (float)(texture_cut_y + texture_cut_height) / texture_height;

		pV[0].texcoord = D3DXVECTOR2(u0, v0);
		pV[1].texcoord = D3DXVECTOR2(u1, v0);
		pV[2].texcoord = D3DXVECTOR2(u0, v1);
		pV[3].texcoord = D3DXVECTOR2(u1, v1);

		g_pVertexBuffer->Unlock();
	}

	pDevice->SetStreamSource(0,						// �p�C�v���C���ԍ�
							 g_pVertexBuffer,		// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,						// �ǂ����痬�����ނ�(offset)
							 sizeof(VERTEX_2D));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=====================================================================
// [ 2D�X�v���C�g�`��֐� ]
//=====================================================================
void DrawSprite2D(float x, float y, float plygon_width_half, float polygon_height_half,
									float uv_left		   , float uv_right,
									float uv_up			   , float uv_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVF�̐ݒ�( �f�o�C�X�̕��ɒ��_�̑����������� )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
		g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

		pV[0].pos = D3DXVECTOR3(-plygon_width_half,  polygon_height_half, 0.0f);
		pV[1].pos = D3DXVECTOR3( plygon_width_half,  polygon_height_half, 0.0f);
		pV[2].pos = D3DXVECTOR3(-plygon_width_half, -polygon_height_half, 0.0f);
		pV[3].pos = D3DXVECTOR3( plygon_width_half, -polygon_height_half, 0.0f);

		pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = 0xFFFFFFFF;

		pV[0].texcoord = D3DXVECTOR2(uv_left, uv_up);
		pV[1].texcoord = D3DXVECTOR2(uv_right, uv_up);
		pV[2].texcoord = D3DXVECTOR2(uv_left, uv_down);
		pV[3].texcoord = D3DXVECTOR2(uv_right, uv_down);

		g_pVertexBuffer->Unlock();
	}

	pDevice->SetStreamSource(0,						// �p�C�v���C���ԍ�
							 g_pVertexBuffer,		// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,						// �ǂ����痬�����ނ�(offset)
							 sizeof(VERTEX_2D));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


//=====================================================================
// [ �l�p�`�|���S���`��֐� ]
//=====================================================================
void DrawRect2D(float x, float y, float plygon_width, float polygon_height,
								  float uv_left,	  float uv_right,
								  float uv_up,		  float uv_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVF�̐ݒ�( �f�o�C�X�̕��ɒ��_�̑����������� )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
		g_pVertexBuffer->Lock(0, sizeof(VERTEX_2D) * 4, (void**)&pV, D3DLOCK_DISCARD);

		pV[0].pos = D3DXVECTOR3(0.0f,		   0.0f,		   0.0f);
		pV[1].pos = D3DXVECTOR3(plygon_width,  0.0f,		   0.0f);
		pV[2].pos = D3DXVECTOR3(0.0f,		  -polygon_height, 0.0f);
		pV[3].pos = D3DXVECTOR3(plygon_width, -polygon_height, 0.0f);

		pV[0].color =
		pV[1].color =
		pV[2].color =
		pV[3].color = 0xFFFFFFFF;

		pV[0].texcoord = D3DXVECTOR2(uv_left, uv_up);
		pV[1].texcoord = D3DXVECTOR2(uv_right, uv_up);
		pV[2].texcoord = D3DXVECTOR2(uv_left, uv_down);
		pV[3].texcoord = D3DXVECTOR2(uv_right, uv_down);

		g_pVertexBuffer->Unlock();
	}

	pDevice->SetStreamSource(0,						// �p�C�v���C���ԍ�
							 g_pVertexBuffer,		// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,						// �ǂ����痬�����ނ�(offset)
							 sizeof(VERTEX_2D));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}