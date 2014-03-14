#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <conio.h>

#pragma comment(lib,"Psapi.lib")

class DynamicMemory
{
public:
	explicit DynamicMemory(void);
	~DynamicMemory(void);



private:
	DynamicMemory& operator=(const DynamicMemory& obj);
	DynamicMemory(const DynamicMemory& obj);

private:

};

