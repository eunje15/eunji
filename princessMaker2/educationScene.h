#pragma once
#include "gameNode.h"
#include "status.h"

enum DAYOFWEEK { MON, TUE, WED, THU, FRI, SAT, SUN };
enum EDU_TYPE { EDU_SCHOOL, EDU_POETRY, EDU_THEOLOGY, EDU_STRATEGY, EDU_SWORDS, EDU_FIGHTING, EDU_MAGIC, EDU_SCIENCE, EDU_BALLET, EDU_ART };
enum EDU_STATUS { EDU_STUDY, EDU_SLEEP, EDU_NOSTUDY };

class princess;

class educationScene : public gameNode
{
private:
	princess* _princess;
	status* _education;

	int _day, _dayCount;
	int _gold;
	int _startF, _endF, _count, _frameCount, _frameX, _success;
	int _teacherFrameX;
	bool _start;

	string _typeStr;
	string _eduName;
	EDU_TYPE _type;
	EDU_STATUS _status;
	DAYOFWEEK _dayOfWeek;

	image* _back;
	image* _princessImg;
	vector<image*> _friends;

	bool _fin;

public:
	educationScene();
	~educationScene();

	HRESULT init(status* education, int dayCount);
	void update();
	void render();
	void release();

	void setImage();

	bool getFin() { return _fin; }
};

