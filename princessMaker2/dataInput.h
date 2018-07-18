#pragma once
#include "gameNode.h"
#include "data.h"

enum PROLOGUE_MODE { PROLOGUE_DADNAME, PROLOGUE_DADCAL, PROLOGUE_DADAGE, PROLOGUE_NAME, PROLOGUE_CAL, PROLOGUE_BLOOD, PROLOGUE_DIALOG };

class princess;

class dataInput :public gameNode
{
private:
	princess* _princess;
	tagInfo _princessInfo;

	image* _back;
	tagObj _okBtn;
	tagObj _backBtn;

	PROLOGUE_MODE _mode;

	string _dadName;
	string _princessName;

	tagObj _cal[12][42];
	image* _img;
	
	tagObj _dadAgeArr[10];
	list<int> _lDadAge;
	list<int>::iterator _lDadAgeIter;
	int	_dadAge, _dadYear;

public:
	dataInput();
	~dataInput();

	HRESULT init();
	void update();
	void render();
	void release();
	void setDadName();
	void setDadNameRender();
	void setPrincessName();
	void setPrincessNameRender();
	void changeMode();
	void setCal();
	void CalRender();
	void clickCal();

	void setDadAge();

	void dadAgeRender();

	void checkRender();

	void setDadCal();

	void dadCalRender();

	void setPrincessAddressLink(princess* princess) { _princess = princess; }
};

