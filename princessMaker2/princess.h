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
	vector<item*> _vInven;
	
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
	tagBody getBodyInfo() { return _bodyInfo; }
	string getDadName() { return _info.firstName; }

	void setGold(int gold) { _info.gold -= gold; }
	int getGold() { return _info.gold; }

	void setDietType(string type) { _info.dietType = type; }
	void setStress(int stress);

	vector<item*> getVItem() { return _vInven; }
	void setVItemName(int idx, string name) { _vInven[idx]->setName(name); }

	bool setItem(item* newItem);
	void setDataItem();
};

