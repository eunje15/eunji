#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum WEAPON_TYPE { WEAPON_FIN, WEAPON_SELECT, WEAPON_CLICK, WEAPON_NONE };

class weaponStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	WEAPON_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[12];
	tagImg _quitImg;
	bool _fin, _selectItem;
public:
	weaponStore();
	~weaponStore();

	HRESULT init();
	void update();
	void render();
	void release();

	void setItem();
	void setDialog(string dialog);
	bool dialogRender();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

