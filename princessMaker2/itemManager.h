#pragma once
#include "gameNode.h"
#include "item.h"

enum DATA_TYPE { DATA_WEAPON, DATA_ARMOR, DATA_CLOTHES, DATA_GOODS };
class itemManager : public gameNode
{
private:
	vector<item*> _vWeapon;
	vector<item*> _vArmor;
	vector<item*> _vClothes;
	vector<item*> _vGoods;

	DATA_TYPE _type;
public:
	itemManager();
	~itemManager();

	HRESULT init();
	void update();
	void render();
	void release();
	void loadData(const char* dataName);
};

