#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::image_init()
{
	//==================���ѷα� �̸��Է�=======================
	IMAGEMANAGER->addImage("dadName", "image/prologue/dadName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ƺ��Ϸ�", "image/prologue/�ƺ��Ϸ�(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));
	
	IMAGEMANAGER->addImage("princessName", "image/prologue/princessName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ϸ�", "image/prologue/���Ϸ�(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));

	return S_OK;
}