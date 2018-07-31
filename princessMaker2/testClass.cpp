#include "stdafx.h"
#include "testClass.h"


testClass::testClass()
{
}


testClass::~testClass()
{
}

HRESULT testClass::init()
{
	/*_back = IMAGEMANAGER->findImage("미술배경");
	_friends.push_back(IMAGEMANAGER->findImage("미술친구1"));
	_friends.push_back(IMAGEMANAGER->findImage("미술친구2"));
	_friends.push_back(IMAGEMANAGER->findImage("미술선생"));
	_princess = IMAGEMANAGER->findImage("미술공주");

	switch (RND->getInt(3))
	{
	case 0:
		_type = EDU_STUDY;
		_startF = 0, _endF = 2;
		_typeStr = "공부중";
		break;
	case 1:
		_type = EDU_SLEEP;
		_startF = 3, _endF = 4;
		_typeStr = "조는중";
		break;
	case 2:
		_type = EDU_NOSTUDY;
		_startF = 5, _endF = 6;
		_typeStr = "농땡이";
		break;
	}
	_day = _success = _count = _frameCount = 0;
	_gold = 10;
	_dayOfWeek = MON;
	_frameX = _startF;*/
	return S_OK;
}

void testClass::update()
{
	/*if (_day >= 10) return;
	_count++;
	if (!(_count % 30))
	{
		_count = 0;
		for (int i = 0; i < _friends.size(); i++)
		{
			if (_friends[i]->getFrameX() < _friends[i]->getMaxFrameX())
				_friends[i]->setFrameX(_friends[i]->getFrameX() + 1);
			else
				_friends[i]->setFrameX(0);
		}
		_frameCount++;
		if (_frameX >= _endF) _frameX = _startF;
		_frameX++;
		if (_frameCount == 3)
		{
			_day++;
			_frameCount = 0;
			switch (_dayOfWeek)
			{
			case MON:
				_dayOfWeek = TUE;
				break;
			case TUE:
				_dayOfWeek = WED;
				break;
			case WED:
				_dayOfWeek = THU;
				break;
			case THU:
				_dayOfWeek = FRI;
				break;
			case FRI:
				_dayOfWeek = SAT;
				break;
			case SAT:
				_dayOfWeek = SUN;
				break;
			case SUN:
				_dayOfWeek = MON;
				break;
			}
			switch (RND->getInt(3))
			{
			case 0:
				_type = EDU_STUDY;
				_startF = 0, _endF = 2;
				_typeStr = "공부중";
				break;
			case 1:
				_type = EDU_SLEEP;
				_startF = 3, _endF = 4;
				_typeStr = "조는중";
				break;
			case 2:
				_type = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				_typeStr = "농땡이";
				break;
			}
		}
		
	}
	if (_day == 10)
	{
		_typeStr = "끝";
	}*/
}

void testClass::render()
{
	_back->render(DC, 0, 0);
	for (int i = 0; i < _friends.size() - 1; i++)
	{
		
	}
	_friends[0]->frameRender(DC, 89, 43, _friends[0]->getFrameX(), 0);
	_friends[1]->frameRender(DC, 160, 42, _friends[1]->getFrameX(), 0);
	_friends[_friends.size() - 1]->frameRender(DC, 310, 42, _friends[_friends.size() - 1]->getFrameX(), 0);
	_princess->frameRender(DC, 10, 42, _frameX, 0);
	char str[128];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 700, 500, str, strlen(str));

	sprintf_s(str, "횟수 : %d", _day);
	TextOut(DC, 600, 500, str, strlen(str));
	TextOut(DC, 600, 550, _typeStr.c_str(), strlen(_typeStr.c_str()));
}

void testClass::release()
{
}
