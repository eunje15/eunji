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
	_back = IMAGEMANAGER->findImage("주점배경");
	_friends.push_back(IMAGEMANAGER->findImage("주점선생"));
	_friends.push_back(IMAGEMANAGER->findImage("주점친구1"));
	_friends.push_back(IMAGEMANAGER->findImage("주점친구2"));
	_friends.push_back(IMAGEMANAGER->findImage("주점친구3"));
	_princess = IMAGEMANAGER->findImage("주점공주");

	switch (RND->getInt(3))
	{
	case 0:
		_type = TEST_STUDY;
		_startF = 0, _endF = 7;
		_typeStr = "공부중";
		break;
	case 1:
		_type = TEST_SLEEP;
		_startF = 7, _endF = 17;
		_typeStr = "조는중";
		break;
	case 2:
		_type = TEST_NOSTUDY;
		_startF = 18, _endF = 19;
		_typeStr = "농땡이";
		break;
	}
	_day = _success = _count = _frameCount = 0;
	_gold = 10;
	_dayOfWeek = MON;
	_frameX = _startF;
	return S_OK;
}

void testClass::update()
{
	if (_day >= 10) return;
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
		if (_frameX >= _endF)
		{
			_frameCount++;
			_frameX = _startF;
		}
		else
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
				_type = TEST_STUDY;
				_startF = 0, _endF = 7;
				_typeStr = "공부중";
				break;
			case 1:
				_type = TEST_SLEEP;
				_startF = 7, _endF = 17;
				_typeStr = "조는중";
				break;
			case 2:
				_type = TEST_NOSTUDY;
				_startF = 18, _endF = 19;
				_typeStr = "농땡이";
				break;
			}
			_frameX = _startF;
		}
		
	}
	if (_day == 10)
	{
		_typeStr = "끝";
	}
}

void testClass::render()
{
	_back->render(DC, 0, 0);
	_friends[0]->frameRender(DC, 200, 0, _friends[0]->getFrameX(), 0);
	_friends[1]->frameRender(DC, 60, 17, _friends[1]->getFrameX(), 0);
	_friends[2]->frameRender(DC, 210, 42, _friends[2]->getFrameX(), 0);
	_friends[3]->frameRender(DC, 270, 43, _friends[3]->getFrameX(), 0);
	_princess->frameRender(DC, 300, 17, _frameX, 0);
	
	
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
