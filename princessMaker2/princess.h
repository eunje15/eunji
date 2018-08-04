#pragma once
#include "gameNode.h"
#include "data.h"
#include "item.h"

class princess : public gameNode
{
private:
	tagInfo _info;
	tagStatus _status;
	tagBody _bodyInfo;
	tagImg _face, _body;
	tagDate _date;
	vector<item*> _vInven;
	vector<string> _vItemName;
public:
	princess();
	~princess();

	HRESULT init();
	void update();
	void render();
	void release();

	void setStatus();

	void setInfo(tagInfo info){	_info = info; }
	void setStatus(tagStatus status) { _status = status; }
	void setBodyInfo(tagBody bodyInfo) { _bodyInfo = bodyInfo; }
	void setDadName(string dadName) { _info.firstName = dadName; }
	tagInfo getInfo() { return _info; }
	tagStatus getStatus() { return _status; }
	tagStatus* getStatusP() { return &_status; }
	tagBody getBodyInfo() { return _bodyInfo; }
	string getDadName() { return _info.firstName; }

	void setGold(int gold) { _info.gold -= gold; }
	int getGold() { return _info.gold; }

	void setDietType(string type) { _info.dietType = type; }
	void setStress(int stress);

	vector<item*> getVItem() { return _vInven; }
	//void setVItemName(int idx, string name) { _vInven[idx]->setName(name); }

	void setVItemName(vector<string> vName) { _vItemName = vName; }
	bool setItem(item* newItem);
	void setDataItem(vector<item*> vTotal);

	tagDate getDate() { return _date; }
	void setDate(tagDate date) { _date = date; }

	void setDayOfWeek(int dayOfWeek) { _date.dayOfWeek = dayOfWeek; }
	int getDayOfWeek() { return _date.dayOfWeek; }
	void setDay(int day) { _date.day = day; }
	int getDay() { return _date.day; }
};

