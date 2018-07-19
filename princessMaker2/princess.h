#pragma once
#include "gameNode.h"
#include "data.h"
class princess : public gameNode
{
private:
	tagInfo _info;

	
public:
	princess();
	~princess();

	HRESULT init();
	void update();
	void render();
	void release();

	void setInfo(tagInfo info){	_info = info; }
	tagInfo getInfo() { return _info; }
};

