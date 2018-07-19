#include "stdafx.h"
#include "dialogManager.h"


dialogManager::dialogManager()
{
}


dialogManager::~dialogManager()
{
}

HRESULT dialogManager::init()
{
	
	return S_OK;
}

void dialogManager::release()
{
}

void dialogManager::update()
{
}

void dialogManager::render()
{
}

void dialogManager::setDialog(string str)
{
	_str = str;
	_idx = _count = 0;
}

string dialogManager::getCurrentDialog()
{
	string temp;
	if(_count < _str.size())
	_count++;
	temp = _str.substr(0, _count);
	return temp;
}

string dialogManager::getTotalDialog()
{
	return _str;
}
