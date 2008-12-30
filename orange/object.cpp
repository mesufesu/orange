#include "stdafx.h"
#include ".\\object.h"

CObject::CObject()
{
	this->guid = -1;
	type = OBJECT_EMPTY;
	this->teleporting = false;
	this->state = 1;
	this->viewstate = 0;
	this->viewskillstate = 0;

	this->level = 0;
	this->strength = 0;
	this->dexterity = 0;
	this->vitality = 0;
	this->energy = 0;
	this->leadership = 0;

	this->life = 0.0f;
	this->maxlife = 0.0f;
	this->mana = 0.0f;
	this->maxmana = 0.0f;
	this->shield = 0.0f;
	this->maxshield = 0.0f;
	this->bp = 0.0f;
	this->maxbp = 0.0f;
}