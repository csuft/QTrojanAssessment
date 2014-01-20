#ifndef _BASICINFORMATION_H_
#define _BASICINFORMATION_H_

#define WIN32_LEAN_AND_MEAN   // to solve the conflicts between Windows.h and WinSock2.h

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <cstdio>

#include <tchar.h>
#include <qt_windows.h>  // modified version of Windows.h header file. To avoid the collision of min() and max() macros.
#include <WinSock2.h>
#include <IPHlpApi.h>  // for GetAdaptersAddresses() function
#include <WinInet.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")  // for GetAdaptersAddresses() function
#pragma comment(lib, "Wininet.lib")

using std::string;
using std::wstring;
using std::vector;
using std::wofstream;

#define INFO_BUFFER_SIZE 32767
#define DIV 1024.0

#define SystemTimeInformation 3
typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG); 
typedef struct _SYSTEM_TIME_INFORMATION   
{   
	LARGE_INTEGER liKeBootTime;   
	LARGE_INTEGER liKeSystemTime;   
	LARGE_INTEGER liExpTimeZoneBias;   
	ULONG uCurrentTimeZoneId;   
	DWORD dwReserved;   
} SYSTEM_TIME_INFORMATION;

class BasicInformation
{
public:
	BasicInformation(void);
	~BasicInformation(void);

public:
	string& getSystemBootTime();
	string& getCPUInfos();
	string& getHostName();
	vector<string> getIPAddress();
	vector<string> getMACAddress();
	string& getMemAvailTotal();
	vector<string> getNetworkCard();
	string& getOSInformation();
	vector<string> getVolumeInformation();

private:
	bool _getSystemBootTime();
	bool _getCPUInfos();
	bool _getHostName();
	bool _getMemAvailTotal();
	bool _getNetworkInfo();
	bool _getOSInformation();
	bool _getVolumeInformation();

private:
	BasicInformation& operator=(const BasicInformation& obj);
	BasicInformation(const BasicInformation& obj);

private:
	string m_boottime;
	string m_cpuinfo;
	string m_hostname;
	vector<string> m_ipaddr;
	vector<string> m_macaddr;
	string m_memAvailTotal;
	vector<string>m_ncard;
	string m_osinfo;
	vector<string> m_volinfo;
	string m_unknownResult;
	vector<string> m_unknownVector;
};

class IECookieInfo
{
public:

private:

};

typedef struct _CacheEntry
{
	string m_fileName;
	string m_urlStr;
	string m_localPath;
	string m_subFolder;
	string m_headerInfo;
	long   m_entrySize;    // the size of the cache entry
	int    m_hits;
	string m_lastAccess;
	string m_lastModified;
	string m_expiration;
	string m_lastChecked;
	string m_entryType;
}CacheEntry, *pCacheEntry;

class IECacheInfo
{
public:
	IECacheInfo();
	~IECacheInfo() {}

	const vector<CacheEntry>& getCacheEntVec() const { return m_recordsVec; }

private:
	HANDLE getStartCacheEntry(LPINTERNET_CACHE_ENTRY_INFO* startEnt);
	bool getNextCacheEntry(HANDLE hDir, LPINTERNET_CACHE_ENTRY_INFO* next);
	void setAllFields(pCacheEntry entry, const LPINTERNET_CACHE_ENTRY_INFO record);
	void transformTimeFormat(pCacheEntry entry, const LPINTERNET_CACHE_ENTRY_INFO lpCacheEnt);
private:
	vector<CacheEntry> m_recordsVec;
};

#endif