#ifndef __MAPCLASS_H_
#define __MAPCLASS_H_

#include ".\\zzzpath.h"
#include ".\\MapItem.h"

#define MAX_MAPS 60

enum MAP_INDEX
{
  MAP_INDEX_LORENCIA = 0,
  MAP_INDEX_DUNGEON = 1,
  MAP_INDEX_DEVIAS = 2,
  MAP_INDEX_NORIA = 3,
  MAP_INDEX_LOSTTOWER = 4,
  MAP_INDEX_RESERVED = 5,
  MAP_INDEX_BATTLESOCCER = 6,
  MAP_INDEX_ATHLANSE = 7,
  MAP_INDEX_TARKAN = 8,
  MAP_INDEX_DEVILSQUARE = 9,
  MAP_INDEX_ICARUS = 10,
  MAP_INDEX_BLOODCASTLE1 = 11,
  MAP_INDEX_BLOODCASTLE2 = 12,
  MAP_INDEX_BLOODCASTLE3 = 13,
  MAP_INDEX_BLOODCASTLE4 = 14,
  MAP_INDEX_BLOODCASTLE5 = 15,
  MAP_INDEX_BLOODCASTLE6 = 16,
  MAP_INDEX_BLOODCASTLE7 = 17,
  MAP_INDEX_CHAOSCASTLE1 = 18,
  MAP_INDEX_CHAOSCASTLE2 = 19,
  MAP_INDEX_CHAOSCASTLE3 = 20,
  MAP_INDEX_CHAOSCASTLE4 = 21,
  MAP_INDEX_CHAOSCASTLE5 = 22,
  MAP_INDEX_CHAOSCASTLE6 = 23,
  MAP_INDEX_KALIMA1 = 24,
  MAP_INDEX_KALIMA2 = 25,
  MAP_INDEX_KALIMA3 = 26,
  MAP_INDEX_KALIMA4 = 27,
  MAP_INDEX_KALIMA5 = 28,
  MAP_INDEX_KALIMA6 = 29,
  MAP_INDEX_CASTLESIEGE = 30,
  MAP_INDEX_CASTLEHUNTZONE = 31,
  MAP_INDEX_DEVILSQUARE2 = 32,
  MAP_INDEX_AIDA = 33,
  MAP_INDEX_CRYWOLF_FIRSTZONE = 34,
  MAP_INDEX_CRYWOLF_SECONDZONE = 35,
  MAP_INDEX_KALIMA7 = 36,
  MAP_INDEX_KANTURU1 = 37,
  MAP_INDEX_KANTURU2 = 38,
  MAP_INDEX_KANTURU_BOSS = 39,
  MAP_INDEX_SILENT = 40,
  MAP_INDEX_BALGASS = 41,
  MAP_INDEX_BARRACK = 42,
  MAP_INDEX_DUMMY1 = 43,
  MAP_INDEX_DUMMY2 = 44,
  MAP_INDEX_ILLUSIONTEMPLE1 = 45,
};

class MapClass
{
public:
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char m_Weather;
  /*<thisrel this+0x5>*/ /*|0x1|*/ unsigned char m_WeatherVariation;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long m_WeatherTimer;
  /*<thisrel this+0xc>*/ /*|0x4|*/ unsigned long m_NextWeatherTimer;
  /*<thisrel this+0x10>*/ /*|0x4|*/ unsigned char* m_attrbuf;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int m_width;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_height;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ PATH* path;
  /*<thisrel this+0x20>*/ /*|0x50dc0|*/ CMapItem m_cItem[300];
  /*<thisrel this+0x50de0>*/ /*|0x4|*/ int m_ItemCount;
  /*<thisrel this+0x50de4>*/ /*|0x280|*/ tagRECT gRegenRect[60];
  /*<thisrel this+0x51064>*/ /*|0x4|*/ int thisMapNumber;

  void IndexAutoPlus();
  void SaveItemInfo();
  void GetLevelPos(short level, short* ox, short* oy);
  void GetMapPos(short Map, short* ox, short* oy);
  void GetRandomLengthPos(short& x, short& y, int length);
  void SearchStandAttr(short& x, short& y);
  int AttrLoad(char* filename);
  void LoadMapAttr(char* filename, int MapNumber);
  int CheckWall(int sx1, int sy1, int sx2, int sy2);
  unsigned char CheckWall2(int sx1, int sy1, int sx2, int sy2);
  void ItemInit();
  int ItemGive(int aIndex, int item_num, unsigned char bFailNotSend);
  int ItemDrop(int type, int level, float dur, int x, int y, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char NOption, unsigned char SOption, unsigned long number, int aIndex, int PetLevel, int PetExp, unsigned char ItemEffectEx);
  int MonsterItemDrop(int type, int level, float dur, int x, int y, unsigned char Option1, unsigned char Option2, unsigned char Option3, unsigned char NOption, unsigned char SOption, int aIndex, unsigned long number, unsigned char ItemEffectEx);
  int MoneyItemDrop(int money, int x, int y);
  void WeatherVariationProcess();
  unsigned char GetWeather();
  void SetWeather(unsigned char a_weather, unsigned char a_variation);
  void StateSetDestroy();
  unsigned char PathFinding2(int sx, int sy, int tx, int ty, PATH_t* a);
  unsigned char PathFinding3(int sx, int sy, int tx, int ty, PATH_t* a);
  unsigned char PathFinding4(int sx, int sy, int tx, int ty, PATH_t* a);
  void SetStandAttr(int x, int y);
  void ClearStandAttr(int x, int y);
  int GetStandAttr(int x, int y);
  unsigned char GetAttr(int x, int y);
  void init();
  void free();
  MapClass(void);
  void NewConst();

  // virtual functions ------------------------------
  virtual /*<vtableoff 0x0>*/ ~MapClass(void);
};
// <size 0x51068>

int MapNumberCheck(int map);

extern MapClass MapC[MAX_MAPS];
extern char MapAttrName[MAX_MAPS][15];

#endif