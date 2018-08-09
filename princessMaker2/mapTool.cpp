#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	IMAGEMANAGER->addFrameImage("sampleMap", "image/field/e_samplemap(320x1680,16x84).bmp", 320, 1680, 16, 84, false, RGB(255, 0, 255));
	
	_isSetObj = true;

	setup();
	
	return S_OK;
}

void mapTool::update()
{
	if (_isSetObj)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) setObject();
		if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
		{
			for (int i = 0; i < SAMPLE_TILEX*SAMPLE_TILEY; i++)
			{
				if (PtInRect(&_sampleTile[i].rc, _ptMouse))
				{
					_sampleTile[i].object = OBJ_NONE;
					InvalidateRect(_hWnd, NULL, false);
					break;
				}
			}
		}
	}
}

void mapTool::render()
{
	if (_isSetObj)
	{
		for (int i = 3; i < 5; i++)
		{
			Rectangle(DC, _selectBox[i].left, _selectBox[i].top, _selectBox[i].right, _selectBox[i].bottom);
		}

		DrawText(DC, TEXT("save"), strlen("save"), &_selectBox[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DrawText(DC, TEXT("load"), strlen("load"), &_selectBox[4], DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		for (int i = 0; i < SAMPLE_TILEY * SAMPLE_TILEX; i++)
		{
			IMAGEMANAGER->findImage("sampleMap")->frameRender(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].frameX, _sampleTile[i].frameY);
		}

		for (int i = 0; i < _objRect.size(); i++)
		{
			Rectangle(DC, _objRect[i].first.left, _objRect[i].first.top, _objRect[i].first.right, _objRect[i].first.bottom);
			switch (_objRect[i].second)
			{
			case OBJ_WOOD:
				DrawText(DC, TEXT("OBJ_WOOD"), strlen("OBJ_WOOD"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CASTLE:
				DrawText(DC, TEXT("OBJ_CASTLE"), strlen("OBJ_CASTLE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_DOWN1:
				DrawText(DC, TEXT("OBJ_HALL_DOWN1"), strlen("OBJ_HALL_DOWN1"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_UP1:
				DrawText(DC, TEXT("OBJ_HALL_UP1"), strlen("OBJ_HALL_UP1"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_DOWN2:
				DrawText(DC, TEXT("OBJ_HALL_DOWN2"), strlen("OBJ_HALL_DOWN2"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_HALL_UP2:
				DrawText(DC, TEXT("OBJ_HALL_UP2"), strlen("OBJ_HALL_UP2"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CIENAGA_DOWN:
				DrawText(DC, TEXT("OBJ_CIENAGA_DOWN"), strlen("OBJ_CIENAGA_DOWN"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CIENAGA_UP:
				DrawText(DC, TEXT("OBJ_CIENAGA_UP"), strlen("OBJ_CIENAGA_UP"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_NOTICE:
				DrawText(DC, TEXT("OBJ_NOTICE"), strlen("OBJ_NOTICE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_STONE:
				DrawText(DC, TEXT("OBJ_STONE"), strlen("OBJ_STONE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_TREASURE:
				DrawText(DC, TEXT("OBJ_TREASURE"), strlen("OBJ_TREASURE"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_ETC:
				DrawText(DC, TEXT("OBJ_ETC"), strlen("OBJ_ETC"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			case OBJ_CRIMINAL:
				DrawText(DC, TEXT("OBJ_CRIMINAL"), strlen("OBJ_CRIMINAL"), &_objRect[i].first, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
		}
		if (KEYMANAGER->isToggleKey(VK_TAB))
		{
			for (int i = 0; i < SAMPLE_TILEY * SAMPLE_TILEX; i++)
			{
					Rectangle(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, _sampleTile[i].rc.right, _sampleTile[i].rc.bottom);
					char str[128];
					sprintf_s(str, "%d", (int)_sampleTile[i].object);
					TextOut(DC, _sampleTile[i].rc.left, _sampleTile[i].rc.top, str, strlen(str));
			}
		}
	}
}

void mapTool::release()
{
}

void mapTool::setup()
{
	if (_isSetObj)
	{
		for (int i = 0; i < SAMPLE_TILEY; i++)
		{
			for (int j = 0; j < SAMPLE_TILEX; j++)
			{
				_sampleTile[i * SAMPLE_TILEX + j].frameX = j;
				_sampleTile[i * SAMPLE_TILEX + j].frameY = i;

				_sampleTile[i*SAMPLE_TILEX + j].object = OBJ_NONE;

				SetRect(&_sampleTile[i*SAMPLE_TILEX + j].rc, j*SAMPLE_TILE_SIZE, i*SAMPLE_TILE_SIZE, 
					SAMPLE_TILE_SIZE + j * SAMPLE_TILE_SIZE, SAMPLE_TILE_SIZE + i * SAMPLE_TILE_SIZE);
			}
		}

		for (int i = 0; i < 5; i++)
		{
			if (i < 3)
				_selectBox[i] = RectMake(0, 0, 0, 0);
			else
				_selectBox[i] = RectMake(500 + i * 50, 50, 40, 20);
		}

		for (int i = 1; i < 14; i++)
		{
			RECT rc = RectMake(450 + (i % 2) * 160, 100 + (i / 2) * 50, 150, 30);
			_objRect.push_back(make_pair(rc, (OBJECT)i));
		}
	}
}

void mapTool::setObject()
{
	for (int i = 3; i < 5; i++)
	{
		if (PtInRect(&_selectBox[i], _ptMouse))
		{
			if (i == 3)
			{
				save();
				break;
			}
			if (i == 4)
			{
				load();
				break;
			}
		}
	}

	for (int i = 0; i < _objRect.size(); i++)
	{
		if (PtInRect(&_objRect[i].first, _ptMouse))
		{
			_obj = _objRect[i].second;
			break;
		}
	}

	for (int i = 0; i < SAMPLE_TILEX * SAMPLE_TILEY; i++)
	{
		if (PtInRect(&_sampleTile[i].rc, _ptMouse))
		{
			_sampleTile[i].object = _obj;
			InvalidateRect(_hWnd, NULL, false);
			break;
		}
	}
}


void mapTool::save()
{
	HANDLE	file;
	DWORD	save;

	file = CreateFile(FILENAME, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLE_TILEX * SAMPLE_TILEY, &save, NULL);

	CloseHandle(file);
}

void mapTool::load()
{
	HANDLE	file;
	DWORD	load;

	file = CreateFile(FILENAME, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _sampleTile, sizeof(tagSampleTile) * SAMPLE_TILEX * SAMPLE_TILEY, &load, NULL);

	CloseHandle(file);
}