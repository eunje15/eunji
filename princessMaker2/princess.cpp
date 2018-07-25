#include "stdafx.h"
#include "princess.h"


princess::princess()
{
}


princess::~princess()
{
}

HRESULT princess::init()
{
	_info.firstName = "윤";
	_info.name = "딸래미";
	_info.year = 1200, _info.mon = 2, _info.day = 28;
	_info.blood = BLOOD_A;
	_info.strBlood = "A";
	_info.age = _age = 11;
	setStatus();
	char str[128];
	sprintf_s(str, "body%d", _age);
	_body.img = IMAGEMANAGER->findImage(str);
	_body.x = 80;
	_body.y = WINSIZEY - _body.img->getFrameHeight();
	
	sprintf_s(str, "face%d", _age);
	_face.img = IMAGEMANAGER->findImage(str);
	_face.x = 80;
	_face.y = _body.y - _face.img->getFrameHeight() + 1;

	_gold = 1000;

	return S_OK;
}

void princess::update()
{
}

void princess::render()
{
	_body.img->frameRender(DC, _body.x, _body.y);
	_face.img->frameRender(DC, _face.x, _face.y);
}

void princess::release()
{
}

void princess::setStatus()
{
	switch (_info.mon)
	{
	case 1:
		if (_info.day <= 19)
			_status.god.constellation = "염소자리", _status.god.idx = 0;
		else
			_status.god.constellation = "물병자리", _status.god.idx = 1;
		break;
	case 2:
		if (_info.day <= 18)
			_status.god.constellation = "물병자리", _status.god.idx = 1;
		else
			_status.god.constellation = "물고기자리", _status.god.idx = 2;
		break;
	case 3:
		if (_info.day <= 20)
			_status.god.constellation = "물고기자리", _status.god.idx = 2;
		else
			_status.god.constellation = "양자리", _status.god.idx = 3;
		break;
	case 4:
		if (_info.day <= 19)
			_status.god.constellation = "양자리", _status.god.idx = 3;
		else
			_status.god.constellation = "황소자리", _status.god.idx = 4;
		break;
	case 5:
		if (_info.day <= 20)
			_status.god.constellation = "황소자리", _status.god.idx = 4;
		else
			_status.god.constellation = "쌍둥이자리", _status.god.idx = 5;
		break;
	case 6:
		if (_info.day <= 21)
			_status.god.constellation = "쌍둥이자리", _status.god.idx = 5;
		else
			_status.god.constellation = "게자리", _status.god.idx = 6;
		break;
	case 7:
		if (_info.day <= 22)
			_status.god.constellation = "게자리", _status.god.idx = 6;
		else
			_status.god.constellation = "사자자리", _status.god.idx = 7;
		break;
	case 8:
		if (_info.day <= 22)
			_status.god.constellation = "사자자리", _status.god.idx = 7;
		else
			_status.god.constellation = "처녀자리", _status.god.idx = 5;
		break;
	case 9:
		if (_info.day <= 22)
			_status.god.constellation = "처녀자리", _status.god.idx = 5;
		else
			_status.god.constellation = "천칭자리", _status.god.idx = 4;
		break;
	case 10:
		if (_info.day <= 23)
			_status.god.constellation = "천칭자리", _status.god.idx = 4;
		else
			_status.god.constellation = "전갈자리", _status.god.idx = 8;
		break;
	case 11:
		if (_info.day <= 22)
			_status.god.constellation = "전갈자리", _status.god.idx = 8;
		else
			_status.god.constellation = "사수자리", _status.god.idx = 9;
		break;
	case 12:
		if (_info.day <= 21)
			_status.god.constellation = "사수자리", _status.god.idx = 9;
		else
			_status.god.constellation = "염소자리", _status.god.idx = 0;
		break;
	}
	vector<string> vStr = TXTDATA->txtLoadCsv("dialog/별자리능력치.csv", _status.god.constellation.c_str());

	_status.god.planet = vStr[0];
	_status.god.name = vStr[1];

	_status.hp = atoi(vStr[3].c_str());
	_status.physical = atoi(vStr[4].c_str());
	_status.intelligence = atoi(vStr[5].c_str());
	_status.elegance = atoi(vStr[6].c_str());
	_status.sexual = atoi(vStr[7].c_str());
	_status.morality = atoi(vStr[8].c_str());
	_status.faith = atoi(vStr[9].c_str());
	_status.sensitivity = atoi(vStr[10].c_str());
	_status.warrior = atoi(vStr[11].c_str());
	_status.warriorSkill = atoi(vStr[12].c_str());
	_status.power = atoi(vStr[13].c_str());
	_status.magic = atoi(vStr[14].c_str());
	_status.magicSkill = atoi(vStr[15].c_str());
	_status.spell = atoi(vStr[16].c_str());
	_status.spellDefence = atoi(vStr[17].c_str());
	_status.sociality = atoi(vStr[18].c_str());
	_status.manner = atoi(vStr[19].c_str());
	_status.art = atoi(vStr[20].c_str());
	_status.conversation = atoi(vStr[21].c_str());
	_status.housework = atoi(vStr[22].c_str());
	_status.cooking = atoi(vStr[23].c_str());
	_status.cleaning = atoi(vStr[24].c_str());
	_status.personality = atoi(vStr[25].c_str());
	_status.total = atoi(vStr[26].c_str());
	_status.plusNorth = vStr[27];
}

void princess::setStress(int stress)
{
	_status.stress -= stress; 
	if (_status.stress < 0) _status.stress = 0;
}
