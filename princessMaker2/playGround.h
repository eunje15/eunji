#pragma once
#include "gameNode.h"
#include "dataInput.h"
#include "princess.h"

class playGround : public gameNode
{
private:
	dataInput* _dataInput;
	princess* _princess;

	image* _test;
	int _frameX, _frameY;
	RECT _rc;
	bool _isTest;
public:
	virtual HRESULT init(void);
	virtual HRESULT image_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
};

