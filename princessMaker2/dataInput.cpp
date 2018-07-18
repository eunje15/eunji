#include "stdafx.h"
#include "dataInput.h"
#include "princess.h"


dataInput::dataInput()
{
}


dataInput::~dataInput()
{
}

HRESULT dataInput::init()
{
	_mode = PROLOGUE_CAL;
	//setDadName();
	setCal();
	return S_OK;
}

void dataInput::update()
{
	if (PtInRect(&_okBtn.rc, _ptMouse))
	{
		_okBtn.isSelected = true;
		_okBtn.idX = 1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			changeMode();
		}
	}
	else
		_okBtn.idX = 0;

	
}

void dataInput::render()
{	
	switch (_mode)
	{
	case PROLOGUE_DADNAME:
		setDadNameRender();
		break;
	case PROLOGUE_DADCAL:
		dadCalRender();
		break;
	case PROLOGUE_DADAGE:
		dadAgeRender();
		break;
	case PROLOGUE_NAME:
		setPrincessNameRender();
		break;
	case PROLOGUE_CAL:
		CalRender();
		break;
	case PROLOGUE_BLOOD:
		break;
	case PROLOGUE_DIALOG:
		break;
	}

	char str[128];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 100, 100, str, strlen(str));
}

void dataInput::release()
{
}

void dataInput::setDadName()
{
	_isInput = true;
	_back = IMAGEMANAGER->findImage("dadName");
	_okBtn.rc = RectMake(510, WINSIZEY / 2, 68, 37);
	_okBtn.isSelected = _okBtn.idX = _okBtn.idY = 0;
}

void dataInput::setDadNameRender()
{
	_back->render(DC, 0, 0);

	SetTextColor(DC, RGB(255, 255, 255));
	RectangleMake(DC, WINSIZEX / 2 - 195, WINSIZEY / 2, 300, 30);

	SetTextColor(DC, RGB(0, 0, 0));
	if (_inputData.size())
	{
		list<TCHAR>::iterator iter = _inputData.begin();
		string str = "";
		for (; iter != _inputData.end(); iter++)
		{
			str += *iter;
		}
		_dadName = str;
		TextOut(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 + 5, str.c_str(), strlen(str.c_str()));
	}
	IMAGEMANAGER->findImage("dadOK")->frameRender(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.idX, 0);
}
void dataInput::setPrincessName()
{
	_isInput = true;
	_back = IMAGEMANAGER->findImage("princessName");
	_okBtn.rc = RectMake(510, WINSIZEY / 2, 68, 37);
	_okBtn.isSelected = _okBtn.idX = _okBtn.idY = 0;
}

void dataInput::setPrincessNameRender()
{
	_dadOrDaughter = true;

	_back->render(DC, 0, 0);

	SetTextColor(DC, RGB(255, 255, 255));
	RectangleMake(DC, WINSIZEX / 2 - 195, WINSIZEY / 2, 300, 30);

	SetTextColor(DC, RGB(0, 0, 0));
	if (_inputData.size())
	{
		list<TCHAR>::iterator iter = _inputData.begin();
		string str = "";
		for (; iter != _inputData.end(); iter++)
		{
			str += *iter;
		}
		_princessName = str;
		TextOut(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 + 5, str.c_str(), strlen(str.c_str()));
	}
	IMAGEMANAGER->findImage("princessOK")->frameRender(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.idX, 0);
}

void dataInput::changeMode()
{
	string temp = "";
	switch (_mode)
	{
	case PROLOGUE_DADNAME:
		_mode = PROLOGUE_NAME;
		if (_dadName.size() > 8)
			_dadName = _dadName.substr(0, 7);
		setPrincessName();
		break;
	case PROLOGUE_DADCAL:
		break;
	case PROLOGUE_DADAGE:
		_lDadAgeIter = _lDadAge.begin();
		for (; _lDadAgeIter != _lDadAge.end(); ++_lDadAgeIter)
		{
			temp += to_string(*_lDadAgeIter);
		}
		_dadAge = atoi(temp.c_str());
		if (_dadAge > 9)
		{
			_mode = PROLOGUE_DADCAL;
			setDadCal();
		}
		break;
	case PROLOGUE_NAME:
		_mode = PROLOGUE_NAME;
		if (_princessName.size() > 8)
			_princessName = _princessName.substr(0, 7);
		_princessInfo.name = _princessName;
		break;
	case PROLOGUE_CAL:
		_mode = PROLOGUE_DADAGE;
		setDadAge();
		break;
	case PROLOGUE_BLOOD:
		break;
	case PROLOGUE_DIALOG:
		break;
	}
}

void dataInput::setCal()
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 42; j++)
		{			
			switch (i)
			{
				case 0:
					if ((j < 6 || j > 36)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 5;
					break;
				case 1:
					if ((j < 2 || j > 30)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 1;
					break;
				case 2:
					if ((j < 3 || j > 33)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 2;
					break;
				case 3:
					if ((j < 6 || j > 35)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 5;
					break;
				case 4:
					if ((j < 1 || j > 31)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j;
					break;
				case 5:
					if ((j < 4 || j > 33)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 3;
					break;
				case 6:
					if ((j < 6 || j > 36)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 5;
					break;
				case 7:
					if ((j < 2 || j > 32)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 1;
					break;
				case 8:
					if ((j < 5 || j > 34)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 4;
					break;
				case 9:
					if ((j > 30)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j + 1;
					break;
				case 10:
					if ((j < 3 || j > 32)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 2;
					break;
				case 11:
					if ((j < 5 || j > 35)) break;
					_cal[i][j].isData = true;
					_cal[i][j].idY = j - 4;
					break;
			}
			_cal[i][j].idX = i + 1;
			_cal[i][j].rc = RectMake((i % 3) * 250 + 61 + 30 * (j % 7), 104 + 108 * (i / 3) + 16 * (j / 7), 30, 16);
		}
	}

	_img = IMAGEMANAGER->findImage("princessYellow");
}

void dataInput::CalRender()
{
	clickCal();

	if (!KEYMANAGER->isToggleKey(VK_TAB)) return;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 42; j++)
		{
			Rectangle(DC, _cal[i][j].rc.left, _cal[i][j].rc.top, _cal[i][j].rc.right, _cal[i][j].rc.bottom);
		}
	}
}

void dataInput::clickCal()
{
	if(_mode == PROLOGUE_CAL)
		IMAGEMANAGER->findImage("princessCal")->render(DC);
	if (_mode == PROLOGUE_DADCAL)
		IMAGEMANAGER->findImage("dadCal")->render(DC);

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 42; j++)
		{
			if (!PtInRect(&_cal[i][j].rc, _ptMouse) || !_cal[i][j].isData) continue;

			_img->render(DC,_cal[i][j].rc.left,_cal[i][j].rc.top, _cal[i][j].rc.left, _cal[i][j].rc.top, _cal[i][j].rc.right - _cal[i][j].rc.left, _cal[i][j].rc.bottom - _cal[i][j].rc.top);
			SetTextColor(DC, RGB(255, 255, 255));
			if (_mode == PROLOGUE_CAL)
				TextOut(DC, 33, 73, "1200", strlen("1200"));
			if (_mode == PROLOGUE_DADCAL)
				TextOut(DC, 33, 73, to_string(_dadYear).c_str(), strlen(to_string(_dadYear).c_str()));
			TextOut(DC, 83, 73, to_string(_cal[i][j].idX).c_str(), strlen(to_string(_cal[i][j].idX).c_str()));
			TextOut(DC, 112, 73, to_string(_cal[i][j].idY).c_str(), strlen(to_string(_cal[i][j].idY).c_str()));

			if (!KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) continue;
			if (_mode == PROLOGUE_CAL)
			{
				_princessInfo.year = 1200;
				_princessInfo.mon = _cal[i][j].idX;
				_princessInfo.day = _cal[i][j].idY;
			}
			if (_mode == PROLOGUE_DADCAL)
			{
			}

			changeMode();
			
			break;						
		}
	}
}

void dataInput::setDadAge()
{
	for (int i = 0; i < 10; i++)
	{
		_dadAgeArr[i].idX = i;
		_dadAgeArr[i].rc = RectMake(255 + i*30, 347, 20, 20);
	}

	_okBtn.rc = RectMake(168, 435, 45, 25);

	_img = IMAGEMANAGER->findImage("dadAgeYellow");
}

void dataInput::dadAgeRender()
{
	IMAGEMANAGER->findImage("dadAge")->render(DC);

	checkRender();
	
	for (int i = 0; i < 10; i++)
	{
		if (!PtInRect(&_dadAgeArr[i].rc, _ptMouse)) continue;

		_img->render(DC, _dadAgeArr[i].rc.left, _dadAgeArr[i].rc.top, _dadAgeArr[i].rc.left, _dadAgeArr[i].rc.top, _dadAgeArr[i].rc.right - _dadAgeArr[i].rc.left, _dadAgeArr[i].rc.bottom - _dadAgeArr[i].rc.top);
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_lDadAge.push_back(_dadAgeArr[i].idX);
			if (_lDadAge.size() > 2)
			{
				_lDadAge.pop_front();
			}
		}
		break;
	}

	if (PtInRect(&_okBtn.rc, _ptMouse))
	{
		_img->render(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.rc.left, _okBtn.rc.top, _okBtn.rc.right - _okBtn.rc.left, _okBtn.rc.bottom - _okBtn.rc.top);
	}

	int idx = 0;
	_lDadAgeIter = _lDadAge.begin();

	HFONT font, oldFont;
	font = CreateFont(20, 0, 0, 0, 20, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Britannic Bold"));
	oldFont = (HFONT)SelectObject(DC, font);
	SetTextColor(DC, RGB(190, 172, 76));
	for (; _lDadAgeIter != _lDadAge.end(); ++_lDadAgeIter)
	{
		TextOut(DC, 373 + (idx++)* 15, 304, to_string(*_lDadAgeIter).c_str(), strlen(to_string(*_lDadAgeIter).c_str()));
	}
	SelectObject(DC, oldFont);
	DeleteObject(font);
	SetTextColor(DC, RGB(0, 0, 0));
}

void dataInput::checkRender()
{
	if (!KEYMANAGER->isToggleKey(VK_F1)) return;
	
	for (int i = 0; i < 10; i++)
	{
		Rectangle(DC, _dadAgeArr[i].rc.left, _dadAgeArr[i].rc.top, _dadAgeArr[i].rc.right, _dadAgeArr[i].rc.bottom);
	}

	Rectangle(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.rc.right, _okBtn.rc.bottom);	
}

void dataInput::setDadCal()
{
	_img = IMAGEMANAGER->findImage("dadCalYellow");
	_dadYear = 1200 - _dadAge + 1;
}

void dataInput::dadCalRender()
{
	clickCal();

	if (!KEYMANAGER->isToggleKey(VK_TAB)) return;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 42; j++)
		{
			Rectangle(DC, _cal[i][j].rc.left, _cal[i][j].rc.top, _cal[i][j].rc.right, _cal[i][j].rc.bottom);
		}
	}
}