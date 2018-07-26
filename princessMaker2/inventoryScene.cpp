#include "stdafx.h"
#include "inventoryScene.h"
#include "princess.h"

inventoryScene::inventoryScene()
{
}


inventoryScene::~inventoryScene()
{
}

HRESULT inventoryScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setItem();

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].img = new image;
		_chooseBox[i].img->init("image/main/storeQuit(240x40,2x1).bmp", 240, 40, 2, 1, true, RGB(255, 0, 255));
		_chooseBox[i].data.rc = RectMake(10, 260 + i * 50, 120, 40);
		_chooseBox[i].data.isSelected = _chooseBox[i].data.isChoose = false;
	}
	_chooseBox[0].data.str = "公扁秦力";
	_chooseBox[1].data.str = "规绢秦力";

	return S_OK;
}

void inventoryScene::update()
{
	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].frameX = 0;
		if (PtInRect(&_chooseBox[i].data.rc, _ptMouse))
		{
			_chooseBox[i].frameX = 1;
		}
	}
	for (int i = 0; i < _vInvenImg.size(); i++)
	{
		_vInvenImg[i].frameX = 0;
		if (PtInRect(&_vInvenImg[i].data.rc, _ptMouse))
		{
			_vInvenImg[i].frameX = 1;
		}
	}
}

void inventoryScene::render()
{
	IMAGEMANAGER->findImage("info3Back")->render(DC, 10, 135);
	TextOut(DC, 20, 145, "公扁", strlen("公扁"));
	TextOut(DC, 20, 200, "规绢", strlen("规绢"));
	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].img->frameRender(DC, _chooseBox[i].data.rc.left, _chooseBox[i].data.rc.top, _chooseBox[i].frameX, 0);
		TextOut(DC, _chooseBox[i].data.rc.left + 20, _chooseBox[i].data.rc.top + 12, _chooseBox[i].data.str.c_str(), strlen(_chooseBox[i].data.str.c_str()));
	}

	for (int i = 0; i < _vInvenImg.size(); i++)
	{
		_vInvenImg[i].img->frameRender(DC, _vInvenImg[i].data.rc.left, _vInvenImg[i].data.rc.top, _vInvenImg[i].frameX, 0);
		_vInven[i]->render();
		TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 5, _vInven[i]->getName().c_str(), strlen(_vInven[i]->getName().c_str()));
		string gold = to_string(_vInven[i]->getPrice()) + "G";
		TextOut(DC, _vInven[i]->getX() + 45, _vInven[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

		vector<pair<string, float>> vTemp = _vInven[i]->getProperty();
		for (int j = 0; j < vTemp.size(); j++)
		{
			TextOut(DC, _vInven[i]->getX() + j * 80, _vInven[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
			if (vTemp[j].second > 0)
				TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + j * 80, _vInven[i]->getY() + 45, "+", strlen("+"));
			char stat[128];
			sprintf_s(stat, "%d", (int)vTemp[j].second);
			TextOut(DC, _vInven[i]->getX() + vTemp[j].first.size() * 8 + 10 + j * 80, _vInven[i]->getY() + 45, stat, strlen(stat));
		}
	}
}

void inventoryScene::release()
{
}

void inventoryScene::setItem()
{
	_vInven = _princess->getVItem();
	_vInvenImg.resize(_vInven.size());

	for (int i = 0; i < _vInven.size(); i++)
	{
		_vInvenImg[i].img = new image;
		_vInvenImg[i].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
		if((i % 12) < 8)
			_vInvenImg[i].data.rc = RectMake(20 + (i % 4) * 190, 445 + (i / 4) * 76, 190, 76);
		else
			_vInvenImg[i].data.rc = RectMake(590, 369 - ((i % 8) - 8) * 76, 190, 76);
	}

	for (int i = 0; i < _vInven.size(); i++)
	{
		_vInven[i]->setXY(_vInvenImg[i].data.rc.left + 7, _vInvenImg[i].data.rc.top + 5);
	}
}