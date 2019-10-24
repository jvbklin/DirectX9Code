//=================================================================================
//
//    Polygon2D cpp
//    Author : Lin He                                        作成日 : 2018/11/16
//
//=================================================================================

#include "DirectX9.h"

#include "Polygon2D.h"

//*****************************************************************************
// Macro Definition
//*****************************************************************************

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_2D	( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// Struct Declaration
//*****************************************************************************

typedef struct
{
	D3DXVECTOR3 pos;		// 座標
	D3DCOLOR    color;		// カラー
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer;

//=====================================================================
// [ 2D用ポリゴン初期化関数 ]
//=====================================================================
bool InitPolygon2D()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
		D3DUSAGE_WRITEONLY,									// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
		FVF_VERTEX_2D,										// 頂点属性
		D3DPOOL_MANAGED,									// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
		&g_pVertexBuffer,									// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
		NULL);												// NULLでいい

	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファが作れなたっか", L"error", MB_OK);
		return false;
	}


	return true;
}

//=====================================================================
// [ 2D用ポリゴン終了化関数 ]
//=====================================================================
void UninitPolygon2D()
{
	SAFE_RELEASE(g_pVertexBuffer);
}

//=====================================================================
// [ 2D用ポリゴン描画関数 ]
//=====================================================================
void DrawPolygon2D(float x, float y, float plygon_width_half, float polygon_height_half,
									 int texture_width		, int texture_height,
									 int texture_cut_x		, int texture_cut_y,
									 int texture_cut_width	, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVFの設定( デバイスの方に頂点の属性を教える )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*↓ 0でも大丈夫、０を入れると全部ロックします*/
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

	pDevice->SetStreamSource(0,						// パイプライン番号
							 g_pVertexBuffer,		// バーテックスバッファ変数名
							 0,						// どこから流し込むか(offset)
							 sizeof(VERTEX_2D));	// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}

//=====================================================================
// [ 2Dスプライト描画関数 ]
//=====================================================================
void DrawSprite2D(float x, float y, float plygon_width_half, float polygon_height_half,
									float uv_left		   , float uv_right,
									float uv_up			   , float uv_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVFの設定( デバイスの方に頂点の属性を教える )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*↓ 0でも大丈夫、０を入れると全部ロックします*/
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

	pDevice->SetStreamSource(0,						// パイプライン番号
							 g_pVertexBuffer,		// バーテックスバッファ変数名
							 0,						// どこから流し込むか(offset)
							 sizeof(VERTEX_2D));	// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


//=====================================================================
// [ 四角形ポリゴン描画関数 ]
//=====================================================================
void DrawRect2D(float x, float y, float plygon_width, float polygon_height,
								  float uv_left,	  float uv_right,
								  float uv_up,		  float uv_down)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// FVFの設定( デバイスの方に頂点の属性を教える )
	pDevice->SetFVF(FVF_VERTEX_2D);

	{
		D3DXMATRIX mtxWorld;

		D3DXMatrixTranslation(&mtxWorld, x, y, 0.0f);
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	}

	{
		VERTEX_2D* pV;

		//*↓ 0でも大丈夫、０を入れると全部ロックします*/
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

	pDevice->SetStreamSource(0,						// パイプライン番号
							 g_pVertexBuffer,		// バーテックスバッファ変数名
							 0,						// どこから流し込むか(offset)
							 sizeof(VERTEX_2D));	// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}