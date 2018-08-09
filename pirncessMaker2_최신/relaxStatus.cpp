#include "stdafx.h"
#include "relaxStatus.h"


relaxStatus::relaxStatus()
{
}


relaxStatus::~relaxStatus()
{
}

HRESULT relaxStatus::init()
{
	return S_OK;
}

void relaxStatus::update()
{
}

void relaxStatus::render()
{
}

void relaxStatus::release()
{
}

void relaxStatus::setRelaxStatus(int season, int type)
{
	_type = (RELAX_TYPE)type;
	_season = season;
	switch (_type)
	{
	case FREE_NOGOLD:
		_name = "자유행동";
		_sensitivity = 0;
		_stress = -1;
	break;
	case FREE_GOLD:
		_name = "자유행동";
		_sensitivity = 0;
		_stress = -2;
		_gold = 10;
	break;
	case VACATION_SEA:
		_name = "바캉스";
		if (season == 0){
			_stress = -3;
			_gold = 10;
		}
		else if (season == 1){
			_stress = -6;
			_weight = -0.1;
			_gold = 10;
		}
		else if (season == 2){
			_stress = -3;
			_gold = 10;
		}
		else if (season == 3){
			_stress = -2;
			_gold = 10;
		}				
	break;
	case VACATION_MOUNTAIN:
		_name = "바캉스";
		if (season == 0) {
			_sensitivity = 1;
			_stress = -3;
			_gold = 10;
		}
		else if (season == 1) {
			_sensitivity = 1;
			_stress = -3;
			_gold = 10;
		}
		else if (season == 2) {
			_weight = 0.1;
			_stress = -6;
			_sensitivity = 2;
			_gold = 10;
		}
		else if (season == 3) {
			_sensitivity = 1;
			_stress = -3;
			_gold = 10;
		}
	break;
	}
}
