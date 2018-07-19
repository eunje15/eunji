#include "stdafx.h"
#include "prologueDialog.h"


prologueDialog::prologueDialog()
{
}


prologueDialog::~prologueDialog()
{
}

HRESULT prologueDialog::init()
{
	_scene = SCENE_WAR;
	_whoDialog = DIALOG_NONE;
	_loop = 0;
	setWar();
	return S_OK;
}

void prologueDialog::update()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			if (_loop < 1300)
				_loop += 0.8;
			else
				changeMode();
			break;
		case SCENE_WAR:
			switch (_whoDialog)
			{
				//case DIALOG_DEVIL:
				//
				//break;
				//case DIALOG_KING:
				//
				//break;
				//case DIALOG_GOD:
				//
				//break;
				case DIALOG_NONE: case DIALOG_CONTINUE:
					warUpdate();
				break;
				default:
					//setDialog();
				break;
			}
			break;
		case SCENE_DEVIL_DIALOG:
			break;
		case SCENE_KING_DIALOG:
			break;
		case SCENE_PRINCESS:
			break;
	}
}

void prologueDialog::render()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			prologueRender();
			break;
		case SCENE_WAR:
			warRender();
			break;
		case SCENE_DEVIL_DIALOG:
			break;
		case SCENE_KING_DIALOG:
			break;
		case SCENE_PRINCESS:
			break;
	}
}

void prologueDialog::release()
{
}

void prologueDialog::changeMode()
{
	switch (_scene)
	{
		case SCENE_PROLOGUE:
			_scene = SCENE_WAR;
			setWar();
			break;
		case SCENE_WAR:
			_frameY = 0;
		break;
		//case SCENE_DEVIL_DIALOG:
		//	dialogRender();
		//	break;
		//case SCENE_KING_DIALOG:
		//	break;
		case SCENE_PRINCESS:
			break;
	}
}

void prologueDialog::prologueRender()
{
	IMAGEMANAGER->findImage("prologue")->loopRender(DC, &RectMake(0, 0, WINSIZEX, WINSIZEY), 0, _loop);

	SetTextColor(DC, RGB(255, 255, 255));
	char str[128];
	sprintf_s(str, "루프 %f", _loop);
	TextOut(DC, 50, 100, str, strlen(str));

}

void prologueDialog::warRender()
{
	IMAGEMANAGER->findImage("war")->alphaFrameRender(DC, 0, 0, 0, _frameY, _alpha);

	if ((_whoDialog == DIALOG_NONE) || (_whoDialog == DIALOG_CONTINUE))
	{
		if (!_isRender) return;

		HFONT font, oldFont;
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("Castellar"));
		oldFont = (HFONT)SelectObject(DC, font);
		SetTextColor(DC, RGB(255, 255, 255));
		for (int i = 0; i < 2; i++)
		{
			if (_printDialog[i].size())
				TextOut(DC, WINSIZEX / 2 - _printDialog[i].size() * 5, WINSIZEY - 150 + i * 30, _printDialog[i].c_str(), strlen(_printDialog[i].c_str()));
		}
		SelectObject(DC, oldFont);
		DeleteObject(font);
	}
	else
		dialogRender();
}

void prologueDialog::setWar()
{
	_vDialog = TXTDATA->txtLoad("dialog/dialog.txt");
	//_vDevilDialog = TXTDATA->txtLoad("dialog/마왕다이얼로그.txt");
	//_vKingDialog = TXTDATA->txtLoad("dialog/왕다이얼로그.txt");
	//_vGodDialog = TXTDATA->txtLoad("dialog/신다이얼로그.txt");
	//_whoDialog = DIALOG_NONE;
	_count = _frameY = _isAlpha = 0;
	_isRender = 1;
	_strCount = 0;
	_alpha = 255;

	//임시로 아빠이름~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	_dadName = "대디";

	
	string temp = "(아빠성)";
	for (int i = 0; i < _vDialog.size(); i++)
	{
		size_t pos = 0;
		if ((pos = _vDialog[i].find(temp, pos)) != std::string::npos)
		{
			_vDialog[i].replace(pos, temp.length(), _dadName);
			pos += _dadName.length();
		}
	}
}

void prologueDialog::warUpdate()
{
	if (_whoDialog != DIALOG_NONE) return;

	_count++;
	if (_isAlpha) _alpha -= 2;
	if (!(_count % 100))
	{
		if (_strCount == 3 && _frameY == 0 && _isAlpha)
		{
			_frameY++;
			_isAlpha = false;
			_alpha = 255;
		}
		if (_strCount == 5)
		{
			_whoDialog = DIALOG_DEVIL;
			dialogRender();
			return;
		}
		if (_isRender)
		{
			_isRender = false;
			if(_strCount == 3 && _frameY == 0) _isAlpha = true;
			return;
		}
		_isRender = true;
		if (_strCount >= _vDialog.size()) return;
		
		_printDialog[0].clear();
		_printDialog[1].clear();

		bool isSlash = false;
		for (int i = 0; i < _vDialog[_strCount].size(); i++)
		{
			if (_vDialog[_strCount][i] == '/')
			{
				isSlash = true;
				_printDialog[0] = _vDialog[_strCount].substr(0, i - 1);
				_printDialog[1] = _vDialog[_strCount].substr(i+1, _vDialog[_strCount].size());
				break;
			}
		}
		if (!isSlash) _printDialog[0] = _vDialog[_strCount];
		_strCount++;
	}
}


void prologueDialog::setDialog()
{
	if (_whoDialog == DIALOG_NONE || _whoDialog == DIALOG_CONTINUE) return;

	DIALOG->setDialog(_vDialog[_strCount]);
}

void prologueDialog::dialogRender()
{
	if (_whoDialog == DIALOG_NONE || _whoDialog == DIALOG_CONTINUE) return;

	IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX / 2 - 100, WINSIZEY / 2);
}
