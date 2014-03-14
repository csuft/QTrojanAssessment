#ifndef _BASICINFORMATION_H_
#define _BASICINFORMATION_H_

#define WIN32_LEAN_AND_MEAN   // to solve the conflicts between Windows.h and WinSock2.h

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <cstdio>

#include <QSysInfo>
#include <tchar.h>
#include <qt_windows.h>  // modified version of Windows.h header file. To avoid the collision of min() and max() macros.
#include <WinSock2.h>
#include <IPHlpApi.h>  // for GetAdaptersAddresses() function
#include <WinInet.h>
#include <Psapi.h>
#include <TlHelp32.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Iphlpapi.lib")  // for GetAdaptersAddresses() function
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Psapi.lib")

using std::string;
using std::vector;
using std::wstring;

#define INFO_BUFFER_SIZE 32767
#define TMPSIZE 1204
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
//////////////////////////////////////////////////////////////////////////
typedef struct _cookieRecord
{
	char m_key[32];
	char m_value[1024];
	char m_domain[32];
	char m_flag[8];
	char m_expiration[32];
	char m_creation[32];
	char m_creator[8];
}CookieRecord, *lpCookieRecord;

typedef struct _CookieEntry
{
	string m_website;
	string m_fileName;
	string m_user;
	string m_localPath;
	long   m_cookieSize;    // the size of the cache entry
	int    m_hits;
	string m_lastAccess;
	string m_lastModified;
	int    m_recordNum;     // the order number in the hash section.
}CookieEntry, *LPCookieEntry;

// Head structure
struct CacheDir
{
	DWORD nFileCount;
	char sDirName[8];
};

typedef struct _MEMMAP_HEADER_SMALL
{
	char    FileSignature[28];     // ”Client UrlCache MMF Ver 5.2”
	DWORD    FileSize;             // index.dat文件的大小
	DWORD    dwHashTableOffset;    // 第一个哈希表的偏移,相对于文件的开始地址
	DWORD    NumUrlInternalEntries;// 未知
	DWORD    NumUrlEntriesAlloced; // 未知
	DWORD    dwGarbage;            // 未知
	LONGLONG CacheLimit;           // 8Byte
	LONGLONG CacheSize;            // 8Byte
	LONGLONG ExemptUsage;          // 8Byte
	DWORD    nDirCount;            // 子目录个数
	CacheDir DirArray[32];         // 子目录名称
	DWORD    dwHeaderData[33];     // 未知
}MEMMAP_HEADER_SMALL, *LPMEMMAP_HEADER_SMALL;

typedef struct _MEMMAP_HEADER : _MEMMAP_HEADER_SMALL
{
	DWORD AllocationBitMap[3948];
}MEMMAP_HEADER, *LPMEMMAP_HEADER;

//////////////////////////////////////////////////////////////////////////
// Hash items
typedef struct _FILEMAP_ENTRY
{
	DWORD dwSig;      //条目标识
	DWORD nBlocks;    //条目占用多少个块（每块128字节）
}FILEMAP_ENTRY, *LPFILEMAP_ENTRY;

typedef struct _HASH_FILEMAP_ENTRY : _FILEMAP_ENTRY
{
	DWORD dwNext;     // 下一个哈希表偏移（0表示为最后一个）,偏移以index.dat文件第0字节为基地址。
	DWORD nOrder;     // 本哈希表的序列号。从0，1，2…….
}HASH_FILEMAP_ENTRY, *LPHASH_FILEMAP_ENTRY;

typedef struct _HASH_ITEM
{
	DWORD dwHash;     //哈希值，注意最后6位为0
	DWORD dwOffset;   //指向的实体中的记录部分的偏移, 偏移以index.dat文件第0字节为基地址。
}HASH_ITEM, *LPHASH_ITEM;

// LEAK is the same as URL
typedef struct _IE5_URL_FILEMAP_ENTRY : _FILEMAP_ENTRY
{
	LONGLONG LastModifiedTime;         // 最后修改时间
	LONGLONG LastAccessedTime;         // 最后访问时间
	DWORD    dostExpireTime;           // 到期时间
	DWORD    dostPostCheckTime;

	DWORD    dwFileSize;               // 硬盘缓存中的文件的大小
	DWORD    dwRedirHashItemOffset;    // ask DanpoZ
	DWORD    dwGroupOffset;
	union
	{
		DWORD  dwExemptDelta;          // for SIG_URL
		DWORD  dwNextLeak;             // for SIG_LEAK
	};

	DWORD    CopySize;                 // 好像总是0x60
	DWORD    UrlNameOffset;            // URL名称偏移。基地址是本URL条目的开始地址
	BYTE     DirIndex;                 // 属于的子文件夹索引
	BYTE     bSyncState;               // automatic sync mode state
	BYTE     bVerCreate;               // 建立本ENTRY的CACHE的版本
	BYTE     bVerUpdate;               // 升级本ENTRY的CACHE的版本

	DWORD    InternalFileNameOffset;   // 硬盘上文件名（不包括目录）字符串的偏移，基地址是本URL条目的开始地址。
	DWORD    CacheEntryType;           // 缓存类型
	DWORD    HeaderInfoOffset;         // 从WEB服务器中取本文件时的返回的HTTP头部信息
	DWORD    HeaderInfoSize;           // HTTP头部大小（注意包括最后的回车换行的）
	DWORD    FileExtensionOffset;      // should be WORD
	DWORD    dostLastSyncTime;      
	DWORD    NumAccessed;              // 存取次数（点击率）
	DWORD    NumReferences;            // 引用次数
	DWORD    dostFileCreationTime;   
}IE5_URL_FILEMAP_ENTRY, *LPIE5_URL_FILEMAP_ENTRY;

class IECookieInfo
{
public:
	explicit IECookieInfo(void);
	~IECookieInfo(void);

	const vector<CookieEntry>& getCacheEntVec() const { return m_recordsVec;}
	static const string getCookiePath(const char* name);
private:
	IECookieInfo& operator=(const IECookieInfo& obj);
	IECookieInfo(const IECookieInfo& obj);
	void initializeEntriesVec();
	const string transformTimeFormat(LONGLONG dtime);
	void splitCookieURL(char* url, CookieEntry& obj);

private:
	vector<CookieEntry>	m_recordsVec;
	HANDLE				m_hFile;
	HANDLE				m_hMapping;
	LPSTR				m_startAddr;
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
//////////////////////////////////////////////////////////////////////////
// processes and software installed.
typedef struct _procEntry
{
	wstring procName;
	unsigned int procId;    // process id
	unsigned int procPid;   // parent process id
	unsigned short ctThread; // thread count
	unsigned int priorBase;
	unsigned int priorClass;
	wstring exePath;
}ProcEntry, *pProcEntry;

typedef struct _appEntry
{
	wstring appName;
	wstring appVer;
	wstring installDate;
	wstring location;
	wstring publisher;
}AppEntry, *pAppEntry;

typedef struct _moduleEntry
{
	DWORD glblcntUsage;
	DWORD proccntUsage;
	DWORD modBaseSize;
	DWORD modPid;
	wstring modName;
	wstring exePath;
}ModuleEntry, *pModuleEntry;

class RetrieveHelper
{
public:
	RetrieveHelper(void);
	~RetrieveHelper(void);

	const vector<AppEntry>& getApplist() const { return m_appList; }
	const vector<ProcEntry>& getProclist() const { return m_procList; }
private:
	RetrieveHelper& operator=(const RetrieveHelper& obj);
	RetrieveHelper(const RetrieveHelper& obj);

	void setApplist();
	void setProclist();
	bool RetrieveHelper::NormalizeNTPath(wchar_t* pszPath, size_t nMax);
	void retrieveAppkey(HKEY hKey, LPCTSTR szDesKeyItem, LONG flag);
	BOOL determineOSBit();
private:
	vector<AppEntry> m_appList;
	vector<ProcEntry> m_procList;
};

#endif