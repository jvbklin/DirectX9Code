//=================================================================================
//
//    Polygon2D header
//    Author : Lin He                                        �쐬�� : 2018/11/16
//
//=================================================================================

#ifndef _POLYGON_2D_H_
#define _POLYGON_2D_H_

//=====================================================================
// [ 2D�p�|���S���������֐� ]
//=====================================================================
bool InitPolygon2D();

//=====================================================================
// [ 2D�p�|���S���I�����֐� ]
//=====================================================================
void UninitPolygon2D();

//=====================================================================
// [ 2D�p�|���S���`��֐� ]
//=====================================================================
void DrawPolygon2D(float x, float y, float plygon_width_half, float polygon_height_half,
									 int texture_width,		  int texture_height,
									 int texture_cut_x,		  int texture_cut_y,
									 int texture_cut_width,	  int texture_cut_height);

//=====================================================================
// [ 2D�X�v���C�g�`��֐� ]
//=====================================================================
void DrawSprite2D(float x, float y, float plygon_width_half, float polygon_height_half,
									float uv_left = 0.0f,	 float uv_right = 1.0f,
									float uv_up = 0.0f,		 float uv_down = 1.0f);

//=====================================================================
// [ 2D�l�p�`�|���S���`��֐� ]
//=====================================================================
void DrawRect2D(float x, float y, float plygon_width,   float polygon_height,
								  float uv_left = 0.0f, float uv_right = 1.0f,
								  float uv_up = 0.0f,   float uv_down = 1.0f);
#endif // !_POLYGON_2D_H_

