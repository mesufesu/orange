#ifndef ZZZPATH_H__
#define ZZZPATH_H__

struct PATH_t
{
  /*<thisrel this+0x0>*/ /*|0x4|*/ int PathNum;
  /*<thisrel this+0x4>*/ /*|0x3c|*/ int PathX[15];
  /*<thisrel this+0x40>*/ /*|0x3c|*/ int PathY[15];
  /*<thisrel this+0x7c>*/ /*|0x4|*/ int CurrentPath;
};
// <size 0x80>

class PATH
{
public:
  /*<thisrel this+0x0>*/ /*|0x4|*/ int Width;
  /*<thisrel this+0x4>*/ /*|0x4|*/ int Height;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int NumPath;
  /*<thisrel this+0xc>*/ /*|0x1f4|*/ unsigned char PathX[500];
  /*<thisrel this+0x200>*/ /*|0x1f4|*/ unsigned char PathY[500];
  /*<thisrel this+0x3f4>*/ /*|0x40|*/ int Dir[16];
  /*<thisrel this+0x434>*/ /*|0x4|*/ int LastDir;
  /*<thisrel this+0x438>*/ /*|0x4|*/ int NumFails;
  /*<thisrel this+0x43c>*/ /*|0x4|*/ unsigned char* Map;
  /*<thisrel this+0x440>*/ /*|0x4|*/ unsigned char* HitMap;
  /*<thisrel this+0x444>*/ /*|0x4|*/ int stx;
  /*<thisrel this+0x448>*/ /*|0x4|*/ int sty;
  /*<thisrel this+0x44c>*/ /*|0x4|*/ int edx;
  /*<thisrel this+0x450>*/ /*|0x4|*/ int edy;

  int GetDist(int x1, int y1, int x2, int y2);
  int VerifyThatOnPath(int x, int y);
  int CanWeMoveForward(int x, int y);
  int CanWeMoveForward2(int x, int y);
  int CanWeMoveForward3(int x, int y);
  int IsThisSpotOK(int x, int y);
  int FindNextDir(int sx, int sy, int dx, int dy, int dirstart, unsigned char First, unsigned char ErrorCheck);
  int FindNextDir2(int sx, int sy, int dx, int dy, int dirstart, unsigned char First, unsigned char ErrorCheck);
  int FindNextDir3(int sx, int sy, int dx, int dy, int dirstart, unsigned char First, unsigned char ErrorCheck);
  PATH();
  ~PATH();
  unsigned char FindPath(int startx, int starty, int endx, int endy, unsigned char ErrorCheck);
  unsigned char FindPath2(int startx, int starty, int endx, int endy, unsigned char ErrorCheck);
  unsigned char FindPath3(int startx, int starty, int endx, int endy, unsigned char ErrorCheck);
  void SetMapDimensions(int w, int h, unsigned char* map);
  int GetPath();
  unsigned char* GetPathX();
  unsigned char* GetPathY();
};
// <size 0x454>

#endif