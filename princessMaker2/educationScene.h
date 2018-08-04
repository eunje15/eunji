#pragma once
#include "gameNode.h"
#include "status.h"
#include "data.h"

enum DAYOFWEEK { MON, TUE, WED, THU, FRI, SAT, SUN };
enum EDU_TYPE { EDU_SCHOOL, EDU_POETRY, EDU_THEOLOGY, EDU_STRATEGY, EDU_SWORDS, EDU_FIGHTING, EDU_MAGIC, EDU_SCIENCE, EDU_BALLET, EDU_ART };
enum EDU_STATUS { EDU_STUDY, EDU_SLEEP, EDU_NOSTUDY };

class princess;

class educationScene : public gameNode
{
private:
	princess* _princess;
	status* _education;
	vector<string> _vDialog;
	DIALOG_TYPE _dialogType;
	int _dialogIdx;

	int _day, _dayCount, _dayIdx;
	int _gold;
	int _startF, _endF, _count, _frameCount, _frameX, _success;
	int _teacherFrameX;
	int _dialogX, _dialogY;

	string _typeStr;
	string _eduName;
	string _teachDialog;
	EDU_TYPE _type;
	EDU_STATUS _status;
	STATUS_TYPE _statusProgess;
	DAYOFWEEK _dayOfWeek;
	vector<pair<string,int>> _eduStatus;

	image* _back;
	image* _princessImg;
	vector<image*> _friends;

	bool _fin;

	tagProgress _pGold;
	tagProgress _vPStatus;

public:
	educationScene();
	~educationScene();

	HRESULT init(status* education, int dayCount);
	void update();
	void render();
	void release();

	void initStatus();
	void setImage();
	void setTeachDialog();
	void setDialog(string dialog);

	void changeFrame();
	void changeStatus(string name, int value);

	bool dialogRender();
	void eduRender();

	bool getFin() { return _fin; }
};

