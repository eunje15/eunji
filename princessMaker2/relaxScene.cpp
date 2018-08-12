#include "stdafx.h"
#include "relaxScene.h"
#include "princess.h"

relaxScene::relaxScene()
{
}


relaxScene::~relaxScene()
{
}

HRESULT relaxScene::init(relaxStatus * relax, int dayCount)
{
	_princess = SCENEMANAGER->getPrincessAddress();

	_relax = relax;
	_status = RELAX_SELECT;
	_dayCount = dayCount;

	for (int i = 0; i < 2; i++)
	{
		_selectBox[i].rc = RectMake(600, 330 + i * 28, 120, 28);
		_selectBox[i].isChoose = _selectBox[i].isSelected = false;
	}
	if (_type == RELAX_FREE)
	{
		setDialog("�뵷�� �ֽðڽ��ϱ�?");
		_selectBox[0].str = "�ش�";
		_selectBox[1].str = "�����ʴ´�";
	}
	else
	{
		setDialog("���� ���ðڽ��ϱ�?");
		_selectBox[0].str = "��";
		_selectBox[1].str = "�ٴ�";
	}
	_dialogIdx = 0;
	_dialogType = DIALOG_ING;

	_fin = _moneyOk = false;
	_princessAnswer = -1;
	return S_OK;
}

void relaxScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_status)
	{
	case RELAX_SELECT:
		for (int i = 0; i < 2; i++)
		{
			_selectBox[i].isSelected = false;
			if (PtInRect(&_selectBox[i].rc, _ptMouse))
			{
				_selectBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					setRelax(i);
					if (i == 1 && _type == RELAX_FREE)
					{
						_princessAnswer = 0;
						setDialog("�ٳ���ڽ��ϴ�");
						_dialogIdx = 0;
						_dialogType = DIALOG_ING;
					}
				}
			}
		}
		break;
	case RELAX_OK:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_princessAnswer == -1 && _type == RELAX_FREE)
			{
				setDialog("�ٳ���ڽ��ϴ�.");
				_dialogIdx = 0;
				_dialogType = DIALOG_ING;
				_princessAnswer = 0;
			}
			else if (_princessAnswer == 0)
			{
				string str = "";
				if (_moneyOk)
					str = _princess->getInfo().name + "�� �Ÿ��� ��������ϴ�.";
				else
					str = _princess->getInfo().name + "���� �뵷���� �Ÿ��� ��������ϴ�.";
				_princessAnswer = 1;
				_dialogIdx = 0;
				_dialogType = DIALOG_ING;
			}
			else
				_status = RELAX_ING;
		}
		break;
	case RELAX_FAIL:
		break;
	case RELAX_ING:
		_count++;
		if (!(_count % 30))
		{
			changeDay();
		}
		break;
	case RELAX_FIN:
		break;
	}
}

void relaxScene::render()
{
	switch (_status)
	{
	case RELAX_SELECT:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
			IMAGEMANAGER->findImage("2Back")->render(DC, 590, 315);
			for (int i = 0; i < 2; i++)
			{
				if (_selectBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_selectBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _selectBox[i].rc.left + 2, _selectBox[i].rc.top + 5, _selectBox[i].str.c_str(), strlen(_selectBox[i].str.c_str()));
			}
		}
		break;
	case RELAX_OK:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	case RELAX_FAIL:
		IMAGEMANAGER->findImage("wideBack")->render(DC, 10, 430);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		break;
	case RELAX_ING:
		if (_type == RELAX_FREE)
		{

		}
		else
		{

		}
		break;
	case RELAX_FIN:
		break;
	}
}

void relaxScene::release()
{
}

void relaxScene::setRelax(int idx)
{
	_relax->getRelaxIdx(idx);
	if (_type == RELAX_FREE)
	{
		if (idx == 0)
		{
			if (_princess->getGold() >= _princess->getInfo().age*_dayCount)
			{
				_moneyOk = true;
				string str = _princess->getInfo().name + "���� �뵷 " + to_string(_relax->getGold()*_dayCount) + "G�� ����ϴ�.";
				setDialog(str);
				_dialogIdx = 0;
				_princess->getStatusP()->withFather += 3;
				initStatus(1);
				_princess->setGold(_princess->getInfo().age*_dayCount);
				_status = RELAX_OK;
			}
			else
			{
				//���߿� ť��� �ٲ��
				string str = "�������� ������ �뵷�� �ִ� ���� �����Դϴ�.";
				setDialog(str);
				_dialogIdx = 0;
				initStatus(0);
				_status = RELAX_FAIL;
			}
		}
	}
	else
	{
		if (_princess->getGold() >= _dayCount*_princess->getInfo().age)
		{
			SEASON_TYPE season = _princess->getSeason();
			string str = "�γ�� �Բ� ";
			switch (season)
			{
			case SPRING:
				str += "���� ";
				break;
			case SUMMER:
				str += "������ ";
				break;
			case AUTUMN:
				str += "������ ";
				break;
			case WINTER:
				str += "�ܿ��� ";
				break;
			}
			if (idx == 0)
				str += "������ �����...";
			else
				str == "�ٴٷ� �����...";
			setDialog(str);
			_dialogIdx = 0;
			_dialogType = DIALOG_ING;
			initStatus(2);
			_status = RELAX_OK;
		}
		else
		{
			string str = "��Ĳ���� �� ���� �����ϴ�";
			setDialog(str);
			_dialogIdx = 0;
			initStatus(3);
			_status = RELAX_FAIL;
		}
	}
}

void relaxScene::initStatus(int idx)
{
	_relaxStatus.clear();
	_vPStatus.clear();

	if (idx == 0 || idx == 1)//��Ʈ������
	{
		if(idx == 0)
			_relaxStatus.push_back(make_pair("��Ʈ����", -5));
		else
			_relaxStatus.push_back(make_pair("��Ʈ����", -10));

		image* img = new image;
		img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;

		temp.str = "��Ʈ����";
		temp.data = _princess->getStatus().stress;

		temp.strRc = RectMake(500, 440, 80, 25);
		temp.dataRc = RectMake(580, 440, 30, 25);

		temp.progressBar = new progressBar;
		temp.progressBar->init(610, 440, 110, 20);
		temp.progressBar->setGauge(temp.data, 500);

		_vPStatus.push_back(make_pair(img, temp));
	}
	else if (idx == 2) //��Ĳ������
	{
		for (int i = 0; i < 3; i++)
		{
			image* img = new image;
			img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

			tagProgress temp;

			if (i == 0)
			{
				_relaxStatus.push_back(make_pair("��Ʈ����", _relaxInfo.stress));

				temp.str = "��Ʈ����";
				temp.data = _princess->getStatus().stress;
			}
			else if (i == 1)
			{
				if (_relaxInfo.sensitivity == 0)
				{
					if (_relaxInfo.weight == 0)
						break;
					else
					{
						_relaxStatus.push_back(make_pair("������", _relaxInfo.weight));
						temp.str = "������";
						temp.data = _princess->getBodyInfo().weight;
					}
				}
				else 
				{
					_relaxStatus.push_back(make_pair("������", _relaxInfo.sensitivity));
					temp.str = "������";
					temp.data = _princess->getStatus().sensitivity;
				}
			}
			else
			{
				_relaxStatus.push_back(make_pair("������", _relaxInfo.weight));
				temp.str = "������";
				temp.data = _princess->getBodyInfo().weight;
			}

			temp.strRc = RectMake(50 + 280 * (i), 440, 80, 25);
			temp.dataRc = RectMake(130 + 280 * (i), 440, 30, 25);

			temp.progressBar = new progressBar;
			temp.progressBar->init(160 + 280 * (i % 2), 440, 110, 20);
			temp.progressBar->setGauge(temp.data, 500);

			_vPStatus.push_back(make_pair(img, temp));

			if (i == 0 && temp.str == "������") break;
		}
	}
	else //��븸
	{
		image* img = new image;
		img->init("image/education/progressBack(300x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;

		temp.str = "���";
		temp.data = _dayCount * _princess->getInfo().age;

		temp.strRc = RectMake(500, 300, 80, 25);
		temp.dataRc = RectMake(580, 300, 30, 25);

		_vPStatus.push_back(make_pair(img, temp));
	}
}

int relaxScene::changeStatus(string name, int value)
{
	int temp;
	if (name == "��Ʈ����")
	{
		_princess->getStatusP()->stress += value;
		if (_princess->getStatus().stress < 0)
			_princess->getStatusP()->stress = 0;
		temp = _princess->getStatus().stress;
	}
	else if (name == "������")
	{
		_princess->getStatusP()->sensitivity += value;
		if (_princess->getStatus().sensitivity < 0)
			_princess->getStatusP()->sensitivity = 0;
		temp = _princess->getStatus().sensitivity;
	}
	else if (name == "������")
	{
		_princess->getBodyInfoP()->weight += value;
		if (_princess->getBodyInfo().weight < 0)
			_princess->getBodyInfoP()->weight = 0;
		temp = _princess->getBodyInfo().weight;
	}
	return temp;
}

void relaxScene::changeDay()
{
	_count = 0;

	if (_dayIdx < _dayCount)
	{
		_day++;
		_dayIdx++;
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
		_princess->setDay(_day);
		_princess->setDayOfWeek(_dayOfWeek);
		for (int i = 0; i < _vPStatus.size(); i++)
		{
			int temp = changeStatus(_relaxStatus[i].first, _relaxStatus[i].second);
			_vPStatus[i].second.progressBar->setGauge(temp, 500);
		}
	}
	else
	{
		_clickHome.str = "������ ���ư��ϴ�.";
		_clickHome.isSelected = false;
		_clickHome.rc = RectMake(400, 400, 100, 20);
		_status = RELAX_FIN;
	}
}

void relaxScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	_vDialog.clear();
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


bool relaxScene::dialogRender()
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
					TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
				}
			}
			TextOut(DC, 20, 440 + _dialogIdx * 30, temp.c_str(), strlen(temp.c_str()));
		}
	}
	else
	{
		_dialogType = DIALOG_FIN;
		return true;
	}
	return false;
}
