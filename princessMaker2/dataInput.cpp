#include "stdafx.h"
#include "dataInput.h"


dataInput::dataInput()
{
}


dataInput::~dataInput()
{
}

HRESULT dataInput::init()
{
	_mode = PROLOGUE_DADNAME;
	setDadName();
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
			_mode = PROLOGUE_NAME;
			//_dadName = _inputData.end();
		}
	}
	else
		_okBtn.idX = 0;
}

void dataInput::render()
{
	char str[128];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 100, 100, str, strlen(str));
	
	switch (_mode)
	{
	case PROLOGUE_DADNAME:
		setDadNameRender();
		break;
	case PROLOGUE_DADCAL:
		break;
	case PROLOGUE_NAME:
		break;
	case PROLOGUE_CAL:
		break;
	case PROLOGUE_BLOOD:
		break;
	case PROLOGUE_DIALOG:
		break;
	}
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
	_inputData.clear();
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
		TextOut(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 + 5, str.c_str(), strlen(str.c_str()));
	}
	IMAGEMANAGER->findImage("아빠완료")->frameRender(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.idX, 0);
}
void dataInput::setPrincessName()
{
	_isInput = true;
	_back = IMAGEMANAGER->findImage("princessName");
	_okBtn.rc = RectMake(510, WINSIZEY / 2, 68, 37);
	_okBtn.isSelected = _okBtn.idX = _okBtn.idY = 0;
	_inputData.clear();
}

void dataInput::setPrincessNameRender()
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
		TextOut(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 + 5, str.c_str(), strlen(str.c_str()));
	}
	IMAGEMANAGER->findImage("딸완료")->frameRender(DC, _okBtn.rc.left, _okBtn.rc.top, _okBtn.idX, 0);
}