#pragma once
#include "gameNode.h"

enum RELAX_TYPE { FREE_NOGOLD, FREE_GOLD, VACATION_SEA, VACATION_MOUNTAIN };
class relaxStatus : public gameNode
{
private:
	string _name;
	int _season;
	int _sensitivity;
	int _stress;
	int _gold;
	float _weight;	//¹«°Ô
	RELAX_TYPE _type;
public:
	relaxStatus();
	~relaxStatus();
	HRESULT init();
	void update();
	void render();
	void release();

	void setRelaxStatus(int season, int type);

	string getName() { return _name; }
	int getGold() { return _gold; }
};

