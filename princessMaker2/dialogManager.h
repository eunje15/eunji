#pragma once
#include "singletonBase.h"
class dialogManager : public singletonBase<dialogManager>
{
private:
	string _str;
	int _count, _idx;
public:
	dialogManager();
	~dialogManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setDialog(string str);
	string getCurrentDialog();
	string getTotalDialog();
};

