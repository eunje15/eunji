#pragma once
#include "gameNode.h"
#include "dataInput.h"

class playGround : public gameNode
{
private:
	dataInput* _dataInput;

	image* _test;
	int _frameX, _frameY;

public:
	virtual HRESULT init(void);
	virtual HRESULT image_init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	playGround();
	~playGround();
};

