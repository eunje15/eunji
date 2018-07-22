#pragma once
#include "gameNode.h"
#include "data.h"
class princess : public gameNode
{
private:
	tagInfo _info;
	tagStatus _status;
	string _dadName;
	tagImg _face, _body;

	int _age;
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
	void setDadName(string dadName) { _dadName = dadName; }
	tagInfo getInfo() { return _info; }
	tagStatus getStatus() { return _status; }
	string getDadName() { return _dadName; }
};

