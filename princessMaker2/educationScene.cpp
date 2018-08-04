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
	_dayOfWeek = (DAYOFWEEK)_princess->getDate().dayOfWeek;
	_day = _princess->getDate().day;
	
	_education = education;
	_eduName = _education->getName();
	_dayCount = dayCount;
	
	if (_eduName == "�ڿ�����")
		_type = EDU_SCHOOL;
	else if (_eduName == "�ù�")
		_type = EDU_POETRY;
	else if (_eduName == "����")
		_type = EDU_THEOLOGY;
	else if (_eduName == "������")
		_type = EDU_STRATEGY;
	else if (_eduName == "�˼�")
		_type = EDU_SWORDS;
	else if (_eduName == "������")
		_type = EDU_FIGHTING;
	else if (_eduName == "����")
		_type = EDU_MAGIC;
	else if (_eduName == "����")
		_type = EDU_SCIENCE;
	else if (_eduName == "����")
		_type = EDU_BALLET;
	else if (_eduName == "�̼�")
		_type = EDU_ART;

	initStatus();
	setImage();
	setTeachDialog();

	_gold = _education->getTuition();
	_success = _count = _frameCount = _dayIdx = 0;
	_frameX = _startF;
	_fin = false;
	_statusProgess = STATUS_START;
	string str = _princess->getInfo().name + "�� ���ú��� " + _eduName +  "�� ���ϴ�";
	setDialog(str);
	_dialogX = 20, _dialogY = WINSIZEY - 180;
	_dialogIdx = 0, _dialogType = DIALOG_ING;

	_princess->setGold(_gold);

	return S_OK;
}

void educationScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_statusProgess)
	{
	case STATUS_START:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_statusProgess = STATUS_TEACH;
			setDialog(_teachDialog);
			_dialogX = 190, _dialogY = 235;
			_dialogIdx = 0, _dialogType = DIALOG_ING;
		}
		break;
	case STATUS_TEACH:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_statusProgess = STATUS_ING;
			_dialogType = DIALOG_FIN;
			_dialogX = 450, _dialogY = 250;
		}
		break;
	case STATUS_ING:
		changeFrame();
		break;
	case STATUS_FIN:
		break;
	}
		
}

void educationScene::render()
{
		switch (_statusProgess)
		{
		case STATUS_START:
			IMAGEMANAGER->findImage("��������")->render(DC, 10, WINSIZEY - 190);
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			break;
		case STATUS_TEACH:
			IMAGEMANAGER->findImage("frame")->render(DC, 35, 225);
			IMAGEMANAGER->findImage("peopleFace")->frameRender(DC, 45, 235, 0, 4);
			IMAGEMANAGER->findImage("dialogFrame")->render(DC, 180, 225);
			if (dialogRender())
			{
				for (int i = 0; i < _vDialog.size(); i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			break;
		case STATUS_ING:
			IMAGEMANAGER->findImage("info2Back")->render(DC, 440, 238);
			if (dialogRender())
			{
				eduRender();
			}
			break;
		case STATUS_FIN:
			_fin = true;
			break;
		}
}

void educationScene::release()
{
}

void educationScene::initStatus()
{
	_pGold.str = "���ݾ�", _pGold.data = 0;

	_pGold.strRc = RectMake(10, 230, 80, 20);
	_pGold.dataRc = RectMake(90, 230, 30, 20);

	for (int i = 0; i < _education->getProperty().size(); i++)
	{
		_eduStatus.push_back(make_pair(_education->getProperty()[i].name, 0));
	}
}

void educationScene::setImage()
{
	string str = _eduName + "���";
	_back = IMAGEMANAGER->findImage(str);
	str = _eduName + "����";
	_princessImg = IMAGEMANAGER->findImage(str);
	_friends.clear();
	switch (_type)
	{
	case EDU_SCHOOL:
		_friends.push_back(IMAGEMANAGER->findImage("�ڿ����м���"));
		_friends.push_back(IMAGEMANAGER->findImage("�ڿ�����ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("�ڿ�����ģ��2"));

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
		_friends.push_back(IMAGEMANAGER->findImage("�ù�����"));
		_friends.push_back(IMAGEMANAGER->findImage("�ù�ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("�ù�ģ��2"));

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
		_friends.push_back(IMAGEMANAGER->findImage("���м���"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��3"));

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
		_friends.push_back(IMAGEMANAGER->findImage("�����м���"));
		_friends.push_back(IMAGEMANAGER->findImage("������ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("������ģ��2"));

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
		_friends.push_back(IMAGEMANAGER->findImage("�˼�����"));
		_friends.push_back(IMAGEMANAGER->findImage("�˼�ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("�˼�ģ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("�˼�ģ��3"));

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
		_friends.push_back(IMAGEMANAGER->findImage("����������"));
		_friends.push_back(IMAGEMANAGER->findImage("������ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("������ģ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("������ȶ��"));
		_friends.push_back(IMAGEMANAGER->findImage("�����������"));

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
		_friends.push_back(IMAGEMANAGER->findImage("��������"));
		_friends.push_back(IMAGEMANAGER->findImage("����ȶ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("����ȶ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��1"));

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
		_friends.push_back(IMAGEMANAGER->findImage("��������"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��3"));

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
		_friends.push_back(IMAGEMANAGER->findImage("���뼱��"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("����ģ��2"));

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
		_friends.push_back(IMAGEMANAGER->findImage("�̼�ģ��1"));
		_friends.push_back(IMAGEMANAGER->findImage("�̼�ģ��2"));
		_friends.push_back(IMAGEMANAGER->findImage("�̼�����"));

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

void educationScene::setTeachDialog()
{
	vector<string> vStr = TXTDATA->txtLoad("dialog/�������̾�α�.txt");
	_teachDialog = vStr[(int)_type];
}

void educationScene::changeFrame()
{
	if (_dayIdx >= _dayCount)
	{
		_statusProgess = STATUS_FIN;
		return;
	}
	_count++;
	if (!(_count % 20))
	{
		if (_dayOfWeek != SUN)
		{

		
		for (int i = 0; i < _friends.size(); i++)
		{
			if (_friends[i]->getFrameX() < _friends[i]->getMaxFrameX())
				_friends[i]->setFrameX(_friends[i]->getFrameX() + 1);
			else
				_friends[i]->setFrameX(0);
		}
		if (_frameX >= _endF)
		{
			_frameX = _startF;
			_frameCount++;
		}
		else
			_frameX++;
		}
		if (_frameCount == 3 || _dayOfWeek == SUN)
		{
			_day++;
			_princess->setDay(_day);
			_dayIdx++;
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
				setDialog("������ �Ͽ����Դϴ�.");
				_dialogIdx = 0;
				break;
			case SUN:
				_dayOfWeek = MON;
				break;
			}
			_princess->setDayOfWeek(int(_dayOfWeek));
			if (_dayOfWeek != MON)
			{
				if (_status == EDU_STUDY)
				{
					for (int i = 0; i < _education->getProperty().size(); i++)
					{
						int randNum;
						if (_eduStatus[i].first == "�׸���")
							randNum = RND->getInt(2);
						else
							randNum = RND->getFromIntTo(_education->getProperty()[i].startP, _education->getProperty()[i].endP);
						changeStatus(_eduStatus[i].first, randNum);
						if (_eduStatus[i].first == "�׸���")
							_eduStatus[i].second -= randNum;
						else
							_eduStatus[i].second += randNum;
					}
				}
				_princess->setGold(_gold);
				_pGold.data += _gold;
			}
			switch (_type)
			{
			case EDU_SCHOOL:
				switch (RND->getInt(3))
				{
				case 0:
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
					//setDialog("������ ������ ��Ÿ���� �ֽ��ϴ�.");
					//_dialogType = DIALOG_FIN;
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
}

void educationScene::changeStatus(string name, int value)
{
	if (name == "����")
		_princess->getStatusP()->intelligence += value;
	else if (name == "�������")
		_princess->getStatusP()->warriorSkill += value;
	else if (name == "�������")
		_princess->getStatusP()->magicSkill += value;
	else if (name == "��ǰ")
		_princess->getStatusP()->elegance += value;
	else if (name == "ü��")
		_princess->getStatusP()->hp += value;
	else if (name == "������")
		_princess->getStatusP()->sensitivity += value;
	else if (name == "�žӽ�")
		_princess->getStatusP()->faith += value;
	else if (name == "���ݷ�")
		_princess->getStatusP()->power += value;
	else if (name == "����")
		_princess->getStatusP()->defPower += value;
	else if (name == "����")
		_princess->getStatusP()->spell += value;
	else if (name == "���ǹ���")
		_princess->getStatusP()->manner += value;
	else if (name == "�ŷ�")
		_princess->getStatusP()->sexual += value;
	else if (name == "����")
		_princess->getStatusP()->art += value;
	else if (name == "�׸���")
	{
		if (value == 0)
			_princess->getStatusP()->spellDefence += 0;
		
		else
			_princess->getStatusP()->spellDefence += -1;
		
	}
}

void educationScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	/*if (_statusProgess == STATUS_ING)
	{
		string temp = _eduName + " " + to_string(_dayCount + 1) + "����";
		_vDialog.push_back(temp);
	}*/
	while (1)
	{
		if (strSize > 40)
		{
			_vDialog.push_back(str.substr(idx, 40));
			idx += 40;
			strSize -= 40;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

bool educationScene::dialogRender()
{
	if (_dialogType != DIALOG_ING) return true;

	if (_dialogIdx < _vDialog.size())
	{
		string temp = DIALOG->getCurrentDialog();
		if (temp == "end")
		{
			_dialogIdx++;
			if (_dialogIdx < _vDialog.size())
				DIALOG->setDialog(_vDialog[_dialogIdx], 5);
		}
		else
		{
			if (_dialogIdx > 0)
			{
				for (int i = 0; i < _dialogIdx; i++)
				{
					TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, _dialogX, _dialogY + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}

void educationScene::eduRender()
{
	IMAGEMANAGER->findImage("��������")->render(DC, 10, 240);
	int backX = 20, backY = 250;
	_back->render(DC, backX, backY);
	IMAGEMANAGER->findImage("storeQuit")->render(DC, 10, 190);

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(111, 17, 17));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	FillRect(DC, &_pGold.strRc, brush);
	Rectangle(DC, _pGold.strRc.left, _pGold.strRc.top, _pGold.strRc.right, _pGold.strRc.bottom);
	TextOut(DC, _pGold.strRc.left, _pGold.strRc.top + 2, _pGold.str.c_str(), strlen(_pGold.str.c_str()));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	Rectangle(DC, _pGold.dataRc.left, _pGold.dataRc.top, _pGold.dataRc.right, _pGold.dataRc.bottom);
	char str[128];
	sprintf_s(str, "%3dG", _pGold.data);
	TextOut(DC, _pGold.dataRc.left + 2, _pGold.dataRc.top + 2, str, strlen(str));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	if (_dayOfWeek == SUN)
	{
		TextOut(DC, 450, 250, "������ �Ͽ����Դϴ�.", strlen("������ �Ͽ����Դϴ�."));
		return;
	}
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

	string temp = _eduName + " " + to_string(_dayIdx + 1) + "����";
	TextOut(DC, 450, 250, temp.c_str(), strlen(temp.c_str()));
	char str2[128];
	switch (_status)
	{
	case EDU_STUDY:
		TextOut(DC, 445, 280, "������ ������ �巯���� �ֽ��ϴ�.", strlen("������ ������ �巯���� �ֽ��ϴ�."));
		sprintf_s(str2, "������ī��Ʈ :%d, ������", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	case EDU_SLEEP:
		sprintf_s(str2, "������ī��Ʈ :%d, �ڴ���", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	case EDU_NOSTUDY:
		sprintf_s(str2, "������ī��Ʈ :%d, ������", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	}
}
