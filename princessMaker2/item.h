#pragma once
#include "gameNode.h"

enum ITEM_TYPE { ITEM_WEAPON, ITEM_ARMOR, ITEM_CLOTHES, ITEM_COOK, ITEM_GOODS };
class item : public gameNode
{
private:
	string _name;
	int _price;
	ITEM_TYPE _type;
	int _frameX, _frameY;
	image* _img;
	vector<pair<string, float>> _property;
	bool _isWear;
	float _x, _y;
	bool _isStore;
public:
	item();
	~item();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem(string name, int price, bool isStore, vector<pair<string, float>> property, int type, int frameX, int frameY);
	void setImage();
	void setXY(float x, float y);
	float getX() { return _x; }
	float getY() { return _y; }

	string getName() { return _name; }
	int getPrice() { return _price; }
	vector<pair<string, float>> getProperty() { return _property; }
	bool getIsStore() { return _isStore; }
};

