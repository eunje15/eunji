#include "stdafx.h"
#include "princessScene.h"


princessScene::princessScene()
{
}


princessScene::~princessScene()
{
}

HRESULT princessScene::init()
{
	_princess = SCENEMANAGER->getPrincessAddress();

	_back = IMAGEMANAGER->findImage("back");
	_cal.img = IMAGEMANAGER->findImage("cal");
	_cal.x = _cal.y = 0;

	//�ӽ÷� ����
	_year = 1200, _mon = 2, _day = 28, _dayOfWeek = 0;
	_yearImg.img = IMAGEMANAGER->findImage("year");
	_yearImg.frameY = _year - 1200;
	_monImg.img = IMAGEMANAGER->findImage("month");
	_monImg.frameY = _mon - 1;
	_dayImg.img = IMAGEMANAGER->findImage("day");
	_dayImg.frameY = _day - 1;
	_dayOfWeekImg.img = IMAGEMANAGER->findImage("dayOfWeek");
	_dayOfWeekImg.frameY = _dayOfWeek;

	_season = SPRING;
	_flower.img = IMAGEMANAGER->findImage("flower");
	_flower.frameX = (int)_season;
	_flower.x = 0, _flower.y = 155;

	_frame.img = IMAGEMANAGER->findImage("mainFrame");
	_frame.frameX = 5;
	_frame.x = 460, _frame.y = 92;

	_status.img = IMAGEMANAGER->findImage("status");
	_status.x = WINSIZEX - _status.img->getWidth();
	_status.y = 0;
	setStringStatus();
	_printStrStatus.str = _strStatus[1].str; //�ӽ�
	_printStrStatus.rc = RectMake(600,166, _status.img->getWidth(), 22);
	_nameRc = RectMake(600, 12, _status.img->getWidth(), 22);
	_firstNameRc = RectMake(600, 34, _status.img->getWidth(), 22);

	_menu.img = IMAGEMANAGER->findImage("menu");
	_menu.x = WINSIZEX - _menu.img->getFrameWidth();
	_menu.y = _status.img->getHeight();
	_menu.frameX = 0;

	_selectMenu = IMAGEMANAGER->findImage("selectMenu");
	_selectMenu->setX(WINSIZEX - _menu.img->getFrameWidth());
	_selectMenu->setY(_status.img->getHeight());
	

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_menubox[i*4 + j].rc = RectMake(_menu.x + j * 50, _menu.y + 40 * i, 50, 40);
			_menubox[i].isSelected = false;
		}
	}
	_menubox[8].rc = RectMake(_menu.x, _menu.y + 80, 200, 40);
	_menubox[8].isSelected = false;
	_menuType = SELECT_NONE;

	_perHealth = _perBad = _personalConnect = 0;

	return S_OK;
}

void princessScene::update()
{
	for (int i = 0; i < 9; i++)
	{
		_menubox[i].isSelected = false;
		if (PtInRect(&_menubox[i].rc, _ptMouse))
		{
			_menubox[i].isSelected = true;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (i)
				{
					case 0:
						_menuType = SELECT_STATUS;
					break;
					case 1:
						_menuType = SELECT_TALK;
					break;
					case 2:
						_menuType = SELECT_CHANGE_INFO;
					break;
					case 3:
						_menuType = SELECT_INFO;
					break;
					case 4:
						_menuType = SELECT_TOWN;
					break;
					case 5:
						_menuType = SELECT_CASTLE;
					break;
					case 6:
						_menuType = SELECT_WEAPON;
					break;
					case 7:
						_menuType = SELECT_SAVE;
					break;
					case 8:
						_menuType = SELECT_SCHEDULE;
					break;
				}
				_menubox[i].isData = true;
			}
		}
	}
	
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_menuType = SELECT_NONE;
	}
}

void princessScene::render()
{
	_back->render(DC);
	_cal.img->render(DC);
	_yearImg.img->frameRender(DC, 68, 11, 0, _yearImg.frameY);
	_monImg.img->frameRender(DC, 10, 40, 0, _monImg.frameY);
	_dayOfWeekImg.img->frameRender(DC, 20, 70, 0, _dayOfWeekImg.frameY);
	_dayImg.img->frameRender(DC, 88, 38, 0, _dayImg.frameY);
	_flower.img->frameRender(DC, _flower.x, _flower.y, _flower.frameX, 0);
	_frame.img->frameRender(DC, _frame.x, _frame.y, _frame.frameX, 0);
	
	_princess->render();
	
	_status.img->render(DC, _status.x, _status.y);
	DrawText(DC, _princess->getInfo().name.c_str(), strlen(_princess->getInfo().name.c_str()), &_nameRc, DT_CENTER | DT_VCENTER);
	DrawText(DC, _princess->getInfo().firstName.c_str(), strlen(_princess->getInfo().firstName.c_str()), &_firstNameRc, DT_CENTER | DT_VCENTER);
	DrawText(DC, _printStrStatus.str.c_str(), strlen(_printStrStatus.str.c_str()), &_printStrStatus.rc, DT_CENTER | DT_VCENTER);
	IMAGEMANAGER->findImage("number")->frameRender(DC, 615, 80, 1, 0);
	IMAGEMANAGER->findImage("number")->frameRender(DC, 630, 80, _princess->getInfo().age % 10, 0);
	
	switch (_menuType)
	{
	case SELECT_NONE:
		_menu.img->frameRender(DC, _menu.x, _menu.y, _menu.frameX, 0);
		for (int i = 0; i < 9; i++)
		{
			if (!_menubox[i].isSelected) continue;
			_selectMenu->render(DC, _menubox[i].rc.left, _menubox[i].rc.top, 50 * (i % 4), 40 * (i / 4), _menubox[i].rc.right - _menubox[i].rc.left, _menubox[i].rc.bottom - _menubox[i].rc.top);
		}

		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < 9; i++)
			{
				Rectangle(DC, _menubox[i].rc.left, _menubox[i].rc.top, _menubox[i].rc.right, _menubox[i].rc.bottom);
			}
		}
		break;
	case SELECT_STATUS:
		statusRender();
		break;
	case SELECT_TALK:
		break;
	case SELECT_CHANGE_INFO:
		break;
	case SELECT_INFO:
		infoRender();
		break;
	case SELECT_TOWN:
		break;
	case SELECT_CASTLE:
		break;
	case SELECT_WEAPON:
		break;
	case SELECT_SAVE:
		break;
	case SELECT_SCHEDULE:
		break;
	}
	char str[128];
	SetBkMode(DC, TRANSPARENT);
	SetTextColor(DC, RGB(255, 255, 255));
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 50, 50, str, strlen(str));
}

void princessScene::infoRender()
{
	IMAGEMANAGER->findImage("info1Back")->render(DC, 28, 103);
	IMAGEMANAGER->findImage("info2Back")->render(DC, 28, 106 + IMAGEMANAGER->findImage("info1Back")->getHeight());
	IMAGEMANAGER->findImage("info3Back")->render(DC, WINSIZEX - 260, 105 + IMAGEMANAGER->findImage("info1Back")->getHeight());
	IMAGEMANAGER->findImage("info4Back")->render(DC, WINSIZEX - 285, 228 + IMAGEMANAGER->findImage("info1Back")->getHeight());

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 400, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("����ü"));
	oldFont = (HFONT)SelectObject(DC, font);
	//info1
	TextOut(DC, 40, 110, "�̸�", strlen("�̸�"));
	TextOut(DC, 40, 135, "��", strlen("��"));
	TextOut(DC, 40, 160, "������", strlen("������"));
	TextOut(DC, 40, 185, "����", strlen("����"));
	TextOut(DC, 40, 210, "����", strlen("����"));
	TextOut(DC, 40, 235, "���ڸ�", strlen("���ڸ�"));
	TextOut(DC, 40, 260, "��ȣ��", strlen("��ȣ��"));

	TextOut(DC, 120, 110, _princess->getInfo().name.c_str(), strlen(_princess->getInfo().name.c_str()));
	TextOut(DC, 120, 135, _princess->getInfo().firstName.c_str(), strlen(_princess->getInfo().firstName.c_str()));
	TextOut(DC, 120, 160, _princess->getInfo().strBlood.c_str(), strlen(_princess->getInfo().strBlood.c_str()));
	TextOut(DC, 120, 185, to_string(_princess->getInfo().age).c_str(), strlen(to_string(_princess->getInfo().age).c_str()));
	char str[128];
	sprintf_s(str, "%d/%d/%d", _princess->getInfo().year, _princess->getInfo().mon, _princess->getInfo().day);
	TextOut(DC, 120, 210, str, strlen(str));
	TextOut(DC, 120, 235, _princess->getStatus().god.constellation.c_str(), strlen(_princess->getStatus().god.constellation.c_str()));
	TextOut(DC, 120, 260, _princess->getStatus().god.planet.c_str(), strlen(_princess->getStatus().god.planet.c_str()));

	//info2
	TextOut(DC, 40, 300, "���� ����", strlen("���� ����"));
	TextOut(DC, 40, 325, "�ҷ�ȭ ����", strlen("�ҷ�ȭ ����"));
	TextOut(DC, 40, 350, "�θ�", strlen("�θ�"));

	TextOut(DC, 200, 300, (to_string(_perHealth) + "%").c_str(), strlen((to_string(_perHealth) + "%").c_str()));
	TextOut(DC, 200, 325, (to_string(_perBad) + "%").c_str(), strlen((to_string(_perBad) + "%").c_str()));
	TextOut(DC, 200, 350, to_string(_personalConnect).c_str(), strlen(to_string(_personalConnect).c_str()));

	//�ӽ÷� ����
	TextOut(DC, 40, 375, "�ǰ��մϴ�", strlen("�ǰ��մϴ�"));
	TextOut(DC, 40, 400, "�����մϴ�", strlen("�����մϴ�"));

	string str1 = "�ǰ���" + _printStrStatus.str+"��";
	TextOut(DC, 40, 440, str1.c_str(), strlen(str1.c_str()));

	//info3
	TextOut(DC, WINSIZEX - 250, 300, "Ű", strlen("Ű"));
	TextOut(DC, WINSIZEX - 250, 320, "������", strlen("������"));
	TextOut(DC, WINSIZEX - 250, 340, "����", strlen("����"));
	TextOut(DC, WINSIZEX - 250, 360, "�㸮", strlen("�㸮"));
	TextOut(DC, WINSIZEX - 250, 380, "������", strlen("������"));

	//info4
	TextOut(DC, WINSIZEX - 270, 425, "����", strlen("����"));
	TextOut(DC, WINSIZEX - 270, 470, "��", strlen("��"));
	SelectObject(DC, oldFont);
	DeleteObject(font);
}

void princessScene::statusRender()
{
	IMAGEMANAGER->findImage("status1Back")->render(DC, 8, 150);
	IMAGEMANAGER->findImage("status2Back")->render(DC, 8, 165 + IMAGEMANAGER->findImage("status1Back")->getHeight());
	IMAGEMANAGER->findImage("status3Back")->render(DC, WINSIZEX - 260, 275);
	IMAGEMANAGER->findImage("status4Back")->render(DC, WINSIZEX - 260, 390);
}
void princessScene::release()
{
}

void princessScene::setStringStatus()
{
	_strStatus[0].str = "�������� �ʴ´�";
	_strStatus[1].str = "��·�� ưư�ϰ�";
	_strStatus[2].str = "������ ���̷�";
	_strStatus[3].str = "���̾�Ʈ ��Ų��";
}
