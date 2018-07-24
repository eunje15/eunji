#include "stdafx.h"
#include "weaponStore.h"


weaponStore::weaponStore()
{
}


weaponStore::~weaponStore()
{
}

HRESULT weaponStore::init()
{
	setItem();
	_npc.img = IMAGEMANAGER->findImage("peopleFace");
	_npc.frameX = 6, _npc.frameY = 1;
	setDialog("「어서오세요. 무기도 방어구도 좋은 것들만 모여 있습니다」");
	_dialogIdx = 0;
	_dialogType = STORE_DIALOG_NONE;
	_fin = false;

	for (int i = 0; i < 2; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "물건을 산다";
	_chooseBox[1].str = "가게를 나선다";

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_itemImg[i * 4 + j].img = new image;
			_itemImg[i * 4 + j].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
			_itemImg[i * 4 + j].data.rc = RectMake(20 + j*190, 445 + i*76, 190, 76);
		}
	}

	for (int i = 8; i < 12; i++)
	{
		_itemImg[i].img = new image;
		_itemImg[i].img->init("image/item/itemDialog(380x76,2x1).bmp", 380, 76, 2, 1, true, RGB(255, 0, 255));
		_itemImg[i].data.rc = RectMake(590, 369 - (i - 8) * 76, 190, 76);
	}

	for (int i = 0; i < 12; i++)
	{
		_vItem[i]->setXY(_itemImg[i].data.rc.left + 7, _itemImg[i].data.rc.top + 5);
	}

	_quitImg.data.rc = RectMake(444, 393, 120, 40);
	_quitImg.img = IMAGEMANAGER->findImage("storeQuit");

	_selectItem = false;

	return S_OK;
}

void weaponStore::update()
{
	switch (_dialogType)
	{
	case STORE_DIALOG_FIN:
		for (int i = 0; i < 2; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
						_dialogType = STORE_DIALOG_SELECT;
					else if (i == 1)
						_fin = true;
				}
			}
		}
		break;
	case STORE_DIALOG_SELECT:
		if (!_selectItem)
		{
			for (int i = 0; i < 12; i++)
			{
				_itemImg[i].frameX = 0;
				if (PtInRect(&_itemImg[i].data.rc, _ptMouse))
				{
					_itemImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_selectItem = true;
						_itemImg[i].data.isChoose = true;
						_itemImg[i].frameX = 0;
						string str = "「" + _vItem[i]->getName() + "은 " + to_string(_vItem[i]->getPrice()) + "G 입니다.」";
						setDialog(str);
					}
				}
			}
		}
		_quitImg.frameX = 0;
		if(PtInRect(&_quitImg.data.rc, _ptMouse))
		{
			_quitImg.frameX = 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_fin = true;
			}
		}
		break;
	case STORE_DIALOG_CLICK:
		break;
	case STORE_DIALOG_NONE:
		break;
	}
}

void weaponStore::render()
{
	IMAGEMANAGER->findImage("frame")->render(DC, 20, 295);
	_npc.img->frameRender(DC, 30, 305, _npc.frameX, _npc.frameY);
	IMAGEMANAGER->findImage("status4Back")->render(DC, 170, 300);
	if (dialogRender())
	{
		for (int i = 0; i < _vDialog.size(); i++)
		{
			TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
		}
		switch (_dialogType)
		{
		case STORE_DIALOG_FIN:
			IMAGEMANAGER->findImage("2Back")->render(DC, 600, 280);
			for (int i = 0; i < 2; i++)
			{
				if (_chooseBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_chooseBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _chooseBox[i].rc.left + 2, _chooseBox[i].rc.top + 5, _chooseBox[i].str.c_str(), strlen(_chooseBox[i].str.c_str()));
			}
			break;
		case STORE_DIALOG_SELECT:
			for (int i = 0; i < 12; i++)
			{
				if (_selectItem && !_itemImg[i].data.isChoose) continue;
				//Rectangle(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top, _itemImg[i].data.rc.right, _itemImg[i].data.rc.bottom);
				_itemImg[i].img->frameRender(DC, _itemImg[i].data.rc.left, _itemImg[i].data.rc.top,_itemImg[i].frameX, 0);
				_vItem[i]->render();
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 5, _vItem[i]->getName().c_str(), strlen(_vItem[i]->getName().c_str()));
				string gold = to_string(_vItem[i]->getPrice()) + "G";
				TextOut(DC, _vItem[i]->getX() + 45, _vItem[i]->getY() + 25, gold.c_str(), strlen(gold.c_str()));

				vector<pair<string, int>> vTemp = _vItem[i]->getProperty();
				for (int j = 0; j < vTemp.size(); j++)
				{
					TextOut(DC, _vItem[i]->getX() + j * 80, _vItem[i]->getY() + 45, vTemp[j].first.c_str(), strlen(vTemp[j].first.c_str()));
					if(vTemp[j].second > 0)
						TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size()*8 + j * 80, _vItem[i]->getY() + 45, "+", strlen("+"));
					TextOut(DC, _vItem[i]->getX() + vTemp[j].first.size()*8 + 10 + j * 80, _vItem[i]->getY() + 45, to_string(vTemp[j].second).c_str(), strlen(to_string(vTemp[j].second).c_str()));
				}

				_quitImg.img->frameRender(DC, 444, 393, _quitImg.frameX, 0);

				TextOut(DC, _quitImg.data.rc.left + 30, _quitImg.data.rc.top + 10, "관둔다", strlen("관둔다"));
			}
			break;
		case STORE_DIALOG_CLICK:
			break;
		}
	}
}

void weaponStore::release()
{
}

void weaponStore::setItem()
{
	vector<string> vStr = TXTDATA->txtLoadCsv("dialog/weapon2.csv");
	int idx = 0;
	for (int i = 0; i < vStr.size(); i++)
	{
		char str[100000];
		strcpy(str, vStr[i].c_str());
		vector<string> temp = TXTDATA->charArraySeparation(str);
		item* tItem = new item;
		vector<pair<string, int>> property;
		if (temp[2] == "X") continue;
		for (int j = 3; j < temp.size() - 1; j += 2)
		{
			property.push_back(make_pair(temp[j], atoi(temp[j + 1].c_str())));
		}
			if (i < 10)
				tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 0, i, 0);
			else
				tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 1, i, 0);
			_vItem.push_back(tItem);
		//	idx++;
	}
}


void weaponStore::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	_vDialog.push_back("무기점의 제노");
	while (1)
	{
		if (strSize > 30)
		{
			_vDialog.push_back(str.substr(idx, 30));
			idx += 30;
			strSize -= 30;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool weaponStore::dialogRender()
{
	if (_dialogType != STORE_DIALOG_NONE) return true;

	if (_dialogIdx < _vDialog.size())
	{
		string temp = DIALOG->getCurrentDialog();
		if (temp == "end")
		{
			_dialogIdx++;
			if (_dialogIdx < _vDialog.size())
				DIALOG->setDialog(_vDialog[_dialogIdx], 5);
		}
		else
		{
			if (_dialogIdx > 0)
			{
				for (int i = 0; i < _dialogIdx; i++)
				{
					TextOut(DC, 180, 310 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 180, 310 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = STORE_DIALOG_FIN;
		return true;
	}
	return false;
}