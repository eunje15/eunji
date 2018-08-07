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
	_back = IMAGEMANAGER->findImage("³ª¹«²Û¹è°æ");
	_friends.push_back(IMAGEMANAGER->findImage("³ª¹«²Û¼±»ý"));
	_friends.push_back(IMAGEMANAGER->findImage("³ª¹«²ÛÄ£±¸1"));
	_friends.push_back(IMAGEMANAGER->findImage("³ª¹«²ÛÄ£±¸2"));
	_princess = IMAGEMANAGER->findImage("³ª¹«²Û°øÁÖ");

	switch (RND->getInt(3))
	{
	case 0:
		_type = TEST_STUDY;
		_startF = 0, _endF = 4;
		_typeStr = "°øºÎÁß";
		break;
	case 1:
		_type = TEST_SLEEP;
		_startF = 0, _endF = 9;
		_typeStr = "Á¶´ÂÁß";
		break;
	case 2:
		_type = TEST_NOSTUDY;
		_startF = 11, _endF = 12;
		_typeStr = "³ó¶¯ÀÌ";
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
				_typeStr = "°øºÎÁß";
				break;
			case 1:
				_type = TEST_SLEEP;
				_startF = 0, _endF = 9;
				_typeStr = "Á¶´ÂÁß";
				break;
			case 2:
				_type = TEST_NOSTUDY;
				_startF = 11, _endF = 12;
				_typeStr = "³ó¶¯ÀÌ";
				break;
			}
			_frameX = _startF;
		}
		
	}
	if (_day == 10)
	{
		_typeStr = "³¡";
	}
}

void testClass::render()
{
	_back->render(DC, 0, 0);
	_friends[0]->frameRender(DC, 330, 20, _friends[0]->getFrameX(), 0);
	_friends[1]->frameRender(DC, 200, 43, _friends[1]->getFrameX(), 0);
	_friends[2]->frameRender(DC, 0, 43, _friends[2]->getFrameX(), 0);
	_princess->frameRender(DC, 80, 42, _frameX, 0);
	IMAGEMANAGER->findImage("³ª¹«²ÛÇ®")->render(DC, 0, 108);
	char str[128];
	sprintf_s(str, "%d %d", _ptMouse.x, _ptMouse.y);
	TextOut(DC, 700, 500, str, strlen(str));

	sprintf_s(str, "È½¼ö : %d", _day);
	TextOut(DC, 600, 500, str, strlen(str));
	TextOut(DC, 600, 550, _typeStr.c_str(), strlen(_typeStr.c_str()));
}

void testClass::release()
{
}
