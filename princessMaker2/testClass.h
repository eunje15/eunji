#pragma once
#include "gameNode.h"

//enum EDU_TYPE { EDU_STUDY, EDU_SLEEP, EDU_NOSTUDY };
//enum DAYOFWEEK {MON, TUE, WED, THU, FRI, SAT, SUN };
class testClass : public gameNode
{
private:
	int _day;
	int _gold;
	int _success;
	int _startF, _endF, _count, _frameCount, _frameX;
	string _typeStr;
	//EDU_TYPE _type;
	//DAYOFWEEK _dayOfWeek;
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

