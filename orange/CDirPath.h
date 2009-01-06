/*
	Copyright 2008-2009 Ambient.5

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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