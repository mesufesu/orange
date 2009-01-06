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

#ifndef _CATTACKEVENT_H_
#define _CATTACKEVENT_H_

class CAttackEvent
{
public:
  /*<thisrel this+0x4>*/ /*|0x1|*/ unsigned char EventState;
  /*<thisrel this+0x8>*/ /*|0x4|*/ unsigned long EventStartTime;
  /*<thisrel this+0xc>*/ /*|0x1|*/ unsigned char m_MapNumber;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int m_BossMap55;
  /*<thisrel this+0x14>*/ /*|0x4|*/ int m_BossMapX55;
  /*<thisrel this+0x18>*/ /*|0x4|*/ int m_BossMapY55;
  /*<thisrel this+0x1c>*/ /*|0x4|*/ int m_BossMap53;
  /*<thisrel this+0x20>*/ /*|0x4|*/ int m_BossMapX53;
  /*<thisrel this+0x24>*/ /*|0x4|*/ int m_BossMapY53;
  /*<thisrel this+0x28>*/ /*|0x4|*/ bool m_bManualStart;

  void Active();
  void Run();
  void End();
  void Start();
  void Init();
  CAttackEvent();
  void SetManualStart(/*<regrel ebp+0x8>*/ /*|0x4|*/ bool bMenualStart);
  void Start_Manual();
  void End_Manual();

  virtual /*<vtableoff 0x0>*/ ~CAttackEvent();
};
// <size 0x2c>

extern CAttackEvent * pAttackEvent;

#endif