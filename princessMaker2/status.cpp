#include "stdafx.h"
#include "status.h"


status::status()
{
}


status::~status()
{
}

HRESULT status::init()
{
	return S_OK;
}

void status::update()
{
}

void status::render()
{
	_img->frameRender(DC, _x, _y, _frameX, _frameY);
}

void status::release()
{
}

void status::setStatus(string name, string teacher, int tuition, int plus, vector<tagStatusData> property, int type, int frameX, int frameY)
{
	_name = name;
	_teacher = teacher;
	_tuition = tuition;
	_property = property;
	_type = (STATUS_TYPE)type;
	_frameX = frameX;
	_frameY = frameY;
	_step = 0;
	setImage();
}

void status::setImage()
{
	switch (_type)
	{
	case STATUS_TEACH:
		_img = IMAGEMANAGER->findImage("teachImg");
		break;
	case STATUS_WORK:
		_img = IMAGEMANAGER->findImage("workImg");
		break;
	case STATUS_FIGHT:
		_img = IMAGEMANAGER->findImage("fightImg");
		break;
	case STATUS_RELAX:
		_img = IMAGEMANAGER->findImage("relaxImg");
		break;
	}
}

void status::upgradeStep()
{
	if(_step < 4)
		_step += 1;
}

string status::getStringStep()
{
	if (_step == 0)
		return "초급";
	if (_step == 1)
		return "중급";
	if (_step == 2)
		return "상급";
	if (_step == 3)
		return "고급";
}
