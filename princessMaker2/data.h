#pragma once
struct tagObj
{
	RECT rc;
	bool isData;
	int idX, idY;
	bool isSelected;
};

enum BLOOD_TYPE { BLOOD_A, BLOOD_B, BLOOD_O, BLOOD_AB };
struct tagInfo
{
	string firstName;
	string name;
	int year;
	int mon;
	int day;
	int age;
	BLOOD_TYPE blood;
	string strBlood;
};

struct tagGod
{
	string planet;
	string name;
	string constellation;
};

struct tagStatus
{
	tagGod god;
	int hp;				
	int physical;
	int intelligence;
	int elegance;
	int sexual;
	int morality;
	int faith;
	int sensitivity;
	int warrior;
	int warriorSkill;
	int power;
	int magic;
	int magicSkill;
	int spell;
	int spellDefence;
	int sociality;
	int manner;
	int art;
	int conversation;
	int housework;
	int cooking;
	int cleaning;
	int personality;
	int total;
	string plusNorth;
};

struct tagImg
{
	image* img;
	int x, y;
	int frameX, frameY;
};

struct tagString
{
	string str;
	RECT rc;
	bool isSelected;
};