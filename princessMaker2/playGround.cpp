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
	image_init();
	
	_dataInput = new dataInput;
	_dataInput->init();

	_princess = new princess;
	_princess->init();

	_prologue = new prologueDialog;
	_prologue->init();

	_dataInput->setPrincessAddressLink(_princess);
	
	_str = TXTDATA->txtLoadCsv("dialog/º°ÀÚ¸®´É·ÂÄ¡.csv", "Ã³³àÀÚ¸®");

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

	_prologue->update();
	
	_dataInput->update();
}

void playGround::render(void)
{
	
	//Èò»öµµÈ­Áö ÇÑ Àå ±ò¾ÆµÐ´Ù
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	//_dataInput->render();
	_prologue->render();
	
	//////////////////////////////////////////////////////////
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

