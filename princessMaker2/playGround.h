#pragma once
#include "gameNode.h"
#include "dataInput.h"
#include "princess.h"
#include "prologueDialog.h"


class playGround : public gameNode
{
private:
	dataInput* _dataInput;
	princess* _princess;
	prologueDialog* _prologue;

	image* _test;
	int _frameX, _frameY;
	RECT _rc;
	bool _isTest;
	vector<string> _str;

public:
	virtual HRESULT init(void);
	virtual HRESULT image_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
};

