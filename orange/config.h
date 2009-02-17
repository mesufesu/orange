#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned __int64 uint64;

typedef signed int int32;
typedef signed short int16;
typedef signed char int8;
typedef signed __int64 int64;

class CConfigStorage
{
public:
	uint32 world_tick_rate;
	std::string log_file_name;
	CConfigStorage();
	bool Read();
};

extern CConfigStorage config;

#endif