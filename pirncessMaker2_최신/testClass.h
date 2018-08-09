#pragma once
#include "gameNode.h"
#include "data.h"

enum TEST_TYPE { TEST_STUDY, TEST_SLEEP, TEST_NOSTUDY };
//enum DAYOFWEEK {MON, TUE, WED, THU, FRI, SAT, SUN };
class testClass : public gameNode
{
private:
	int _day;
	int _gold;
	int _success;
	int _startF, _endF, _count, _frameCount, _frameX;
	int _teacherStartF, _teacherEndF;
	string _typeStr;
	TEST_TYPE _type;
	DAYOFWEEK _dayOfWeek;
	image* _back;
	image* _princess;
	image* _teacher;
	vector<image*> _friends;
public:
	testClass();
	~testClass();

	HRESULT init();
	void update();
	void render();
	void release();
};

