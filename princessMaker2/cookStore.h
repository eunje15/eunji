#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum COOK_DIALOG_TYPE { COOK_DIALOG_FIN, COOK_DIALOG_SELECT, COOK_DIALOG_CLICK, COOK_DIALOG_NONE };


class cookStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	COOK_DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[3];
	tagImg _quitImg;
	bool _fin, _selectItem;

public:
	cookStore();
	~cookStore();

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

