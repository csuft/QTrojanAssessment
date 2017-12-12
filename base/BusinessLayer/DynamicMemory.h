#ifndef __DYNAMICMEMORY_H__
#define __DYNAMICMEMORY_H__ 

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <vector>
#include <string>

#pragma comment(lib,"Psapi.lib")
using namespace std;

typedef struct ProcessMemory {
	DWORD pid;
	wstring pname;
	DWORD PageFaultCount;
	DWORD PeakWorkingSetSize;
	DWORD WorkingSetSize;
	DWORD QuotaPeakPagedPoolUsage;
	DWORD QuotaPagedPoolUsage;
	DWORD QuotaPeakNonPagedPoolUsage;
	DWORD QuotaNonPagedPoolUsage;
	DWORD PagefileUsage;
	DWORD PeakPagefileUsage;
}ProcessMemory;

typedef struct MemoryProperty{
	DWORD pid;
	DWORD AllocationBase;
	DWORD State;
	DWORD AllocationProtect;
	DWORD BaseAddress;
	DWORD RegionSize;
	DWORD Type;
	DWORD Protect;
}MemoryProperty;

class DynamicMemory
{
public:
	explicit DynamicMemory(void);
	~DynamicMemory(void);

	const vector<ProcessMemory>& getProcessMemory() { return m_procsmem; }
private:
	DynamicMemory& operator=(const DynamicMemory& obj);
	DynamicMemory(const DynamicMemory& obj);

	void _getProcessMemory();
private:
	vector<ProcessMemory> m_procsmem;
};

class MemoryProps
{
public:
	explicit MemoryProps(void);
	~MemoryProps();

	const vector<MemoryProperty>& getMemoryState() { return m_procpros; }
private:
	MemoryProps& operator=(const MemoryProps& obj);
	MemoryProps(const MemoryProps& obj);
	void _getMemoryState();
private:
	vector<MemoryProperty> m_procpros;
};

#endif