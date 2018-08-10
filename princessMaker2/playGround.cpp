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
	_cameraCenter = PointMake(WINSIZEX / 2, WINSIZEY / 2);

	image_init();
	
	_princess = new princess;
	_princess->init();

	/*SCENEMANAGER->setPrincessAddressLink(_princess);

	SCENEMANAGER->addScene("데이터입력", new dataInput);
	SCENEMANAGER->addScene("프롤로그", new prologueDialog);
	SCENEMANAGER->addScene("공주씬", new princessScene);
	
	SCENEMANAGER->changeScene("공주씬");
	_str = TXTDATA->txtLoadCsv("dialog/별자리능력치.csv", "처녀자리");*/

	/*SCENEMANAGER->addScene("테스트", new testClass);
	SCENEMANAGER->changeScene("테스트");
*/
	SCENEMANAGER->addScene("맵툴", new mapTool);
	SCENEMANAGER->changeScene("맵툴");

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

	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_cameraCenter.y -= 50;
		if (_cameraCenter.y < WINSIZEY / 2)
			_cameraCenter.y = WINSIZEY / 2;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_cameraCenter.y += 50;
		if (_cameraCenter.y > 1600 - WINSIZEY / 2)
			_cameraCenter.y = 1600 - WINSIZEY / 2;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_cameraCenter.x -= 50;
		if (_cameraCenter.x < WINSIZEX / 2)
			_cameraCenter.x = WINSIZEX / 2;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_cameraCenter.x += 50;
		if (_cameraCenter.x > 4000 - WINSIZEX / 2)
			_cameraCenter.x = 4000 - WINSIZEX / 2;
	}
}

void playGround::render(void)
{
	//흰색도화지 한 장 깔아둔다
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(getMemDC(), _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY, WHITENESS);
	PatBlt(_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	SCENEMANAGER->render();

	char str[128];
	sprintf_s(str, "%d,%d", _ptMouse.x, _ptMouse.y);
	TextOut(_camera->getMemDC(), 700, 20, str,strlen(str));
	//////////////////////////////////////////////////////////
	//TIMEMANAGER->render(getMemDC());
	GdiTransparentBlt(this->getBackBuffer()->getMemDC(), _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY,
		_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(255, 255, 255));
	this->getBackBuffer()->render(getHDC(), 0, 0, _cameraCenter.x - WINSIZEX / 2, _cameraCenter.y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	//this->getBackBuffer()->render(getHDC(), 0, 0);
}

