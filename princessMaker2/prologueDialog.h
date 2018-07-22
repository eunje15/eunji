#pragma once
#include "gameNode.h"
#include "princess.h"

enum SCENE_TYPE { SCENE_PROLOGUE, SCENE_WAR, SCENE_PRINCESS };
enum DIALOG_TYPE { DIALOG_DEVIL, DIALOG_KING, DIALOG_GOD, DIALOG_NONE };
enum DIALOG_PROGRESS { DIALOG_START, DIALOG_ING, DIALOG_FIN, FRAME_START, FRAME_FIN };
class prologueDialog :	public gameNode
{
private:
	princess* _princess;

	float _loop;
	SCENE_TYPE _scene;
	DIALOG_TYPE _whoDialog;
	DIALOG_PROGRESS _progress;

	int _frameY, _count, _strCount;
	bool _isRender;
	vector<string> _vDialog;

	string _printDialog[2];
	bool _isAlpha;
	int _alpha, _alpha2;
	string _godPlanet,_godName, _dadName;
	int _godIndex;

public:
	prologueDialog();
	~prologueDialog();

	HRESULT init();
	void update();
	void render();
	void release();

	void changeMode();
	void changePrintDialog();

	void setGodPhoto();
	void setWar();
	void setDialog();

	void prologueRender();
	void warRender();
	void dialogRender();

	void setDadName(string dadName) { _dadName = dadName; }
};

