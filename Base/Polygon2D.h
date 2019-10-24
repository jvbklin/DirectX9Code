//=================================================================================
//
//    Polygon2D header
//    Author : Lin He                                        作成日 : 2018/11/16
//
//=================================================================================

#ifndef _POLYGON_2D_H_
#define _POLYGON_2D_H_

//=====================================================================
// [ 2D用ポリゴン初期化関数 ]
//=====================================================================
bool InitPolygon2D();

//=====================================================================
// [ 2D用ポリゴン終了化関数 ]
//=====================================================================
void UninitPolygon2D();

//=====================================================================
// [ 2D用ポリゴン描画関数 ]
//=====================================================================
void DrawPolygon2D(float x, float y, float plygon_width_half, float polygon_height_half,
									 int texture_width,		  int texture_height,
									 int texture_cut_x,		  int texture_cut_y,
									 int texture_cut_width,	  int texture_cut_height);

//=====================================================================
// [ 2Dスプライト描画関数 ]
//=====================================================================
void DrawSprite2D(float x, float y, float plygon_width_half, float polygon_height_half,
									float uv_left = 0.0f,	 float uv_right = 1.0f,
									float uv_up = 0.0f,		 float uv_down = 1.0f);

//=====================================================================
// [ 2D四角形ポリゴン描画関数 ]
//=====================================================================
void DrawRect2D(float x, float y, float plygon_width,   float polygon_height,
								  float uv_left = 0.0f, float uv_right = 1.0f,
								  float uv_up = 0.0f,   float uv_down = 1.0f);
#endif // !_POLYGON_2D_H_

