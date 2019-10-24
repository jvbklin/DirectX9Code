//=================================================================================
//
//    Camera cpp
//    Author : Lin He                                        作成日 : 2018/11/16
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
// [ Camera初期化関数 ]
//=====================================================================
void Camera::Init()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	// カメラ座標
	D3DXVECTOR3 eye(0.0f, 0.0f, -10.0f);

	// 見る場所( 注視点 )
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);

	// カメラの上方向
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	// ビュー変換行列( LHは左手座標系の意味 )
	D3DXMatrixLookAtLH(&mtxView_, &eye, &at, &up);

	// プロジェクション行列の作成
	// 視野角は画角の半分
	// アスペクト比
	// しすい台の中にカメラを入れない＝ニアクリップ > 0.0f

	//透視投影にする
	D3DXMatrixPerspectiveFovLH(&mtxProjection_, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	//D3DXMatrixOrthoLH(&mtxProjection, (float)SCREEN_WIDTH * 0.025f, SCREEN_HEIGHT * 0.025f, 0.1f, 1000.0f);

	//// 各種行列の設定( この順番は関係ない )
	//// デバイスがリセットされない限り、この値がデバイスに保持される
	pDevice->SetTransform(D3DTS_VIEW, &mtxView_);
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection_);
}