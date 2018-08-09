#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapTool : public gameNode
{
private:
	tagTile _tile[TILEX*TILEY];
	tagSampleTile _sampleTile[SAMPLE_TILEX*SAMPLE_TILEY];
	TERRAIN _terrain;
	OBJECT _obj;
	bool _isSetObj;
	vector<pair<RECT, OBJECT>> _objRect;
	RECT _selectBox[5];
public:
	mapTool();
	~mapTool();

	HRESULT init();
	void update();
	void render();
	void release();

	void setup();
	void setObject();
	void save();
	void load();
};

