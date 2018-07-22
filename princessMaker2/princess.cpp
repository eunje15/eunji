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
	_info.firstName = "��";
	_info.name = "������";
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
			_status.god.constellation = "�����ڸ�";
		else
			_status.god.constellation = "�����ڸ�";
		break;
	case 2:
		if (_info.day <= 18)
			_status.god.constellation = "�����ڸ�";
		else
			_status.god.constellation = "������ڸ�";
		break;
	case 3:
		if (_info.day <= 20)
			_status.god.constellation = "������ڸ�";
		else
			_status.god.constellation = "���ڸ�";
		break;
	case 4:
		if (_info.day <= 19)
			_status.god.constellation = "���ڸ�";
		else
			_status.god.constellation = "Ȳ���ڸ�";
		break;
	case 5:
		if (_info.day <= 20)
			_status.god.constellation = "Ȳ���ڸ�";
		else
			_status.god.constellation = "�ֵ����ڸ�";
		break;
	case 6:
		if (_info.day <= 21)
			_status.god.constellation = "�ֵ����ڸ�";
		else
			_status.god.constellation = "���ڸ�";
		break;
	case 7:
		if (_info.day <= 22)
			_status.god.constellation = "���ڸ�";
		else
			_status.god.constellation = "�����ڸ�";
		break;
	case 8:
		if (_info.day <= 22)
			_status.god.constellation = "�����ڸ�";
		else
			_status.god.constellation = "ó���ڸ�";
		break;
	case 9:
		if (_info.day <= 22)
			_status.god.constellation = "ó���ڸ�";
		else
			_status.god.constellation = "õĪ�ڸ�";
		break;
	case 10:
		if (_info.day <= 23)
			_status.god.constellation = "õĪ�ڸ�";
		else
			_status.god.constellation = "�����ڸ�";
		break;
	case 11:
		if (_info.day <= 22)
			_status.god.constellation = "�����ڸ�";
		else
			_status.god.constellation = "����ڸ�";
		break;
	case 12:
		if (_info.day <= 21)
			_status.god.constellation = "����ڸ�";
		else
			_status.god.constellation = "�����ڸ�";
		break;
	}
	vector<string> vStr = TXTDATA->txtLoadCsv("dialog/���ڸ��ɷ�ġ.csv", _status.god.constellation.c_str());

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