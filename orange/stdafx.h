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

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <math.h>
#include <assert.h>
#include "mt19937.h"
#include "log.h"
#include "config.h"
#include "utils.h"

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned __int64 uint64;

typedef signed int int32;
typedef signed short int16;
typedef signed char int8;
typedef signed __int64 int64;

#define SECOND 1000
#define MINUTE 60 * SECOND

// TODO: reference additional headers your program requires here
