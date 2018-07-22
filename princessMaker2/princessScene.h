#pragma once
#include "gameNode.h"
#include "princess.h"

enum SEASON_TYPE { SPRING, SUMMER, AUTUMN, WINTER };
enum MENU_TYPE { SELECT_NONE, SELECT_STATUS, SELECT_TALK, SELECT_CHANGE_INFO, SELECT_INFO,
				 SELECT_TOWN, SELECT_CASTLE, SELECT_WEAPON, SELECT_SAVE, SELECT_SCHEDULE };
class princessScene : public gameNode
{
private:
	princess* _princess;
	image *_back, *_selectMenu;
	MENU_TYPE _menuType;
	int _year, _mon, _day, _dayOfWeek;
	int _perHealth, _perBad, _personalConnect;
	SEASON_TYPE _season;
	tagImg _cal, _status, _menu, _flower, _frame;
	tagImg _yearImg, _monImg, _dayImg, _dayOfWeekImg;
	tagObj _menubox[9];
	RECT _nameRc, _firstNameRc;
	tagString _strStatus[4], _printStrStatus;
	
public:
	princessScene();
	~princessScene();

	HRESULT init();
	void update();
	void render();
	void infoRender();
	void statusRender();
	void release();

	void setStringStatus();
};

