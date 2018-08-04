#pragma once
#include "gameNode.h"
#include "data.h"
#include "statusManager.h"
#include "educationScene.h"

enum SCHEDULE_TYPE {SCHEDULE_NONE, SCHEDULE_TEACH, SCHEDULE_WORK, SCHEDULE_FIGHT, SCHEDULE_RELAX, SCHEDULE_OK, SCHEDULE_GO };

class princess;

class scheduleScene : public gameNode
{
private:
	princess* _princess;
	bool _fin, _select, _scheduleStart;
	int _year, _mon, _gold;
	SCHEDULE_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagImg _calImg[42];
	tagImg _teachImg[10], _workImg[15], _fightImg[4], _relaxImg[2];
	vector<string> _vDialog;
	tagString _chooseBox[4], _selectBox[2];
	string _scheduleWeek[3];
	int _itemIdx[3];
	
	int _dialogIdx, _scheduleIdx, _selectNum;

	statusManager* _sm;
	educationScene* _education;

public:
	scheduleScene();
	~scheduleScene();

	HRESULT init(int year, int mon);
	void update();
	void render();
	void release();

	void setSchedule();

	void setDialog(string dialog);

	void setScheduleImage();

	bool dialogRender();

	bool getFin() { return _fin; }

	void setStatusManagerAddressLink(statusManager* sm) { _sm = sm; }
};

