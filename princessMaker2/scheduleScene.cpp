#include "stdafx.h"
#include "scheduleScene.h"
#include "princess.h"

scheduleScene::scheduleScene()
{
}


scheduleScene::~scheduleScene()
{
}

HRESULT scheduleScene::init(int year, int mon)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	//걍 지금은 일요일부터 무조건 시작
	_year = year, _mon = mon;

	int finday = 30;
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12)
		finday = 31;

	for (int i = 0; i < 42; i++)
	{
		_calImg[i].data.rc = RectMake(20 + (i % 7) * 40 , 160 + 40 * (i / 7), 40, 40);
		_calImg[i].x = (_calImg[i].data.rc.right + _calImg[i].data.rc.left) / 2 - 3;
		_calImg[i].y = (_calImg[i].data.rc.bottom + _calImg[i].data.rc.top) / 2 - 3;
		if (i < finday)
		{
			_calImg[i].data.str = to_string(i + 1);
			_calImg[i].data.isChoose = true;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_chooseBox[i].rc = RectMake(610, 290 + i*28, 150, 28);
		_chooseBox[i].isChoose = _chooseBox[i].isSelected = false;
		if (i > 1) continue;
		_selectBox[i].rc = RectMake(600, 330 + i * 28, 150, 28);
		_selectBox[i].isChoose = _selectBox[i].isSelected = false;
	}

	_chooseBox[0].str = "딸을 단련시킨다";
	_chooseBox[1].str = "딸에게 일을 시킨다";
	_chooseBox[2].str = "무사수행을 보낸다";
	_chooseBox[3].str = "휴식을 준다";

	_selectBox[0].str = "스케줄에 편성한다";
	_selectBox[1].str = "취소";

	_type = SCHEDULE_NONE;

	setDialog("이번달 딸의 예정은?(첫번째)");
	_dialogType = DIALOG_ING;
	_dialogIdx = _scheduleIdx = 0;
	_selectNum = -1;
	setScheduleImage();

	
	return S_OK;
}

void scheduleScene::update()
{
	if (_dialogType == DIALOG_ING) return;
	switch (_type)
	{
	case SCHEDULE_NONE:
		for (int i = 0; i < 4; i++)
		{
			_chooseBox[i].isSelected = false;
			if (PtInRect(&_chooseBox[i].rc, _ptMouse))
			{
				_chooseBox[i].isSelected = true;
				if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					if (i == 0)
					{
						_type = SCHEDULE_TEACH;
						setDialog("딸에게 무엇을 가르치시겠습니까?");
					}
					else if (i == 1)
						_type = SCHEDULE_WORK;
					else if (i == 2)
						_type = SCHEDULE_FIGHT;
					else if (i == 3)
						_type = SCHEDULE_RELAX;
				}
			}
		}
		break;
	case SCHEDULE_TEACH:
	{
		if (!_select)
		{
			for (int i = 0; i < 10; i++)
			{
				_teachImg[i].frameX = 0;
				if (PtInRect(&_teachImg[i].data.rc, _ptMouse))
				{
					_teachImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _sm->getVTeach()[_selectNum]->getFrameIndex();
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "teach";
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = "teach";
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "teach";
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "네, 스케줄에 편성하겠습니다. 이번달 딸의 예정은?";
							if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "이번달 딸의 예정은?";
							if (_scheduleIdx == 0)
								str += "(첫번째)";
							else if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}

		}
	}
	break;
	case SCHEDULE_WORK:
		if (!_select)
		{
			for (int i = 0; i < 15; i++)
			{
				_workImg[i].frameX = 0;
				if (PtInRect(&_workImg[i].data.rc, _ptMouse) && _workImg[i].data.isSelected)
				{
					_workImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _sm->getVWork()[_selectNum]->getFrameIndex();
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "work";
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = "work";
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "work";
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "네, 스케줄에 편성하겠습니다. 이번달 딸의 예정은?";
							if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "이번달 딸의 예정은?";
							if (_scheduleIdx == 0)
								str += "(첫번째)";
							else if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}
		}
		break;
	case SCHEDULE_FIGHT:
		break;
	case SCHEDULE_RELAX:
		if (!_select)
		{
			for (int i = 0; i < 2; i++)
			{
				_relaxImg[i].frameX = 0;
				if (PtInRect(&_relaxImg[i].data.rc, _ptMouse))
				{
					_relaxImg[i].frameX = 1;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = true;
						_selectNum = i;
						break;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				_selectBox[i].isSelected = false;
				if (PtInRect(&_selectBox[i].rc, _ptMouse))
				{
					_selectBox[i].isSelected = true;
					if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_select = false;
						if (i == 0)
						{
							int count = 0;
							for (int i = 0; i < 42; i++)
							{
								if (!_calImg[i].data.isChoose || _calImg[i].data.isSelected) continue;
								count++;
								_calImg[i].frameX = _relaxImg[_selectNum].frameY;
								_calImg[i].data.isSelected = true;
								if (_scheduleIdx < 2)
								{
									if (count == 10)
									{
										_scheduleWeek[_scheduleIdx] = "relax";
										_scheduleIdx++;
										break;
									}
								}
								else
								{
									if (_mon == 1 || _mon == 3 || _mon == 5 || _mon == 7 || _mon == 8 || _mon == 10 || _mon == 12)
									{
										if (count == 11)
										{
											_scheduleWeek[_scheduleIdx] = "relax";
											_scheduleIdx++;
											break;
										}
									}
									else
									{
										if (count == 10)
										{
											_scheduleWeek[_scheduleIdx] = "relax";
											_scheduleIdx++;
											break;
										}
									}
								}
							}
							_type = SCHEDULE_NONE;
							string str = "네, 스케줄에 편성하겠습니다. 이번달 딸의 예정은?";
							if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
						else
						{
							_type = SCHEDULE_NONE;
							string str = "이번달 딸의 예정은?";
							if (_scheduleIdx == 0)
								str += "(첫번째)";
							else if (_scheduleIdx == 1)
								str += "(두번째)";
							else if (_scheduleIdx == 2)
								str += "(세번째)";
							setDialog(str);
							_dialogType = DIALOG_FIN;
						}
					}
				}
			}

		}
		 break;
	}
	
}

void scheduleScene::render()
{
	IMAGEMANAGER->findImage("schedule")->render(DC, 10, 110);
	IMAGEMANAGER->findImage("year")->frameRender(DC, 100, 119, 0, _year - 1200);
	IMAGEMANAGER->findImage("month")->frameRender(DC, 160, 119, 0, _mon - 1);

	IMAGEMANAGER->findImage("dialogFrame")->render(DC, 10, 426);
	IMAGEMANAGER->findImage("frame")->render(DC, 20 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 426);
	IMAGEMANAGER->findImage("cube")->frameRender(DC, 30 + IMAGEMANAGER->findImage("dialogFrame")->getWidth(), 436, 0, 0);

	if (dialogRender())
	{
		for (int i = 0; i < _vDialog.size(); i++)
		{
			TextOut(DC, 20, 440 + i * 30, _vDialog[i].c_str(), strlen(_vDialog[i].c_str()));
		}
		switch (_type)
		{
		case SCHEDULE_NONE:
			IMAGEMANAGER->findImage("4Back")->render(DC, 600, 280);

			for (int i = 0; i < 4; i++)
			{
				if (_chooseBox[i].isSelected)
				{
					HBRUSH brush, oldBrush;
					brush = CreateSolidBrush(RGB(43, 0, 0));
					oldBrush = (HBRUSH)SelectObject(DC, brush);
					FillRect(DC, &_chooseBox[i].rc, brush);
					SelectObject(DC, oldBrush);
					DeleteObject(brush);
				}
				TextOut(DC, _chooseBox[i].rc.left + 2, _chooseBox[i].rc.top + 5, _chooseBox[i].str.c_str(), strlen(_chooseBox[i].str.c_str()));
			}
			
			if (KEYMANAGER->isToggleKey(VK_TAB))
			{
				/*for (int i = 0; i < 42; i++)
				{
					Rectangle(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].data.rc.right, _calImg[i].data.rc.bottom);
				}
				*/
				for (int i = 0; i < 10; i++)
				{
					Rectangle(DC, _teachImg[i].data.rc.left, _teachImg[i].data.rc.top, _teachImg[i].data.rc.right, _teachImg[i].data.rc.bottom);
				}
			}
			break;
		case SCHEDULE_TEACH:
			if (!_select)
			{
				for (int i = 0; i < 10; i++)
				{
					_teachImg[i].img->frameRender(DC, _teachImg[i].data.rc.left, _teachImg[i].data.rc.top, _teachImg[i].frameX, 0);
					IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _teachImg[i].data.rc.left + 5, _teachImg[i].data.rc.top + 7, _teachImg[i].frameY, 0);
					TextOut(DC, _teachImg[i].data.rc.left + 50, _teachImg[i].data.rc.top + 7, _sm->getVTeach()[i]->getName().c_str(), strlen(_sm->getVTeach()[i]->getName().c_str()));
					string str = _sm->getVTeach()[i]->getStringStep() + " " + to_string(_sm->getVTeach()[i]->getTuition()) + "G";
					TextOut(DC, _teachImg[i].data.rc.left + 50, _teachImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_WORK:
			if (!_select)
			{
				for (int i = 0; i < 15; i++)
				{
					if (!_workImg[i].data.isSelected) continue;
					_workImg[i].img->frameRender(DC, _workImg[i].data.rc.left, _workImg[i].data.rc.top, _workImg[i].frameX, 0);
					IMAGEMANAGER->findImage("workImg")->frameRender(DC, _workImg[i].data.rc.left + 5, _workImg[i].data.rc.top + 7, _workImg[i].frameY, 0);
					TextOut(DC, _workImg[i].data.rc.left + 50, _workImg[i].data.rc.top + 7, _sm->getVWork()[i]->getName().c_str(), strlen(_sm->getVWork()[i]->getName().c_str()));
					string str = to_string(_sm->getVWork()[i]->getSalary()) + "G";
					TextOut(DC, _workImg[i].data.rc.left + 50, _workImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		case SCHEDULE_FIGHT:
			break;
		case SCHEDULE_RELAX:
			if (!_select)
			{
				for (int i = 0; i < 2; i++)
				{
					_relaxImg[i].img->frameRender(DC, _relaxImg[i].data.rc.left, _relaxImg[i].data.rc.top, _relaxImg[i].frameX, 0);
					IMAGEMANAGER->findImage("relaxImg")->frameRender(DC, _relaxImg[i].data.rc.left + 5, _relaxImg[i].data.rc.top + 7, _relaxImg[i].frameY, 0);
					TextOut(DC, _relaxImg[i].data.rc.left + 50, _relaxImg[i].data.rc.top + 7, _sm->getVRelax()[i]->getName().c_str(), strlen(_sm->getVRelax()[i]->getName().c_str()));
					string str = to_string(_sm->getVRelax()[i]->getGold()*_princess->getInfo().age) + "G";
					TextOut(DC, _relaxImg[i].data.rc.left + 50, _relaxImg[i].data.rc.top + 30, str.c_str(), strlen(str.c_str()));
				}
			}
			else
			{
				IMAGEMANAGER->findImage("3Back")->render(DC, 590, 300);
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
		}
	}
	int count = 0;
	for (int i = 0; i < 42; i++)
	{
		if (!_calImg[i].data.isChoose) break;
		if (_calImg[i].data.isSelected)
		{
			/*if (count / 10 < 0)
			{
				IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
			}*/
			if(_scheduleWeek[count / 10] == "teach")
				IMAGEMANAGER->findImage("teachImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
			else if(_scheduleWeek[count / 10] == "work")
				IMAGEMANAGER->findImage("workImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
			else if (_scheduleWeek[count / 10] == "relax")
				IMAGEMANAGER->findImage("relaxImg")->frameRender(DC, _calImg[i].data.rc.left, _calImg[i].data.rc.top, _calImg[i].frameX, 0);
			count++;
		}
		IMAGEMANAGER->findImage("smallDay")->frameRender(DC, _calImg[i].x, _calImg[i].y, 0, atoi(_calImg[i].data.str.c_str()) - 1);
	}
}

void scheduleScene::release()
{
}


void scheduleScene::setDialog(string dialog)
{
	DIALOG->setDialog(dialog, 5);
	string str = DIALOG->getTotalDialog();
	int strSize = str.size();
	int idx = 0;
	if(_vDialog.size() > 0)
		_vDialog.clear();
	string temp = "스케줄 결정";
	_vDialog.push_back(temp);
	while (1)
	{
		if (strSize > 28)
		{
			_vDialog.push_back(str.substr(idx, 28));
			idx += 28;
			strSize -= 28;
		}
		else
		{
			_vDialog.push_back(str.substr(idx, strSize));
			break;
		}
	}
	DIALOG->setDialog(_vDialog[0], 5);
}

void scheduleScene::setScheduleImage()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_teachImg[j + i * 2].img = new image;
			_teachImg[j + 2 * i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
			_teachImg[j + 2 * i].data.rc = RectMake(460 + 170*j, 135 + 60*i, 160, 52);
						  
			_teachImg[j + 2 * i].frameY = j + 2 * i;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i == 7 && j == 1) break;
			_workImg[j + 2 * i].img = new image;
			_workImg[j + 2 * i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
			_workImg[j + 2 * i].data.rc = RectMake(460 + 170 * j, 435 - 60 * i, 160, 52);
			_workImg[j + 2 * i].frameY = j + 2 * i;

			if (_sm->getVWork()[j + 2 * i]->getAge() <= _princess->getInfo().age)
			{
				_workImg[j + 2 * i].data.isSelected = true;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		_relaxImg[i].img = new image;
		_relaxImg[i].img->init("image/main/storeSelect(320x52,2x1).bmp", 320, 52, 2, 1, true, RGB(255, 0, 255));
		_relaxImg[i].data.rc = RectMake(460 + 170 * i, 300, 160, 52);
		_relaxImg[i].frameY = i;
	}
}

bool scheduleScene::dialogRender()
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