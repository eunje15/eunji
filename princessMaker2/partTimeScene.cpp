#include "stdafx.h"
#include "partTimeScene.h"
#include "princess.h"

partTimeScene::partTimeScene()
{
}


partTimeScene::~partTimeScene()
{
}

HRESULT partTimeScene::init(workStatus* work, int dayCount, int idx)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_dayOfWeek = (DAYOFWEEK)_princess->getDate().dayOfWeek;
	_day = _princess->getDate().day;

	_idx = idx;
	_work = work;
	_workName = _work->getName();
	_dayCount = dayCount;

	if (_workName == "집안일")
		_type = WORK_HOUSE;
	else if (_workName == "보모")
		_type = WORK_NURSERY;
	else if (_workName == "여관")
		_type = WORK_INN;
	else if (_workName == "농장")
		_type = WORK_FARM;
	else if (_workName == "성당")
		_type = WORK_CHURCH;
	else if (_workName == "레스토랑")
		_type = WORK_RESTAURANT;
	else if (_workName == "나무꾼")
		_type = WORK_WOOD;
	else if (_workName == "미용실")
		_type = WORK_HAIR;
	else if (_workName == "미장이")
		_type = WORK_PLASTERER;
	else if (_workName == "사냥꾼")
		_type = WORK_HUNTER;
	else if (_workName == "묘지기")
		_type = WORK_GRAVE;
	else if (_workName == "가정교사")
		_type = WORK_COACH;
	else if (_workName == "주점")
		_type = WORK_DRINK;
	else if (_workName == "밤의 주점")
		_type = WORK_NIGHT_DRINK;
	else if (_workName == "밤의 전당")
		_type = WORK_NIGHT_CLUB;
	
	initStatus();
	setImage();
	setTeachDialog();

	_gold = _work->getSalary();
	_success = _count = _frameCount = _dayIdx = _printDay = 0;
	_frameX = _startF;
	_fin = _goldOk = _workFin = false;
	_progress = STATUS_START;
	string str = _princess->getInfo().name + "는 오늘부터 " + _workName + "을 시작합니다.";
	setDialog(str);
	_dialogX = 20, _dialogY = WINSIZEY - 180;
	_dialogIdx = 0, _dialogType = DIALOG_ING;

	return S_OK;
}

void partTimeScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_progress)
	{
	case STATUS_START:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_progress = STATUS_TEACH;
			setDialog(_teachDialog[1]);
			_dialogX = 190, _dialogY = 235;
			_dialogIdx = 0, _dialogType = DIALOG_ING;
		}
		break;
	case STATUS_TEACH:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_progress = STATUS_ING;
			_dialogType = DIALOG_FIN;
			_dialogX = 450, _dialogY = 250;
		}
		break;
	case STATUS_ING:
		if (!_goldOk)
		{
			_princess->setGold(_gold);
			_pGold.data += _gold;
			_goldOk = true;
		}
		changeFrame();
		break;
	case STATUS_FIN:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_fin = true;
		}
		break;
	}
}

void partTimeScene::render()
{
	switch (_progress)
	{
	case STATUS_START:
		IMAGEMANAGER->findImage("알바액자")->render(DC, 10, WINSIZEY - 190);
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
		IMAGEMANAGER->findImage("알바선생")->frameRender(DC, 45, 235, _teacherFrameX, 0);
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
			workRender();
		}
		break;
	case STATUS_FIN:
		IMAGEMANAGER->findImage("info2Back")->render(DC, 440, 238);
		if (dialogRender())
		{
			for (int i = 0; i < _vDialog.size(); i++)
			{
				TextOut(DC, _dialogX, _dialogY + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
			}
		}
		workRender();
		break;
	}
}

void partTimeScene::release()
{
}

void partTimeScene::initStatus()
{
	_pGold.str = "수입", _pGold.data = 0;

	_pGold.strRc = RectMake(45, 205, 80, 25);
	_pGold.dataRc = RectMake(125, 205, 50, 25);

	_workStatus.clear();
	_vPStatus.clear();

	for (int i = 0; i < _work->getProperty().size(); i++)
	{
		_workStatus.push_back(make_pair(_work->getProperty()[i].first, 0));
	}

	for (int i = 0; i < _workStatus.size() + 1; i++)
	{
		image* img = new image;
		img->init("image/education/progressBack(240x44).bmp", 240, 44, false, RGB(255, 0, 255));

		tagProgress temp;
		if (i == _workStatus.size())
		{
			temp.str = "스트레스";
			temp.data = _princess->getStatus().stress;
		}
		else
		{
			temp.str = _workStatus[i].first;
			temp.data = changeStatus(_workStatus[i].first, 0);
		}

		temp.strRc = RectMake(50 + 250 * (i % 2), 440 + (i / 2) * 50, 80, 25);
		temp.dataRc = RectMake(130 + 250 * (i % 2), 440 + (i / 2) * 50, 30, 25);

		temp.progressBar = new progressBar;
		temp.progressBar->init(160 + 250 * (i % 2), 440 + (i / 2) * 50, 110, 20);
		temp.progressBar->setGauge(temp.data, 500);

		_vPStatus.push_back(make_pair(img, temp));
	}
}

void partTimeScene::setImage()
{
	//이미지 따기
}

void partTimeScene::setTeachDialog()
{
	//다이얼로그 만들기
}

void partTimeScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if (_vDialog.size() > 0)
		_vDialog.clear();
	
	int strLength = 40;
	if (_progress == STATUS_FIN || _progress == STATUS_TEACH) strLength = 28;
	while (1)
	{
		if (strSize > strLength)
		{
			_vDialog.push_back(str.substr(idx, strLength));
			idx += strLength;
			strSize -= strLength;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

void partTimeScene::setResultDialog()
{
	_progress = STATUS_FIN;
	_vDialog.clear();
	//게임보고 마무리 어떻게 지어지나 봐야해
	string str = to_string(_printDay) + "일간의 급여는"+ to_string(_pGold.data)+"이다.";
	_vDialog.push_back(str);
	DIALOG->setDialog(_vDialog[0], 5);
}

void partTimeScene::changeFrame()
{
	if (_workFin) return;

	if (_dayIdx >= _dayCount)
	{
		setResultDialog();
		_workFin = true;
		return;
	}
	_count++;
	if (!(_count % 5))
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
			if (_frameX < _endF)
				_frameX++;
			else
			{
				_frameX = _startF;
				_frameCount++;
			}
		}
		else
			_frameCount++;
		if (_frameCount == 3)
		{
			_frameCount = 0;
			_day++;
			_dayIdx++;
			if (_dayOfWeek != SUN)
				_printDay++;
			switch (_dayOfWeek)
			{
			case MON:
				_dayOfWeek = TUE;
				_goldOk = false;
				break;
			case TUE:
				_dayOfWeek = WED;
				_goldOk = false;
				break;
			case WED:
				_dayOfWeek = THU;
				_goldOk = false;
				break;
			case THU:
				_dayOfWeek = FRI;
				_goldOk = false;
				break;
			case FRI:
				_dayOfWeek = SAT;
				_goldOk = false;
				break;
			case SAT:
				_dayOfWeek = SUN;
				break;
			case SUN:
				_dayOfWeek = MON;
				_goldOk = false;
				break;
			}
			if (_dayOfWeek != MON)
			{
				//workStatus올려주기
				for (int i = 0; i < _work->getProperty().size(); i++)
				{
					int randNum;
					if (_work->getProperty()[i].second.first == _work->getProperty()[i].second.second)
						randNum = _work->getProperty()[i].second.first;
					else
					{
						if (_work->getProperty()[i].second.second < 0)
						{
							randNum = RND->getFromIntTo(_work->getProperty()[i].second.first, -_work->getProperty()[i].second.second);
							randNum = -randNum;
						}
						else
						{
							randNum = RND->getFromIntTo(_work->getProperty()[i].second.first, _work->getProperty()[i].second.second);
						}
					}
					changeStatus(_work->getProperty()[i].first, randNum);
					_workStatus[i].second += randNum;
					_vPStatus[i].second.data += randNum;
				}
			}
			switch (_type)
			{
			case WORK_HOUSE:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_NURSERY:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_INN:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_FARM:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_CHURCH:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_RESTAURANT:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_WOOD:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_HAIR:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_PLASTERER:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_HUNTER:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_GRAVE:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_COACH:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_DRINK:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_NIGHT_DRINK:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			case WORK_NIGHT_CLUB:
				if (selectStatus() == WORK_HARD)
				{

				}
				else if (selectStatus() == WORK_SLEEP)
				{

				}
				else
				{

				}
				break;
			}
			if (_dayIdx < _dayCount)
			{
				_princess->getStatusP()->stress += _work->getStress();
				_vPStatus[_vPStatus.size() - 1].second.data += _work->getStress();
				_princess->setDay(_day);
				_princess->setDayOfWeek(_dayOfWeek);
			}
		}
	}
}

WORK_STATUS partTimeScene::selectStatus()
{
	//성공 조건 다시해야해
	if (_princess->getStatus().stress > _princess->getStatus().faith)
		return WORK_SLEEP;
	if (_princess->getStatus().stress > _princess->getStatus().morality)
		return WORK_NOHARD;
	return WORK_HARD;
}

int partTimeScene::changeStatus(string name, int value)
{
	int temp;
	
	if (name == "요리")
	{
		temp = _princess->getStatus().cooking;
		_princess->getStatusP()->cooking += value;
	}
	else if (name == "감수성")
	{
		temp = _princess->getStatus().sensitivity;
		_princess->getStatusP()->sensitivity += value;
	}
	else if (name == "청소세탁")
	{
		temp = _princess->getStatus().cleaning;
		_princess->getStatusP()->cleaning += value;
	}
	else if (name == "체력")
	{
		temp = _princess->getStatus().hp;
		_princess->getStatusP()->hp += value;
	}
	else if (name == "도덕성")
	{
		temp = _princess->getStatus().morality;
		_princess->getStatusP()->morality += value;
	}
	else if (name == "근력")
	{
		temp = _princess->getStatus().physical;
		_princess->getStatusP()->physical += value;
	}
	else if (name == "매력")
	{
		temp = _princess->getStatus().sexual;
		_princess->getStatusP()->sexual += value;
	}
	else if (name == "전투기술")
	{
		temp = _princess->getStatus().warriorSkill;
		_princess->getStatusP()->warriorSkill += value;
	}
	else if (name == "신앙심")
	{
		temp = _princess->getStatus().faith;
		_princess->getStatusP()->faith += value;
	}
	else if (name == "기품")
	{
		temp = _princess->getStatus().elegance;
		_princess->getStatusP()->elegance += value;
	}
	else if (name == "항마력")
	{
		temp = _princess->getStatus().spellDefence;
		_princess->getStatusP()->spellDefence += value;
	}
	else if (name == "화술")
	{
		temp = _princess->getStatus().conversation;
		_princess->getStatusP()->conversation += value;
	}
	else if (name == "인과")
	{
		temp = _princess->getStatus().karma;
		_princess->getStatusP()->karma += value;
	}
	else if (name == "성품")
	{
		temp = _princess->getStatus().personality;
		_princess->getStatusP()->personality += value;
	}
	else if (name == "지능")
	{
		temp = _princess->getStatus().intelligence;
		_princess->getStatusP()->intelligence += value;
	}
	else if (name == "관계")
	{
		temp = _princess->getStatus().withFather;
		_princess->getStatusP()->withFather += value;
	}
	return temp;
}

bool partTimeScene::dialogRender()
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

void partTimeScene::workRender()
{
	IMAGEMANAGER->findImage("교육액자")->render(DC, 10, 240);
	int backX = 20, backY = 250;
	_back->render(DC, backX, backY);
	IMAGEMANAGER->findImage("goldBack")->render(DC, _pGold.strRc.left - 35, _pGold.strRc.top - 10);

	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(111, 17, 17));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	FillRect(DC, &_pGold.strRc, brush);
	Rectangle(DC, _pGold.strRc.left, _pGold.strRc.top, _pGold.strRc.right, _pGold.strRc.bottom);
	TextOut(DC, _pGold.strRc.left + 5, _pGold.strRc.top + 7, _pGold.str.c_str(), strlen(_pGold.str.c_str()));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	brush = CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(DC, brush);
	Rectangle(DC, _pGold.dataRc.left, _pGold.dataRc.top, _pGold.dataRc.right, _pGold.dataRc.bottom);
	char str[128];
	sprintf_s(str, "%3dG", _pGold.data);
	TextOut(DC, _pGold.dataRc.left + 5, _pGold.dataRc.top + 7, str, strlen(str));
	SelectObject(DC, oldBrush);
	DeleteObject(brush);

	if (_progress == STATUS_FIN) return;

	if (_dayOfWeek == SUN && (_dayIdx < _dayCount))
	{
		TextOut(DC, 450, 250, "오늘은 일요일입니다.", strlen("오늘은 일요일입니다."));
		return;
	}

	switch (_type)
	{
	case WORK_HOUSE:
		break;
	case WORK_NURSERY:
		break;
	case WORK_INN:
		break;
	case WORK_FARM:
		break;
	case WORK_CHURCH:
		break;
	case WORK_RESTAURANT:
		break;
	case WORK_WOOD:
		break;
	case WORK_HAIR:
		break;
	case WORK_PLASTERER:
		break;
	case WORK_HUNTER:
		break;
	case WORK_GRAVE:
		break;
	case WORK_COACH:
		break;
	case WORK_DRINK:
		break;
	case WORK_NIGHT_DRINK:
		break;
	case WORK_NIGHT_CLUB:
		break;
	}

	string temp = _workName + " " + to_string(_printDay + 1) + "일차";
	TextOut(DC, 450, 250, temp.c_str(), strlen(temp.c_str()));
	char str2[128];
	switch (_status)
	{
	case WORK_HARD:
		sprintf_s(str2, "프레임카운트 :%d, 공부중", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	case WORK_SLEEP:
		sprintf_s(str2, "프레임카운트 :%d, 자는중", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	case WORK_NOHARD:
		sprintf_s(str2, "프레임카운트 :%d, 농땡이중", _frameCount);
		TextOut(DC, WINSIZEX / 2, WINSIZEY / 2, str2, strlen(str2));
		break;
	}

	for (int i = 0; i < _vPStatus.size(); i++)
	{
		_vPStatus[i].first->render(DC, _vPStatus[i].second.strRc.left - 10, _vPStatus[i].second.strRc.top - 10);
		HBRUSH brush, oldBrush;
		brush = CreateSolidBrush(RGB(111, 17, 17));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		FillRect(DC, &_vPStatus[i].second.strRc, brush);
		Rectangle(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top, _vPStatus[i].second.strRc.right, _vPStatus[i].second.strRc.bottom);
		TextOut(DC, _vPStatus[i].second.strRc.left, _vPStatus[i].second.strRc.top + 2, _vPStatus[i].second.str.c_str(), strlen(_vPStatus[i].second.str.c_str()));
		SelectObject(DC, oldBrush);
		DeleteObject(brush);

		brush = CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = (HBRUSH)SelectObject(DC, brush);
		Rectangle(DC, _vPStatus[i].second.dataRc.left, _vPStatus[i].second.dataRc.top, _vPStatus[i].second.dataRc.right, _vPStatus[i].second.dataRc.bottom);
		char str[128];
		sprintf_s(str, "%3d", _vPStatus[i].second.data);
		TextOut(DC, _vPStatus[i].second.dataRc.left + 2, _vPStatus[i].second.dataRc.top + 2, str, strlen(str));
		SelectObject(DC, oldBrush);
		DeleteObject(brush);

		_vPStatus[i].second.progressBar->render();
	}
}
