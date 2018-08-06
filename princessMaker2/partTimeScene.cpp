#include "stdafx.h"
#include "partTimeScene.h"
#include "princess.h"

partTimeScene::partTimeScene()
{
}


partTimeScene::~partTimeScene()
{
}

HRESULT partTimeScene::init(workStatus * work, int dayCount)
{
	_princess = SCENEMANAGER->getPrincessAddress();
	_dayOfWeek = (DAYOFWEEK)_princess->getDate().dayOfWeek;
	_day = _princess->getDate().day;

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
		break;
	case STATUS_TEACH:
		break;
	case STATUS_ING:
		break;
	case STATUS_FIN:
		break;
	}
}

void partTimeScene::release()
{
}

void partTimeScene::initStatus()
{
}

void partTimeScene::setImage()
{
}

void partTimeScene::setTeachDialog()
{
}

void partTimeScene::setDialog(string dialog)
{
}

void partTimeScene::setResultDialog()
{
}

void partTimeScene::changeFrame()
{
}

WORK_STATUS partTimeScene::selectStatus()
{
	return WORK_STATUS();
}

int partTimeScene::changeStatus(string name, int value)
{
	return 0;
}

bool partTimeScene::dialogRender()
{
	return false;
}

void partTimeScene::workRender()
{
}
