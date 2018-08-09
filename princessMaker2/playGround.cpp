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

	SCENEMANAGER->addScene("�������Է�", new dataInput);
	SCENEMANAGER->addScene("���ѷα�", new prologueDialog);
	SCENEMANAGER->addScene("���־�", new princessScene);
	
	SCENEMANAGER->changeScene("���־�");
	_str = TXTDATA->txtLoadCsv("dialog/���ڸ��ɷ�ġ.csv", "ó���ڸ�");

	//SCENEMANAGER->addScene("�׽�Ʈ", new testClass);
	//SCENEMANAGER->changeScene("�׽�Ʈ");

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
	
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	SCENEMANAGER->render();
	
	//////////////////////////////////////////////////////////
	//TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

