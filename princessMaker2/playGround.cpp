#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init(void)	
{
	gameNode::init(true);

	

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();


}

void playGround::render(void)
{
	
	//Èò»öµµÈ­Áö ÇÑ Àå ±ò¾ÆµÐ´Ù
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	
	


	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

