#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_type = DATA_WEAPON;
	loadData("dialog/weapon2.csv");
	return S_OK;
}

void itemManager::update()
{
}

void itemManager::render()
{
}

void itemManager::release()
{
}

void itemManager::loadData(const char* dataName)
{
	vector<string> vStr = TXTDATA->txtLoadCsv(dataName);
	
	for (int i = 0; i < vStr.size(); i++)
	{
		char str[100000];
		strcpy(str, vStr[i].c_str());
		vector<string> temp = TXTDATA->charArraySeparation(str);
		item* tItem = new item;
		vector<pair<string, float>> property;
		for (int j = 3; j < temp.size() - 1; j += 2)
		{
			property.push_back(make_pair(temp[j], atof(temp[j + 1].c_str())));
		}
		switch (_type)
		{
		case DATA_WEAPON:
			tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 0, i, 0);
			_vWeapon.push_back(tItem);
			break;
		case DATA_ARMOR:
			tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 1, i, 0);
			_vArmor.push_back(tItem);
			break;
		case DATA_CLOTHES:
			tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 2, i, 0);
			_vClothes.push_back(tItem);
			break;
		case DATA_GOODS:
			tItem->setItem(temp[0], atoi(temp[1].c_str()), property, 3, i, 0);
			_vGoods.push_back(tItem);
			break;
		}
	}
}
