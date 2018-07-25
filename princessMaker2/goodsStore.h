#pragma once
#include "gameNode.h"
#include "item.h"
#include "data.h"

enum GOODS_TYPE { GOODS_FIN, GOODS_SELECT, GOODS_CLICK, GOODS_NONE };

class goodsStore : public gameNode
{
private:
	vector<item*> _vItem;
	tagImg	_npc;
	vector<string> _vDialog;
	int _dialogIdx;
	GOODS_TYPE _type;
	DIALOG_TYPE _dialogType;
	tagString _chooseBox[3], _buyBox[3];
	tagImg _itemImg[6];
	tagImg _quitImg;
	bool _fin, _selectItem;

public:
	goodsStore();
	~goodsStore();

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

