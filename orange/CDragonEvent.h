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

#ifndef _CDRAGONEVENT_H_
#define _CDRAGONEVENT_H_

class CDragonEvent
{
public:
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char EventState;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long EventStartTime;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char m_MapNumber;
  /*<thisrel this+0x10>*/ /*|0x4|*/ bool m_bManualStart;

  CDragonEvent();
  unsigned char GetState();
  unsigned char GetMapNumber();
  void Init();
  void Start();
  void End();
  void Run();
  void DragonActive();
  void SetManualStart(bool bManualStart);
  void Start_Manual();
  void End_Manual();

  virtual /*<vtableoff 0x0>*/ ~CDragonEvent();
};
// <size 0x14>

extern CDragonEvent * pDragonEvent;

#endif