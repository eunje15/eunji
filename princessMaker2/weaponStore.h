#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum STORE_DIALOG_TYPE { STORE_DIALOG_FIN, STORE_DIALOG_SELECT, STORE_DIALOG_CLICK, STORE_DIALOG_NONE };

class weaponStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	STORE_DIALOG_TYPE _dialogType;
	tagString _chooseBox[2];
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

