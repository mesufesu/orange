#ifndef _ITEM_TEMPLATE_H_
#define _ITEM_TEMPLATE_H_

#include <unordered_map>
#include <QtCore\\QMutex>

struct ITEM_TEMPLATE
{
	uint16 type;
	int32 slot;
	uint16 skill;
	uint8 width;
	uint8 height;
	bool option;
	bool drop;
	std::string name;
	uint16 level;
	uint16 reqlevel;
	uint8 durability;
	uint64 SPECIAL;
	uint16 strength;
	uint16 dexterity;
	uint16 energy;
	uint16 vitality;
	uint16 leadership;
	uint8 set_option;
	uint32 CLASS_ATTR;
	ITEM_TEMPLATE()
	{
		ZeroMemory(this, sizeof(ITEM_TEMPLATE));
		name.clear();
	}
};

class CItemTemplate
{
public:
	typedef std::tr1::unordered_map<uint16, ITEM_TEMPLATE> MapType;
	CItemTemplate();
	bool Load();
	const ITEM_TEMPLATE* Get(uint16 type);
	bool Reload();
private:
	MapType template_container;
	QMutex mtx;
};

extern CItemTemplate ItemTemplate;

#endif