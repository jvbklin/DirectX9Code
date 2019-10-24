//=================================================================================
//
//    Element cpp
//    Author : Lin He                                        作成日 : 2018/11/23
//
//=================================================================================

#include "Element.h"

#include "../Base/PolygonUI.h"


int ElementSet::GetElementValue(Element::Type type)
{
	switch (type)
	{
	case Element::EATRTH:
		return earth_value;
	case Element::FIRE:
		return fire_value;
	case Element::WIND:
		return wind_value;
	case Element::WATER:
		return water_value;
	}
	return 0;
}

void ElementSet::SetElementValue(Element::Type type, int value)
{
	switch (type)
	{
	case Element::EATRTH:
		earth_value = value;
		break;
	case Element::FIRE:
		fire_value = value;
		break;
	case Element::WIND:
		wind_value = value;
		break;
	case Element::WATER:
		water_value = value;
		break;
	default:
		break;
	}
}

void ElementSet::IncreaseElement(Element::Type type, int value)
{
	switch (type)
	{
	case Element::EATRTH:
		earth_value += value;
		break;
	case Element::FIRE:
		fire_value += value;
		break;
	case Element::WIND:
		wind_value += value;
		break;
	case Element::WATER:
		water_value += value;
		break;
	default:
		break;
	}
}


void ElementUI::Init()
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	HRESULT hr;
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_null.png", &element_null_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_earth.png", &element_earth_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_fire.png", &element_fire_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_wind.png", &element_wind_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
	hr = D3DXCreateTextureFromFile(pDevice, L"Resource/Texture/element_water.png", &element_water_tex_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"テクスチャーが読み込みなかった", L"error", MB_OK);
		return;
	}
}

void ElementUI::Uninit()
{
	SAFE_RELEASE(element_null_tex_);
	SAFE_RELEASE(element_earth_tex_);
	SAFE_RELEASE(element_fire_tex_);
	SAFE_RELEASE(element_wind_tex_);
	SAFE_RELEASE(element_water_tex_);
}

void ElementUI::Draw(ElementSet element_set)
{
	// D3DDeviceの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if (pDevice == NULL)
	{
		MessageBox(NULL, L"DirextXデバイス取得失敗した", L"error", MB_OK);
		return;
	}

	pDevice->SetTexture(0, element_null_tex_);
	for (int i = 0; i < 10; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 10.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 45.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 80.0f, 32, 32, 0, 0, 32, 32);
		DrawPolygonUI(20.0f + i * 32, 115.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_earth_tex_);
	for (int i = 0; i < element_set.earth_value; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 10.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_fire_tex_);
	for (int i = 0; i < element_set.fire_value; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 45.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_wind_tex_);
	for (int i = 0; i < element_set.wind_value; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 80.0f, 32, 32, 0, 0, 32, 32);
	}

	pDevice->SetTexture(0, element_water_tex_);
	for (int i = 0; i < element_set.water_value; i++)
	{
		DrawPolygonUI(20.0f + i * 32, 115.0f, 32, 32, 0, 0, 32, 32);
	}
}
