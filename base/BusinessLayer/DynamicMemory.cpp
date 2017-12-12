#include "DynamicMemory.h"
#include <assert.h>

DynamicMemory::DynamicMemory(void)
{
	_getProcessMemory();
}


DynamicMemory::~DynamicMemory(void)
{

}

void DynamicMemory::_getProcessMemory()
{
	HANDLE proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (proc == INVALID_HANDLE_VALUE)
	{
		assert(proc != INVALID_HANDLE_VALUE);
		return ;
	}
	ProcessMemory item;
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;
	PROCESSENTRY32 procEntry = { 0 };
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(proc,&procEntry);
	while (bRet)
	{
		hProcess = OpenProcess( PROCESS_QUERY_INFORMATION| PROCESS_VM_READ, FALSE, procEntry.th32ProcessID );
		if (NULL == hProcess) 
		{
			int ret = GetLastError();
			// skip the system process and Idle process or one of CSRSS process
			if (ret != ERROR_INVALID_PARAMETER && ret != ERROR_ACCESS_DENIED)  
				return;
		}
		else 
		{
			if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
			{
				item.pname = procEntry.szExeFile;
				item.pid = procEntry.th32ProcessID;
				item.PageFaultCount = pmc.PageFaultCount;
				item.PagefileUsage = pmc.PagefileUsage;
				item.PeakPagefileUsage = pmc.PeakPagefileUsage;
				item.PeakWorkingSetSize = pmc.PeakWorkingSetSize;
				item.QuotaNonPagedPoolUsage = pmc.QuotaNonPagedPoolUsage;
				item.QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
				item.QuotaPeakNonPagedPoolUsage = pmc.QuotaPeakNonPagedPoolUsage;
				item.QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;

				m_procsmem.push_back(item);
			}
		}

		bRet = Process32Next(proc, &procEntry);
	}
	CloseHandle(hProcess);
	CloseHandle(proc);
}

MemoryProps::MemoryProps(void)
{
	_getMemoryState();
}

void MemoryProps::_getMemoryState()
{
	HANDLE proc = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (proc == INVALID_HANDLE_VALUE)
	{
		assert(proc != INVALID_HANDLE_VALUE);
		return ;
	}

	MEMORY_BASIC_INFORMATION mbi;
	MemoryProperty item;
	DWORD ptr = NULL;
	HANDLE hProcess;
	PROCESSENTRY32 procEntry = { 0 };
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(proc,&procEntry);
	while (bRet)
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, procEntry.th32ProcessID);
		if(hProcess == NULL) 
		{
			int ret = GetLastError();
			if (ret != ERROR_INVALID_PARAMETER && ret != ERROR_ACCESS_DENIED)
				return;
		}
		else 
		{
			while(1)
			{
				if(VirtualQueryEx(hProcess, (void*)ptr, &mbi, sizeof(mbi)) == sizeof(MEMORY_BASIC_INFORMATION))
				{
					item.pid = procEntry.th32ProcessID;
					item.AllocationBase = (DWORD)mbi.AllocationBase;
					item.AllocationProtect = mbi.AllocationProtect;
					item.BaseAddress = (DWORD)mbi.BaseAddress;
					item.Protect = mbi.Protect;
					item.RegionSize = mbi.RegionSize;
					item.State = mbi.State;
					item.Type = mbi.Type;

					m_procpros.push_back(item);
				}
				else break;
				int oldptr = ptr;
				ptr = (DWORD)mbi.BaseAddress + mbi.RegionSize;
				if(ptr <= oldptr) break;
			}
		}


		bRet = Process32Next(proc,&procEntry);
	}

	CloseHandle(hProcess);
	CloseHandle(proc);
}

MemoryProps::~MemoryProps()
{

}