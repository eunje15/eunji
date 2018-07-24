#pragma once
#include "gameNode.h"
#include "princess.h"
#include "cube.h"
#include "weaponStore.h"

enum SEASON_TYPE { SPRING, SUMMER, AUTUMN, WINTER };
enum MENU_TYPE { SELECT_NONE, SELECT_STATUS, SELECT_TALK, SELECT_CHANGE_INFO, SELECT_INFO,
				 SELECT_TOWN, SELECT_CASTLE, SELECT_WEAPON, SELECT_SAVE, SELECT_SCHEDULE };
enum STORE_TYPE { STORE_NONE, STORE_WEAPON, STORE_ARMOR, STORE_COOK, STORE_GOODS, STORE_CHURCH, STORE_HOSTIPITAL, STORE_SELECT };

class princessScene : public gameNode
{
private:
	princess* _princess;
	image *_back, *_selectMenu;
	MENU_TYPE _menuType;
	STORE_TYPE _storeType;
	int _year, _mon, _day, _dayOfWeek;
	int _perHealth, _perBad, _personalConnect, _idx, _count;
	SEASON_TYPE _season;
	tagImg _cal, _status, _menu, _flower, _frame;
	tagImg _yearImg, _monImg, _dayImg, _dayOfWeekImg, _constellationImg;
	tagObj _menubox[9];
	RECT _nameRc, _firstNameRc;
	tagString _strStatus[4], _printStrStatus;
	tagProgress _pInfo[10], _p4Stat[4], _pSkill[6], _pBasicStat[6];
	tagString _dadTalk[3], _changeInfo[4], _dialog[4], _chooseAnswer[2];
	bool _dialogSelect, _isClick;
	cube* _cube;
	vector<string> _vDialog;
	tagImg _store[7];
	string _storeDialog;

	weaponStore* _weaponStore;

public:
	princessScene();
	~princessScene();

	HRESULT init();
	void update();
	void render();
	void setStat();
	void setDadTalk();
	void changeInfo();
	void infoRender();
	void statusRender();
	void dadTalkRender();
	void changeInfoRender();
	void release();

	void setStringStatus();
	void setDialog(string dialog);
	void setStore();
	void setRectZero(RECT * rc);
	void clickStore();
	void storeRender();
};

