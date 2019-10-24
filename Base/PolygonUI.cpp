//=================================================================================
//
//    PolygonUI header
//    Author : Lin He                                        作成日 : 2018/11/16
//
//=================================================================================

#include "DirectX9.h"

#include "PolygonUI.h"

//*****************************************************************************
// Macro Definition
//*****************************************************************************

// 頂点属性(1つ目：座標、2つ目：カラー,3つ目：テクスチャー)
#define FVF_VERTEX_UI	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

//*****************************************************************************
// Struct Declaration
//*****************************************************************************

typedef struct
{
	D3DXVECTOR4 pos;		// 座標
	D3DCOLOR    color;		// カラー
	D3DXVECTOR2 texcoord;
}VERTEX_UI;

//*****************************************************************************
// Global Variables Declaration
//*****************************************************************************
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBufferUI;

//=====================================================================
// [ UIポリゴン初期化関数 ]
//=====================================================================
bool InitPolygonUI()
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	HRESULT hr;
	// VRAMのメモリを確保(GPUに依頼)(頂点バッファの作成)
	hr = pDevice->CreateVertexBuffer(sizeof(VERTEX_UI) * 4,	// 借りたいbafの量(バイト)、つまり1頂点の容量×必要頂点数
		D3DUSAGE_WRITEONLY,									// 使用用途(今回は書き込みのみ、GPUが早く動くが書き込んだデータを読んではダメ(値が不定))
		FVF_VERTEX_UI,										// 頂点属性
		D3DPOOL_MANAGED,									// 頂点バッファの管理方法( MANAGEDは管理はDirect3Dにお任せという意味 )
		&g_pVertexBufferUI,									// 管理者の居場所のメモ帳(ポインタのポインタ)(全てはこれの値を知るための作業)
		NULL);												// NULLでいい

	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファが作れなたっか", L"error", MB_OK);
		return false;
	}


	return true;
}


//=====================================================================
// [ UIポリゴン終了化関数 ]
//=====================================================================
void UninitPolygonUI()
{
	SAFE_RELEASE(g_pVertexBufferUI);
}

//=====================================================================
// [ UIポリゴン描画関数 ]
//=====================================================================
void DrawPolygonUI(float x, float y, int texture_width, int texture_height,
									int texture_cut_x, int texture_cut_y,
									int texture_cut_width, int texture_cut_height)
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	VERTEX_UI* pV;
	/*↓ 0でも大丈夫、０を入れると全部ロックします*/
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


	pDevice->SetStreamSource(0,						// パイプライン番号
							 g_pVertexBufferUI,		// バーテックスバッファ変数名
							 0,						// どこから流し込むか(offset)
							 sizeof(VERTEX_UI));	// ストライド値(隣の頂点までの長さ＝1頂点の大きさ)

	//FVF(今から使用する頂点情報)の設定
	pDevice->SetFVF(FVF_VERTEX_UI);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}