#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum CLOTHES_DIALOG_TYPE { CLOTHES_DIALOG_FIN, CLOTHES_DIALOG_SELECT, CLOTHES_DIALOG_CLICK, CLOTHES_DIALOG_NONE };

class clothesStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	CLOTHES_DIALOG_TYPE _dialogType;
	tagString _chooseBox[2], _buyBox[3];
	tagImg _itemImg[6];
	tagImg _quitImg;
	bool _fin, _selectItem;
public:
	clothesStore();
	~clothesStore();

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

