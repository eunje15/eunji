#include "stdafx.h"
#include "saveLoadScene.h"
#include "princess.h"

saveLoadScene::saveLoadScene()
{
}


saveLoadScene::~saveLoadScene()
{
}

HRESULT saveLoadScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	setGodPhoto();
	_npc.img = IMAGEMANAGER->findImage("godFace");
	setDialog("수호성에게 기도한다");
	_dialogIdx = 0;
	_dialogType = DIALOG_FIN;
	_type = SAVELOAD_FIN;
	_fin = false;

	for (int i = 0; i < 3; i++)
	{
		_chooseBox[i].rc = RectMake(610, 295 + i * 28, 120, 28);
		_chooseBox[i].isSelected = _chooseBox[i].isChoose = false;
	}
	_chooseBox[0].str = "시간을 기록한다";
	_chooseBox[1].str = "시간을 되돌린다";
	_chooseBox[2].str = "잠시동안의 이별";


	for (int i = 9; i >= 0; i--)
	{
		_saveLoadInfo[i].img = new image;
		_saveLoadInfo[i].img->init("image/main/saveBack(560x70,1x2).bmp", 460, 70, 1, 2, false, RGB(255, 0, 255));
		_saveLoadInfo[i].data.rc = RectMake(0, WINSIZEY - (i + 1)* 35, 460, 35);
		_saveLoadInfo[i].data.str = to_string(10 - i) + ".";
	}
	return S_OK;
}

void saveLoadScene::update()
{
	switch (_type)
	{
	case SAVELOAD_FIN:
		for (int i = 0; i < 3; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
						_type = SAVELOAD_SAVE;
				}
			}
		}
		break;
	case SAVELOAD_SAVE:
		for (int i = 0; i < 10; i++)
		{
			_saveLoadInfo[i].frameY = 0;
			if (PtInRect(&_saveLoadInfo[i].data.rc, _ptMouse))
			{
				_saveLoadInfo[i].frameY = 1;
			}
		}
		break; 
	case SAVELOAD_LOAD:
			break;
	case SAVELOAD_NONE:
		break;
	}
}

void saveLoadScene::render()
{
	IMAGEMANAGER->findImage("wideBack")->render(DC, 40, 460);
	if (dialogRender())
	{
		for (int i = 0; i < _vDialog.size(); i++)
		{
			TextOut(DC, 50, 470 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
		}
		switch (_type)
		{
		case SAVELOAD_FIN:
			IMAGEMANAGER->findImage("3Back")->render(DC,590,280);
			for (int i = 0; i < 3; i++)
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
		case SAVELOAD_SAVE:
			IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX - 150, _saveLoadInfo[9].data.rc.top);
			_npc.img->frameRender(DC, WINSIZEX - 140, _saveLoadInfo[9].data.rc.top + 10, _npc.frameX, 0);
			IMAGEMANAGER->findImage("info2Back")->render(DC, 540, 410);
			TextOut(DC, 550, 420, "시간을 기록해라", strlen("시간을 기록해라"));
			for (int i = 0; i < 10; i++)
			{
				_saveLoadInfo[i].img->frameRender(DC, _saveLoadInfo[i].data.rc.left, _saveLoadInfo[i].data.rc.top, 0, _saveLoadInfo[i].frameY);
				TextOut(DC, _saveLoadInfo[i].data.rc.left + 10, _saveLoadInfo[i].data.rc.top + 8, _saveLoadInfo[i].data.str.c_str(), strlen(_saveLoadInfo[i].data.str.c_str()));
			}
			break;
		case SAVELOAD_LOAD:
			break;
		case SAVELOAD_NONE:
			break;
		}
	}
}

void saveLoadScene::release()
{
}

void saveLoadScene::saveData(int idx)
{
	FILE 
}

void saveLoadScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
	while (1)
	{
		if (strSize > 29)
		{
			_vDialog.push_back(str.substr(idx, 29));
			idx += 29;
			strSize -= 29;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool saveLoadScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

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
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}

void saveLoadScene::setGodPhoto()
{
	_godName = _princess->getStatus().god.name;
	_godPlanet = _princess->getStatus().god.planet;

	if (_godName == "새턴")
		_npc.frameX = 0;
	else if (_godName == "우라누스")
		_npc.frameX = 1;
	else if (_godName == "넵튠")
		_npc.frameX = 2;
	else if (_godName == "마스")
		_npc.frameX = 3;
	else if (_godName == "비너스")
		_npc.frameX = 4;
	else if (_godName == "머큐리")
		_npc.frameX = 5;
	else if (_godName == "더 문")
		_npc.frameX = 6;
	else if (_godName == "솔")
		_npc.frameX = 7;
	else if (_godName == "하데스")
		_npc.frameX = 8;
	else if (_godName == "주피터")
		_npc.frameX = 9;
}