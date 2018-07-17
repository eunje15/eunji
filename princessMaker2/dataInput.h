#pragma once
#include "gameNode.h"
#include "data.h"

enum PROLOGUE_MODE { PROLOGUE_DADNAME, PROLOGUE_DADCAL, PROLOGUE_NAME, PROLOGUE_CAL, PROLOGUE_BLOOD, PROLOGUE_DIALOG };
class dataInput :public gameNode
{
private:
	image* _back;
	tagObj _okBtn;
	tagObj _backBtn;
	PROLOGUE_MODE _mode;

	string _dadName;
	string _princessName;
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
};

