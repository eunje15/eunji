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
	_back = IMAGEMANAGER->findImage("广狼林痢硅版");
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢急积"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备1"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备2"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备3"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备4"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备5"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢模备6"));
	_friends.push_back(IMAGEMANAGER->findImage("广狼林痢眯阂"));
	_princess = IMAGEMANAGER->findImage("广狼林痢傍林");

	switch (RND->getInt(3))
	{
	case 0:
		_type = TEST_STUDY;
		_startF = 0, _endF = 3;
		_typeStr = "傍何吝";
		break;
	case 1:
		_type = TEST_SLEEP;
		_startF = 4, _endF = 7;
		_typeStr = "炼绰吝";
		break;
	case 2:
		_type = TEST_NOSTUDY;
		_startF = 4, _endF = 7;
		_typeStr = "丑动捞";
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
				_startF = 0, _endF = 3;
				_typeStr = "傍何吝";
				break;
			case 1:
				_type = TEST_SLEEP;
				_startF = 4, _endF = 7;
				_typeStr = "炼绰吝";
				break;
			case 2:
				_type = TEST_NOSTUDY;
				_startF = 4, _endF = 7;
				_typeStr = "丑动捞";
				break;
			}
			_type = TEST_NOSTUDY;
			_startF = 4, _endF = 7;
			_typeStr = "丑动捞";
			_frameX = _startF;
		}
		
	}
	if (_day == 10)
	{
		_typeStr = "场";
	}
}

void testClass::render()
{
	_back->render(DC, 0, 0);
	_friends[0]->frameRender(DC, 0, 42, _friends[0]->getFrameX(), 0);
	_friends[1]->frameRender(DC, 70, 42, _friends[1]->getFrameX(), 0);
	_friends[2]->frameRender(DC, 115, 42, _friends[2]->getFrameX(), 0);
	_friends[3]->frameRender(DC, 145, 43, _friends[3]->getFrameX(), 0);
	_friends[4]->frameRender(DC, 270, 42, _friends[4]->getFrameX(), 0);
	_friends[5]->frameRender(DC, 300, 42, _friends[5]->getFrameX(), 0);
	_friends[6]->frameRender(DC, 200, 0, _friends[6]->getFrameX(), 0);
	_friends[7]->frameRender(DC, 70, 0, _friends[7]->getFrameX(), 0);
	_princess->frameRender(DC, 330, 42, _frameX, 0);
	
	
	char str[128];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 700, 500, str, strlen(str));

	sprintf_s(str, "冉荐 : %d", _day);
	TextOut(DC, 600, 500, str, strlen(str));
	TextOut(DC, 600, 550, _typeStr.c_str(), strlen(_typeStr.c_str()));
}

void testClass::release()
{
}
