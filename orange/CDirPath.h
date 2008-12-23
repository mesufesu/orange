#ifndef _CDIRPATH_H_
#define _CDIRPATH_H_

class CDirPath
{
public:
  CDirPath();
  void SetFirstPath(char* dir_path);
  char* GetNewPath(char* npath);

  virtual /*<vtableoff 0x0>*/ ~CDirPath();
private:
	/*<thisrel this+0x4>*/ /*|0x104|*/ char m_path[260];
	/*<thisrel this+0x108>*/ /*|0x104|*/ char m_newpath[260];
};

extern CDirPath gDirPath;

#endif