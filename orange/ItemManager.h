#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

#include <vector>
#include ".\\deprecated\\zzzitem.h"

struct DATA_ITEM
{
  int guid;
  int slot;
  int type;
  int level;
  double durability;
  int option1;
  int option2;
  int option3;
  int newoption;
  int setoption;
  int setaddstat;
  int petitem_level;
  int petitem_exp;
  int joh_option;
  int joh_strength;
  int joh_dexterity;
  int optionex;
};

class CItemManager
{
public:
	std::vector<int> item_guids;
	CItemManager();
	void LoadCharacterItems();
};

bool LoadItem(DATA_ITEM* item, int guid);

#endif