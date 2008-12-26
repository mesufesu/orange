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
}