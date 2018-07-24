#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum WEAPON_DIALOG_TYPE { WEAPON_DIALOG_FIN, WEAPON_DIALOG_SELECT, WEAPON_DIALOG_CLICK, WEAPON_DIALOG_NONE };

class weaponStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	WEAPON_DIALOG_TYPE _dialogType;
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

