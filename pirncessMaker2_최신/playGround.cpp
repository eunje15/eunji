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
	
	_princess = new princess;
	_princess->init();

	SCENEMANAGER->setPrincessAddressLink(_princess);

	SCENEMANAGER->addScene("데이터입력", new dataInput);
	SCENEMANAGER->addScene("프롤로그", new prologueDialog);
	SCENEMANAGER->addScene("공주씬", new princessScene);
	
	SCENEMANAGER->changeScene("공주씬");
	_str = TXTDATA->txtLoadCsv("dialog/별자리능력치.csv", "처녀자리");

	//SCENEMANAGER->addScene("테스트", new testClass);
	//SCENEMANAGER->changeScene("테스트");

	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	
	//흰색도화지 한 장 깔아둔다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	SCENEMANAGER->render();
	
	//////////////////////////////////////////////////////////
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

