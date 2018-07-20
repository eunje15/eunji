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
	//_whoDialog = DIALOG_NONE;
	//_loop = 0;
	//setWar();
	//_frameY = 1;
	//_strCount = 5;
	_frameY = 0;
	_whoDialog = DIALOG_NONE;
	_progress = FRAME_START;
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
			switch (_progress)
			{
			case DIALOG_START:
				if (_whoDialog != DIALOG_NONE) break;
				if (_frameY == 2 || _frameY == 4 || _frameY == 8 || _frameY == 10)
				{
					_progress = DIALOG_FIN;
					break;
				}
				changePrintDialog();
				if (_frameY == 9) _strCount++;
				_progress = DIALOG_ING;
				/*switch (_frameY)
				{
				case 0:
					break;
				case 1:
					warUpdate();
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				}*/
			break;
			case DIALOG_ING:
				_count++;
				if (!(_count % 10)) //120이 기본
				{
					_count = 0;
					if (_isRender) _progress = DIALOG_FIN;
					else _isRender = true;
				}
			break;
			case DIALOG_FIN:
				_isRender = false;
				switch (_frameY)
				{
				case 0:
					_strCount++;
					if (_strCount < 3)
					{
						_progress = DIALOG_START;
					}
					else
						_progress = FRAME_FIN;
					break;
				case 1:
					_strCount++;
					if (_strCount == 6)
					{
						_whoDialog = DIALOG_DEVIL;
						setDialog();
						_progress = DIALOG_START;
					}
					else if (_strCount == 11)
						_progress = FRAME_FIN;
					else
						_progress = DIALOG_START;
					break;
				case 2:
					_whoDialog = DIALOG_KING;
					setDialog();
					_progress = DIALOG_START;
					break;
				case 3:
					_progress = FRAME_FIN;
					break;
				case 4:
					Sleep(1000);
					_strCount++;
					_progress = FRAME_FIN;
					break;
				case 5:
					_strCount++;
					if (_strCount < 23)
					{
						_progress = DIALOG_START;
					}
					else
						_progress = FRAME_FIN;
					break;
				case 6:
					_strCount++;
					if (_strCount < 24)
					{
						_progress = DIALOG_START;
					}
					else
						_progress = FRAME_FIN;
					break;
				case 7:
					_strCount++;
					if (_strCount < 26)
					{
						_progress = DIALOG_START;
					}
					else
						_progress = FRAME_FIN;
					break;
				case 8:
					_whoDialog = DIALOG_GOD;
					setDialog();
					_progress = DIALOG_START;
					break;
				case 9:
					_strCount++;
					if (_strCount < 37)
					{
						_strCount--;
						_progress = DIALOG_START;
					}
					else
						_progress = FRAME_FIN;
					break;
				case 10:
					_alpha2 += 5;
					if (_alpha2 >= 255)
					{
						_alpha2 = 255;
						_scene = SCENE_PRINCESS;
					}
					break;
				}
				break;
			case FRAME_START:
				_alpha += 30;
				if (_alpha >= 255)
				{
					_alpha = 255;
					_progress = DIALOG_START;
				}
				break;
			case FRAME_FIN:
				_alpha -= 30;
				if (_alpha <= 0)
				{
					_alpha = 0;
					_progress = FRAME_START;
					_frameY++;
					if (_frameY == 9) _alpha2 = 0;
				}
				break;
			}
			//switch (_whoDialog)
			//{
			//	//case DIALOG_DEVIL:
			//	//
			//	//break;
			//	//case DIALOG_KING:
			//	//
			//	//break;
			//	//case DIALOG_GOD:
			//	//
			//	//break;
			//	case DIALOG_NONE: case DIALOG_CONTINUE:
			//		warUpdate();
			//	break;
			//	default:
			//		//setDialog();
			//	break;
			//}
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
			char str[128];
			sprintf_s(str, "str : %d, _frameY : %d", _strCount, _frameY);
			TextOut(DC, 200, 200, str, strlen(str));
			switch (_whoDialog)
			{
				case DIALOG_DEVIL:
					dialogRender();
				break;
				case DIALOG_KING:
				break;
				case DIALOG_GOD:
				break;
				case DIALOG_NONE: case DIALOG_CONTINUE:
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
	if (_frameY == 10) IMAGEMANAGER->findImage("princessMaker")->alphaRender(DC, 0, 0, _alpha2);

	if ((_whoDialog == DIALOG_NONE) || (_whoDialog == DIALOG_CONTINUE))
	{
		if (!_isRender) return;

		HFONT font, oldFont;
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("Castellar"));
		oldFont = (HFONT)SelectObject(DC, font);
		if(_frameY >= 7 && _frameY < 9) SetTextColor(DC, RGB(0, 0, 0));
		else SetTextColor(DC, RGB(255, 255, 255));
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
	_alpha = 0;

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
	/*_count++;

	if (!(_count % 100))
	{
		_count = 0;

		if (_isRender)
		{
			_isRender = false;
			return;
		}

		_isRender = true;


		changePrintDialog();
	}*/
}

void prologueDialog::changePrintDialog()
{
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
			_printDialog[1] = _vDialog[_strCount].substr(i + 1, _vDialog[_strCount].size());
			break;
		}
	}
	if (!isSlash) _printDialog[0] = _vDialog[_strCount];
}

void prologueDialog::setDialog()
{
	if (_whoDialog == DIALOG_NONE || _whoDialog == DIALOG_CONTINUE) return;

	if(_whoDialog == DIALOG_DEVIL)
		DIALOG->setDialog(_vDialog[_strCount], 5);
	else if (_whoDialog == DIALOG_KING)
		DIALOG->setDialog(_vDialog[_strCount], 3);
	else if(_whoDialog == DIALOG_GOD)
		DIALOG->setDialog(_vDialog[_strCount], 5);
}

void prologueDialog::dialogRender()
{
	if (_whoDialog == DIALOG_NONE || _whoDialog == DIALOG_CONTINUE) return;

	IMAGEMANAGER->findImage("war")->alphaFrameRender(DC, 0, 0, 0, _frameY, _alpha);

	IMAGEMANAGER->findImage("frame")->render(DC, WINSIZEX / 2 - 200, WINSIZEY / 2 - 100);
	IMAGEMANAGER->findImage("dialogFrame")->render(DC, WINSIZEX / 2 - 58, WINSIZEY / 2 - 100);
	if (_whoDialog == DIALOG_DEVIL)
		IMAGEMANAGER->findImage("monFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 8, 1);
	else if (_whoDialog == DIALOG_KING)
	{
		if(_strCount == 14)
			IMAGEMANAGER->findImage("peopleFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 0, 2);
		else
			IMAGEMANAGER->findImage("peopleFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 1, 2);
	}
	else if(_whoDialog == DIALOG_GOD)
		IMAGEMANAGER->findImage("godFace")->frameRender(DC, WINSIZEX / 2 - 190, WINSIZEY / 2 - 90, 0, 0);

	string str = DIALOG->getCurrentDialog();
	if (str == "end")
	{
		/*_strCount++;
		if (_strCount == 9 || _strCount == 16)
		{
			if (_strCount == 16)
				_strCount--;
			changePrintDialog();
			_whoDialog = DIALOG_NONE;
			_scene = SCENE_WAR;
			if (_strCount == 16 && _frameY == 2) _isAlpha = true;
		}
		else
			setDialog();*/
		_strCount++;
		if (_whoDialog == DIALOG_DEVIL)
		{
			if (_strCount < 9) setDialog();
			else
			{
				_progress = DIALOG_START;
				_whoDialog = DIALOG_NONE;
			}
		}
		else if (_whoDialog == DIALOG_KING)
		{
			if (_strCount < 16) setDialog();
			else
			{
				_progress = FRAME_FIN;
				_whoDialog = DIALOG_NONE;
			}
		}
		else if (_whoDialog == DIALOG_GOD)
		{
			if (_strCount < 36) setDialog();
			else
			{
				_progress = FRAME_FIN;
				_whoDialog = DIALOG_NONE;
			}
		}
	}
	else
	{
		SetTextColor(DC, RGB(255, 255, 255));
		if(str.size() <= 30)
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, str.c_str(), strlen(str.c_str()));
		else if (str.size() <= 60)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, str.size() - 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
		}
		else if (str.size() <= 90)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(61, str.size() - 61);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 30, temp.c_str(), strlen(temp.c_str()));
		}
		else if (str.size() <= 120)
		{
			string temp = str.substr(0, 31);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 90, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(31, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 60, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(61, 30);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2 - 30, temp.c_str(), strlen(temp.c_str()));
			temp = str.substr(91, str.size() - 91);
			TextOut(DC, WINSIZEX / 2 - 55, WINSIZEY / 2, temp.c_str(), strlen(temp.c_str()));
		}
	}
}
