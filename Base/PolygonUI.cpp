//=================================================================================
//
//    PolygonUI header
//    Author : Lin He                                        �쐬�� : 2018/11/16
//
//=================================================================================

#include "DirectX9.h"

#include "PolygonUI.h"

//*****************************************************************************
// Macro Definition
//*****************************************************************************

// ���_����(1�ځF���W�A2�ځF�J���[,3�ځF�e�N�X�`���[)
#define FVF_VERTEX_UI	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// Struct Declaration
//*****************************************************************************

typedef struct
{
	D3DXVECTOR4 pos;		// ���W
	D3DCOLOR    color;		// �J���[
	D3DXVECTOR2 texcoord;
}VERTEX_UI;

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferUI;

//=====================================================================
// [ UI�|���S���������֐� ]
//=====================================================================
bool InitPolygonUI()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	// VRAM�̃��������m��(GPU�Ɉ˗�)(���_�o�b�t�@�̍쐬)
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_UI) * 4,	// �؂肽��baf�̗�(�o�C�g)�A�܂�1���_�̗e�ʁ~�K�v���_��
		D3DUSAGE_WRITEONLY,									// �g�p�p�r(����͏������݂̂݁AGPU�������������������񂾃f�[�^��ǂ�ł̓_��(�l���s��))
		FVF_VERTEX_UI,										// ���_����
		D3DPOOL_MANAGED,									// ���_�o�b�t�@�̊Ǘ����@( MANAGED�͊Ǘ���Direct3D�ɂ��C���Ƃ����Ӗ� )
		&g_pVertexBufferUI,									// �Ǘ��҂̋��ꏊ�̃�����(�|�C���^�̃|�C���^)(�S�Ă͂���̒l��m�邽�߂̍��)
		NULL);												// NULL�ł���

	if (FAILED(hr))
	{
		MessageBox(NULL, L"���_�o�b�t�@�����Ȃ�����", L"error", MB_OK);
		return false;
	}


	return true;
}


//=====================================================================
// [ UI�|���S���I�����֐� ]
//=====================================================================
void UninitPolygonUI()
{
	SAFE_RELEASE(g_pVertexBufferUI);
}

//=====================================================================
// [ UI�|���S���`��֐� ]
//=====================================================================
void DrawPolygonUI(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	VERTEX_UI* pV;
	/*�� 0�ł����v�A�O������ƑS�����b�N���܂�*/
	g_pVertexBufferUI->Lock(0, sizeof(VERTEX_UI) * 4, (void**)&pV, D3DLOCK_DISCARD);

	pV[0].pos = D3DXVECTOR4(x - 0.5f					, y - 0.5f					   , -1.0f, 1.0f);
	pV[1].pos = D3DXVECTOR4(x + texture_cut_width - 0.5f, y - 0.5f					   , -1.0f, 1.0f);
	pV[2].pos = D3DXVECTOR4(x - 0.5f					, y + texture_cut_height - 0.5f, -1.0f, 1.0f);
	pV[3].pos = D3DXVECTOR4(x + texture_cut_width - 0.5f, y + texture_cut_height - 0.5f, -1.0f, 1.0f);

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

	g_pVertexBufferUI->Unlock();


	pDevice->SetStreamSource(0,						// �p�C�v���C���ԍ�
							 g_pVertexBufferUI,		// �o�[�e�b�N�X�o�b�t�@�ϐ���
							 0,						// �ǂ����痬�����ނ�(offset)
							 sizeof(VERTEX_UI));	// �X�g���C�h�l(�ׂ̒��_�܂ł̒�����1���_�̑傫��)

	//FVF(������g�p���钸�_���)�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_UI);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}