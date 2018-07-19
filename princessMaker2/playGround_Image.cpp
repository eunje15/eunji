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

	IMAGEMANAGER->addImage("dadCal", "image/prologue/dadCal2(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("dadCalYellow", "image/prologue/dadCalYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("princessBlood", "image/prologue/princessBlood(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("princessBloodYellow", "image/prologue/princessBloodYellow(800x600).bmp", 800, 600, false, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("prologue", "image/prologue/prologue(800x2000).bmp", 800, 2000, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("war", "image/prologue/prologue(800x4200,1x7).bmp", 800, 4200, 1, 7, false, RGB(255, 0, 255), true);

	IMAGEMANAGER->addFrameImage("godFace", "image/prologue/godFace(1200x130,10x1).bmp", 1200, 130, 10, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("frame", "image/prologue/dialogFace(140x150).bmp", 140, 150, false, RGB(255, 0, 255));
	return S_OK;
}