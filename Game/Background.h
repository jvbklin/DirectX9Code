//=================================================================================
//
//    Background header
//    Author : Lin He                                        �쐬�� : 2018/11/21
//
//=================================================================================
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "../Base/DirectX9.h"

//*****************************************************************************
// Background Class
//
// �Q�[���V�[���̔w�i����������N���X
//*****************************************************************************
class Background
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

	//�w�i�e�N�X�`���[
	LPDIRECT3DTEXTURE9 texture_;
};

#endif // !BACKGROUND_H_