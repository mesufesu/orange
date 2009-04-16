#include "stdafx.h"
#include "Database.h"
#include "UnitTemplate.h"

CUnitTemplate UnitTemplate;

CUnitTemplate::CUnitTemplate()
{
	this->container.clear();
}

bool CUnitTemplate::Load()
{
	Log.String("Loading unit templates...");
	QSqlQuery q(data_db.db);
	data_db.LockForRead();
	if(!q.exec("SELECT `type`, `model_id`, `rate`, `name`, `level`, `health`, `mana`, `damage_min`, `damage_max`, `defense`, `magic_defense`, `attack_rating`, `block`, `move_range`, `attack_type`, `attack_range`, `view_range`, `move_speed`, `attack_speed`, `respawn_time`, `attribute`, `item_rate`, `money_rate`, `max_item_level`, `skill`, `resistance` FROM `unit_template`;"))
	{
		Log.String("Something wrong with `unit_template`.");
		data_db.Unlock();
		return false;
	}
	data_db.Unlock();
	UNIT_TEMPLATE ut;
	this->mtx.lock();
	while(q.next())
	{
		ut.type = q.value(0).toUInt();
		ut.model_id = q.value(1).toUInt();
		ut.rate = q.value(2).toUInt();
		ut.name = q.value(3).toString().toStdString();
		ut.level = q.value(4).toUInt();
		ut.health = q.value(5).toUInt();
		ut.mana = q.value(6).toUInt();
		ut.damage_min = q.value(7).toUInt();
		ut.damage_max = q.value(8).toUInt();
		ut.defense = q.value(9).toUInt();
		ut.magic_defense = q.value(10).toUInt();
		ut.attack_rating = q.value(11).toUInt();
		ut.block = q.value(12).toUInt();
		ut.move_range = q.value(13).toUInt();
		ut.attack_type = q.value(14).toUInt();
		ut.attack_range = q.value(15).toUInt();
		ut.view_range = q.value(16).toUInt();
		ut.move_speed = q.value(17).toUInt();
		ut.attack_speed = q.value(18).toUInt();
		ut.respawn_time = q.value(19).toUInt();
		ut.attribute = q.value(20).toUInt();
		ut.item_rate = q.value(21).toUInt();
		ut.money_rate = q.value(22).toUInt();
		ut.max_item_level = q.value(23).toUInt();
		ut.skill = q.value(24).toUInt();
		ut.resistance = q.value(25).toUInt();
		this->container.insert(MapType::value_type(ut.type, ut));
		ZeroMemory(&ut, sizeof(ut));
	}
	this->mtx.unlock();
	Log.String("> Loaded %u unit templates.", this->container.size());
	return true;
}

const UNIT_TEMPLATE* CUnitTemplate::Get(uint32 type)
{
	if(type >= 0)
	{
		this->mtx.lock();
		this->mtx.unlock();
		MapType::iterator it = this->container.find(type);
		if(it != this->container.end())
		{
			return &(it->second);
		}
	}
	return NULL;
}