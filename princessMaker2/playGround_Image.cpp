#include "stdafx.h"
#include "playGround.h"

HRESULT playGround::image_init()
{
	//==================프롤로그=======================
	IMAGEMANAGER->addImage("dadName", "image/prologue/dadName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dadOK", "image/prologue/아빠완료(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));
	IMAGEMANAGER->addImage("princessName", "image/prologue/princessName(800x600).bmp", 800, 600, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("princessOK", "image/prologue/딸완료(120x30,2x1).bmp", 120, 30, 2, 1, false, RGB(0, 0, 0));

	IMAGEMANAGER->addImage("princessCal", "image/prologue/princessCal(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("princessYellow", "image/prologue/princessYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("dadAgeYellow", "image/prologue/dadAgeYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dadAge", "image/prologue/dadAge(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("dadCal", "image/prologue/dadCal(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dadCalYellow", "image/prologue/dadCalYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));


	return S_OK;
}