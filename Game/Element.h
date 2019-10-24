//=================================================================================
//
//    Element header
//    Author : Lin He                                        çÏê¨ì˙ : 2018/11/23
//
//=================================================================================

#ifndef _ELEMENT_UI_H_
#define _ELEMENT_UI_H_

#include "../Base/DirectX9.h"

namespace Element
{
	enum Type
	{
		NUll = 0,
		EATRTH = 1,
		FIRE = 2,
		WIND = 3,
		WATER = 4
	};
};

struct ElementSet
{
	int earth_value;
	int fire_value;
	int wind_value;
	int water_value;

	int  GetElementValue(Element::Type type);
	void SetElementValue(Element::Type type, int value);
	void IncreaseElement(Element::Type type, int value);

};

class ElementUI
{

public:
	void Init();
	void Uninit();
	void Draw(ElementSet element_set);

private:

	LPDIRECT3DTEXTURE9 element_null_tex_;
	LPDIRECT3DTEXTURE9 element_earth_tex_;
	LPDIRECT3DTEXTURE9 element_fire_tex_;
	LPDIRECT3DTEXTURE9 element_wind_tex_;
	LPDIRECT3DTEXTURE9 element_water_tex_;
};

#endif