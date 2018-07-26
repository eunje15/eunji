#pragma once
#include "gameNode.h"
#include "data.h"

enum SAVELOAD_TYPE {SAVELOAD_FIN, SAVELOAD_SAVE, SAVELOAD_LOAD, SAVELOAD_NONE};

class princess;

class saveLoadScene : public gameNode
{
private:
	princess * _princess;

	tagImg _npc;
	vector<string> _vDialog;
	int _dialogIdx;
	DIALOG_TYPE _dialogType;
	SAVELOAD_TYPE _type;
	tagString _chooseBox[3];
	tagImg _saveLoadInfo[10];
	bool _fin;
	string _godName, _godPlanet;
public:
	saveLoadScene();
	~saveLoadScene();

	HRESULT init();
	void update();
	void render();
	void release();

	void saveData(int idx);

	void setDialog(string dialog);
	bool dialogRender();

	void setGodPhoto();

	bool getFin() { return _fin; }
	void setFin(bool fin) { _fin = fin; }
};

