#pragma once
#include "gameNode.h"

enum SCENE_TYPE { SCENE_PROLOGUE, SCENE_WAR, SCENE_DEVIL_DIALOG, SCENE_KING_DIALOG, SCENE_PRINCESS };
enum DIALOG_TYPE { DIALOG_DEVIL, DIALOG_KING, DIALOG_GOD, DIALOG_NONE, DIALOG_CONTINUE };
class prologueDialog :	public gameNode
{
private:
	float _loop;
	SCENE_TYPE _scene;
	DIALOG_TYPE _whoDialog;
	int _frameY, _count, _strCount;
	bool _isRender;
	vector<string> _vDialog;
	vector<string> _vDevilDialog;
	vector<string> _vKingDialog;
	vector<string> _vGodDialog;
	string _printDialog[2];
	string _dadName;
	bool _isAlpha;
	int _alpha;
public:
	prologueDialog();
	~prologueDialog();

	HRESULT init();
	void update();
	void render();
	void release();

	void changeMode();
	void prologueRender();
	void warRender();
	void setWar();
	void warUpdate();

	void setDialog();

	void dialogRender();

	void setDadName(string dadName) { _dadName = dadName; }
};

