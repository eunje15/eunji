#pragma once
#include "gameNode.h"
#include "status.h"
#include "workStatus.h"
#include "relaxStatus.h"

enum STATUS_DATA_TYPE { STATUS_DATA_TEACH, STATUS_DATA_WORK, STATUS_DATA_FIGHT, STATUS_DATA_RELAX };
class statusManager : public gameNode
{
private:
	vector<status*>			_vTeach;
	vector<workStatus*>		_vWork;
	vector<status*>			_vFight;
	vector<relaxStatus*>	_vRelax;

	STATUS_DATA_TYPE _type;

public:
	statusManager();
	~statusManager();

	HRESULT init();
	void update();
	void render();
	void release();
	void loadData(const char* dataName);
	void loadWorkData(const char* dataName);

	void setRelaxData();

	vector<status*> getVTeach() { return _vTeach; }
	vector<workStatus*> getVWork() { return _vWork; }
	vector<status*> getVFight() { return _vFight; }
	vector<relaxStatus*> getVRelax() { return _vRelax; }
};

