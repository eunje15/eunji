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
	//_test = IMAGEMANAGER->addImage("테스트", "image/prologue/test.bmp", 100, 100, true, RGB(255, 0, 255), true);
	//_rc = RectMakeCenter(50, 50, 10, 10);
	_dataInput = new dataInput;
	_dataInput->init();

	_princess = new princess;
	_princess->init();

	_dataInput->setPrincessAddressLink(_princess);

	//_test = IMAGEMANAGER->addFrameImage("자음", "image/prologue/자음(80x665,2x19).bmp", 80, 665, 2, 19, true, RGB(255, 0, 255));

	//_frameX = _frameY = 0;
	return S_OK;
}

void playGround::release(void)	
{
	gameNode::release();

	
}

void playGround::update(void)	
{
	gameNode::update();

	
	/*if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_frameX < _test->getMaxFrameX())
			_frameX++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_frameX > 0)
			_frameX--;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_frameY < _test->getMaxFrameY())
			_frameY++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_frameY > 0)
			_frameY--;
	}*/
	_dataInput->update();
}

void playGround::render(void)
{
	
	//흰색도화지 한 장 깔아둔다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//////////////////////////////////////////////////////////

	_dataInput->render();
	//_test->frameRender(DC, WINSIZEX / 2, WINSIZEY / 2, _frameX, _frameY);

	//if (_inputData.size())
	//{
	//	list<TCHAR>::iterator iter = _inputData.begin();
	//	string str ="";
	//	for(;iter != _inputData.end(); iter++)
	//	{
	//		//TextOut(DC, 100, 100, *iter, strlen(*iter));
	//		str += *iter;
	//	}
	//	TextOut(DC, 100, 100, str.c_str(), strlen(str.c_str()));
	//}

	/*if(!_isTest)
		_test->render(DC);

	if (KEYMANAGER->isToggleKey(VK_F2))
		Rectangle(DC, _rc.left, _rc.top, _rc.right, _rc.bottom);

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_test->transRender(_test->getMemDC(), _rc.left, _rc.top, _rc.left, _rc.top, 10, 10, true);
		_test->render(DC);
		_isTest ? _isTest = false : _isTest = true;
	}*/

	//_test->alphaRender(DC, 100);
	//////////////////////////////////////////////////////////
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);

}

