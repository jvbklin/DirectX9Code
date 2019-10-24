//=================================================================================
//
//    Camera header
//    Author : Lin He                                        作成日 : 2018/11/16
//
//=================================================================================

#include "DirectX9.h"

//*****************************************************************************
// Camera Class
//
// ゲームシーンのカメラ設定を行うクラス
//*****************************************************************************
class Camera
{

public:
	void Init();

//-------------------------------------------------------------------------

private:

	// ビュー変換行列( 4×4のfloat行列 )
	D3DXMATRIX mtxView_;

	// プロジェクション変換行列( 4×4のfloat行列 )
	D3DXMATRIX mtxProjection_;

};