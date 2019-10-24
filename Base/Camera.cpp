//=================================================================================
//
//    Camera cpp
//    Author : Lin He                                        �쐬�� : 2018/11/16
//
//=================================================================================

#include "Camera.h"

#include "../main.h"

//*****************************************************************************
// Const Declaration
//*****************************************************************************

const float NEAR_CLIPPING_PLANE = 0.1f;
const float FAR_CLIPPING_PLANE = 1000.0f;

//=====================================================================
// [ Camera�������֐� ]
//=====================================================================
void Camera::Init()
{
	// D3DDevice�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextX�f�o�C�X�擾���s����", L"error", MB_OK);
		return;
	}

	// �J�������W
	D3DXVECTOR3 eye(0.0f, 0.0f, -10.0f);

	// ����ꏊ( �����_ )
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);

	// �J�����̏����
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	// �r���[�ϊ��s��( LH�͍�����W�n�̈Ӗ� )
	D3DXMatrixLookAtLH(&mtxView_, &eye, &at, &up);

	// �v���W�F�N�V�����s��̍쐬
	// ����p�͉�p�̔���
	// �A�X�y�N�g��
	// ��������̒��ɃJ���������Ȃ����j�A�N���b�v > 0.0f

	//�������e�ɂ���
	D3DXMatrixPerspectiveFovLH(&mtxProjection_, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	//D3DXMatrixOrthoLH(&mtxProjection, (float)SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.025f, 0.1f, 1000.0f);

	//// �e��s��̐ݒ�( ���̏��Ԃ͊֌W�Ȃ� )
	//// �f�o�C�X�����Z�b�g����Ȃ�����A���̒l���f�o�C�X�ɕێ������
	pDevice->SetTransform(D3DTS_VIEW, &mtxView_);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection_);
}