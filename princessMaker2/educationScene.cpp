#include "stdafx.h"
#include "educationScene.h"
#include "princess.h"


educationScene::educationScene()
{
}


educationScene::~educationScene()
{
}

HRESULT educationScene::init(status* education, int dayCount)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	
	_education = education;
	_eduName = _education->getName();
	_dayCount = dayCount;
	
	if (_eduName == "자연과학")
		_type = EDU_SCHOOL;
	else if (_eduName == "시문")
		_type = EDU_POETRY;
	else if (_eduName == "신학")
		_type = EDU_THEOLOGY;
	else if (_eduName == "군사학")
		_type = EDU_STRATEGY;
	else if (_eduName == "검술")
		_type = EDU_SWORDS;
	else if (_eduName == "격투술")
		_type = EDU_FIGHTING;
	else if (_eduName == "마법")
		_type = EDU_MAGIC;
	else if (_eduName == "예법")
		_type = EDU_SCIENCE;
	else if (_eduName == "무용")
		_type = EDU_BALLET;
	else if (_eduName == "미술")
		_type = EDU_ART;

	setImage();

	_gold = _education->getTuition();
	_day = _success = _count = _frameCount = 0;
	_dayOfWeek = MON;
	_frameX = _startF;
	_start = _fin = false;

	return S_OK;
}

void educationScene::update()
{
	if (!_start)
	{

	}
	else
	{
		switch (_type)
		{
		case EDU_SCHOOL:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 2;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 3, _endF = 4;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				break;
			}
			break;
		case EDU_POETRY:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 3;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 4, _endF = 7;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 8, _endF = 9;
				break;
			}
			break;
		case EDU_THEOLOGY:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 1;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 2, _endF = 3;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 4, _endF = 5;
				break;
			}
			break;
		case EDU_STRATEGY:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 2;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 3, _endF = 4;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				break;
			}
			break;
		case EDU_SWORDS:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 3;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 4, _endF = 5;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 6, _endF = 7;
				break;
			}
			break;
		case EDU_FIGHTING:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 2;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 3, _endF = 4;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				break;
			}
			break;
		case EDU_MAGIC:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 7;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 8, _endF = 11;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 12, _endF = 13;
				break;
			}
			break;
		case EDU_SCIENCE:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 2;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 3, _endF = 4;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				break;
			}
			break;
		case EDU_BALLET:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 3;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 4, _endF = 5;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 6, _endF = 7;
				break;
			}
			break;
		case EDU_ART:
			switch (RND->getInt(3))
			{
			case 0:
				_status = EDU_STUDY;
				_startF = 0, _endF = 2;
				break;
			case 1:
				_status = EDU_SLEEP;
				_startF = 3, _endF = 4;
				break;
			case 2:
				_status = EDU_NOSTUDY;
				_startF = 5, _endF = 6;
				break;
			}
			break;
		}
	}
}

void educationScene::render()
{
	int backX = 10, backY = 200;
	_back->render(DC, backX, backY);
	switch (_type)
	{
	case EDU_SCHOOL:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 19 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_POETRY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 19 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_THEOLOGY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 140 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_STRATEGY:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 50 + backX, 19 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 60 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 300 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_SWORDS:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 175 + backX, 10 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);

		break;
	case EDU_FIGHTING:
		for (int i = 0; i < _friends.size() - 1; i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 175 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 350 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_friends[_friends.size() - 1]->render(DC, 260 + backX, 42 + backY);
		_princessImg->frameRender(DC, 260 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_MAGIC:
		for (int i = 1; i < _friends.size() - 1; i++)
		{
			_friends[i]->frameRender(DC, 88 + (i - 1) * 202 + backX, 0 + backY, _friends[i]->getFrameX(), 0);
		}
		_friends[0]->frameRender(DC, 152 + backX, 42 + backY, _friends[0]->getFrameX(), 0);
		_friends[_friends.size() - 1]->frameRender(DC, 70 + backX, 42 + backY, _friends[_friends.size() - 1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 280 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_SCIENCE:
		for (int i = 0; i < _friends.size(); i++)
		{
			if (i == 0)
				_friends[i]->frameRender(DC, 180 + backX, 28 + backY, _friends[i]->getFrameX(), 0);
			else if (i == 3)
				_friends[i]->frameRender(DC, 340 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
			else
				_friends[i]->frameRender(DC, 10 + (i - 1) * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 269 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_BALLET:
		for (int i = 0; i < _friends.size(); i++)
		{
			_friends[i]->frameRender(DC, 50 + i * 80 + backX, 42 + backY, _friends[i]->getFrameX(), 0);
		}
		_princessImg->frameRender(DC, 310 + backX, 42 + backY, _frameX, 0);
		break;
	case EDU_ART:
		_friends[0]->frameRender(DC, 89 + backX, 43 + backY, _friends[0]->getFrameX(), 0);
		_friends[1]->frameRender(DC, 160 + backX, 42 + backY, _friends[1]->getFrameX(), 0);
		_friends[_friends.size() - 1]->frameRender(DC, 310 + backX, 42 + backY, _friends[_friends.size() - 1]->getFrameX(), 0);
		_princessImg->frameRender(DC, 10 + backX, 42 + backY, _frameX, 0);
		break;
	}
}

void educationScene::release()
{
}

void educationScene::setImage()
{
	string str = _eduName + "배경";
	_back = IMAGEMANAGER->findImage(str);
	str = _eduName + "공주";
	_princessImg = IMAGEMANAGER->findImage(str);

	switch (_type)
	{
	case EDU_SCHOOL:
		_friends.push_back(IMAGEMANAGER->findImage("자연과학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("자연과학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("자연과학친구2"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
			break;
		}
		break;
	case EDU_POETRY:
		_friends.push_back(IMAGEMANAGER->findImage("시문선생"));
		_friends.push_back(IMAGEMANAGER->findImage("시문친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("시문친구2"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 4, _endF = 7;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 8, _endF = 9;
			break;
		}
		break;
	case EDU_THEOLOGY:
		_friends.push_back(IMAGEMANAGER->findImage("신학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("신학친구3"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 1;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 2, _endF = 3;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 4, _endF = 5;
			break;
		}
		break;
	case EDU_STRATEGY:
		_friends.push_back(IMAGEMANAGER->findImage("군사학선생"));
		_friends.push_back(IMAGEMANAGER->findImage("군사학친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("군사학친구2"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
			break;
		}
		break;
	case EDU_SWORDS:
		_friends.push_back(IMAGEMANAGER->findImage("검술선생"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("검술친구3"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 4, _endF = 5;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 6, _endF = 7;
			break;
		}
		break;
	case EDU_FIGHTING:
		_friends.push_back(IMAGEMANAGER->findImage("격투술선생"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술횃불"));
		_friends.push_back(IMAGEMANAGER->findImage("격투술막대기"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
			break;
		}
		break;
	case EDU_MAGIC:
		_friends.push_back(IMAGEMANAGER->findImage("마법선생"));
		_friends.push_back(IMAGEMANAGER->findImage("마법횃불1"));
		_friends.push_back(IMAGEMANAGER->findImage("마법횃불2"));
		_friends.push_back(IMAGEMANAGER->findImage("마법친구1"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 7;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 8, _endF = 11;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 12, _endF = 13;
			break;
		}
		break;
	case EDU_SCIENCE:
		_friends.push_back(IMAGEMANAGER->findImage("예법선생"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("예법친구3"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
			break;
		}
		break;
	case EDU_BALLET:
		_friends.push_back(IMAGEMANAGER->findImage("발레선생"));
		_friends.push_back(IMAGEMANAGER->findImage("발레친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("발레친구2"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 3;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 4, _endF = 5;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 6, _endF = 7;
			break;
		}
		break;
	case EDU_ART:
		_friends.push_back(IMAGEMANAGER->findImage("미술친구1"));
		_friends.push_back(IMAGEMANAGER->findImage("미술친구2"));
		_friends.push_back(IMAGEMANAGER->findImage("미술선생"));

		switch (RND->getInt(3))
		{
		case 0:
			_status = EDU_STUDY;
			_startF = 0, _endF = 2;
			break;
		case 1:
			_status = EDU_SLEEP;
			_startF = 3, _endF = 4;
			break;
		case 2:
			_status = EDU_NOSTUDY;
			_startF = 5, _endF = 6;
			break;
		}
		break;
	}
}
