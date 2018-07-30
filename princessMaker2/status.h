#pragma once
#include "gameNode.h"
#include "data.h"

enum STATUS_TYPE { STATUS_TEACH, STATUS_WORK, STATUS_FIGHT, STATUS_RELAX };

class status : public gameNode
{
private:
	string _name;
	string _teacher;
	int _tuition, _plusTuition;
	image* _img;
	int _frameX, _frameY, _step;
	//vector<pair<string, int>> _property;
	vector<tagStatusData> _property;
	STATUS_TYPE _type;
	float _x, _y;
public:
	status();
	~status();

	HRESULT init();
	void update();
	void render();
	void release();

	void setStatus(string name, string teacher, int tuition, int plus, vector<tagStatusData> property, int type, int frameX, int frameY);
	void setImage();

	void setXY(float x, float y) { _x = x, _y = y; }

	string getName() { return _name; }
	void upgradeStep();
	string getStringStep();
	int getTuition() {	return _tuition; }

	int getFrameIndex() { return _frameX; }
};

