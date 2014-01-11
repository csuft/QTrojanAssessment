#include "BasicInformation.h"


BasicInformation::BasicInformation(void)
{
	m_unknownResult = "Unknown";
	m_unknownVector.push_back(m_unknownResult);
	// Retrive all information about network card.
	_getNetworkInfo();
}


BasicInformation::~BasicInformation(void)
{

}

string& BasicInformation::getSystemBootTime()
{
	if (_getSystemBootTime())
	{
		return m_boottime;
	}
	return m_unknownResult;
}

string& BasicInformation::getCPUInfos()
{
	if (_getCPUInfos())
	{
		return m_cpuinfo;
	}
	return m_unknownResult;
}

string& BasicInformation::getHostName()
{
	if (_getHostName())
	{
		return m_hostname;
	}
	return m_unknownResult;
}
vector<string> BasicInformation::getIPAddress()
{
	return m_ipaddr.empty()?m_unknownVector:m_ipaddr;
}

vector<string> BasicInformation::getMACAddress()
{
	return m_macaddr.empty()?m_unknownVector:m_macaddr;
}

string& BasicInformation::getMemAvailTotal()
{
	if (_getMemAvailTotal())
	{
		return m_memAvailTotal;
	}
	return m_unknownResult;
}

vector<string> BasicInformation::getNetworkCard()
{
	return m_ncard.empty()?m_unknownVector:m_ncard;
}

string& BasicInformation::getOSInformation()
{
	if (_getOSInformation())
	{
		return m_osinfo;
	}
	return m_unknownResult;
}

vector<string> BasicInformation::getVolumeInformation()
{
	if (_getVolumeInformation())
	{
		return m_volinfo;
	}
	return m_unknownVector;
}
/*
 * 获取系统开机时间
 */
bool BasicInformation::_getSystemBootTime()
{
	SYSTEM_TIME_INFORMATION Sti;   
	LONG                    status;   
	FILETIME                ftSystemBoot;   
	SYSTEMTIME              stSystemBoot;  
	char                    datetime[48];

	PROCNTQSI NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(GetModuleHandle(TEXT("ntdll")), "NtQuerySystemInformation");   
	if (!NtQuerySystemInformation) 
	{
		return false;   
	}
	status = NtQuerySystemInformation(SystemTimeInformation,&Sti,sizeof(Sti),0);   
	if (status!=NO_ERROR)   
	{
		return false;   
	}
	ftSystemBoot = *(FILETIME *)&(Sti.liKeBootTime);   
	FileTimeToLocalFileTime(&ftSystemBoot,&ftSystemBoot);   
	FileTimeToSystemTime(&ftSystemBoot,&stSystemBoot);   
	sprintf(datetime, "%04d-%02d-%02d %02d:%02d:%02d",   
			 stSystemBoot.wYear, stSystemBoot.wMonth, stSystemBoot.wDay,   
			 stSystemBoot.wHour, stSystemBoot.wMinute, stSystemBoot.wSecond);
	m_boottime = datetime;

	return true;
}
/*
 * 获取CPU信息
 */
bool BasicInformation::_getCPUInfos()
{
	HKEY hkey;
	LPCWSTR StrKey = TEXT("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, StrKey, NULL, KEY_ALL_ACCESS, &hkey))
	{
		DWORD dwSize = 256;
		DWORD dwType = REG_SZ;   
		char str[256] = {'\0'};      
		if (ERROR_SUCCESS == RegQueryValueExA(hkey, "ProcessorNameString", 0, &dwType, (LPBYTE)str, &dwSize))   
		{   
			m_cpuinfo = str;
			RegCloseKey(hkey);
		}   
		else
		{
			RegCloseKey(hkey);
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}
/*
 * 获取系统主机名
 */
bool BasicInformation::_getHostName()
{
	CHAR  infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;

	if( !GetComputerNameA( infoBuf, &bufCharCount ))
	{
		return false;
	}
	m_hostname = infoBuf;

	return true;
}

/*
 * 获取系统可用内存及总内存
 */
bool BasicInformation::_getMemAvailTotal()
{
	MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(mem_info);
	if (!GlobalMemoryStatusEx(&mem_info)) {
		return false;
	}

	string tmp;
	CHAR total[16] = {'\0'};   
	CHAR avail[16] = {'\0'};
	CHAR allinfo[32] = {'\0'};
	sprintf(total, "%.2f(GB)", ((mem_info.ullTotalPhys/DIV)/DIV)/DIV);    // to avoid the overflow of multiplication 
	sprintf(avail, "%.2f(GB)", ((mem_info.ullAvailPhys/DIV)/DIV)/DIV);   
	strncat(allinfo, avail, strlen(avail));
	strncat(allinfo, "/", strlen("/"));
	strncat(allinfo, total, strlen(total));

	m_memAvailTotal = allinfo;

	return true;
}
/*
 * 获取系统网络接口卡信息
 */
bool BasicInformation::_getNetworkInfo()
{
	char macaddr[24] = {'\0'};
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	}
	if (ERROR_SUCCESS == nRel)
	{
		//输出网卡信息
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{
			string singleItem = pIpAdapterInfo->Description;
			m_ncard.push_back(singleItem);
			sprintf(macaddr, "%02X-%02X-%02X-%02X-%02X-%02X", pIpAdapterInfo->Address[0],
													pIpAdapterInfo->Address[1],
													pIpAdapterInfo->Address[2],
													pIpAdapterInfo->Address[3],
													pIpAdapterInfo->Address[4],
													pIpAdapterInfo->Address[5]);
			singleItem = macaddr;
			m_macaddr.push_back(singleItem);
			//可能网卡有多IP,因此通过循环去判断
			IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
			do 
			{
				singleItem = pIpAddrString->IpAddress.String;
				m_ipaddr.push_back(singleItem);
				pIpAddrString=pIpAddrString->Next;
			} while (pIpAddrString);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}

	return true;
}
/*
 * 获取操作系统基本信息
 */
bool BasicInformation::_getOSInformation()
{
	HKEY  hKey;   
	UCHAR name[32]={'\0'};   
	UCHAR version[32]={'\0'}; 
	CHAR allinfo[64] = {'\0'};
	DWORD len = 32;    
	DWORD dwDataType = 0;       
	OSVERSIONINFO OsInfo;   
	string singleItem;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);   
	if (GetVersionEx(&OsInfo))
	{    
		switch (OsInfo.dwPlatformId)   
		{   
		case VER_PLATFORM_WIN32_WINDOWS:   
			if(OsInfo.dwMajorVersion == 3)   
			{   
				m_osinfo = "Windows 95";   
			}   
			else if(OsInfo.dwMajorVersion == 4)   
			{   
				if (OsInfo.dwMinorVersion==0x5a)   
				{   
					m_osinfo = "Windows ME";   
				}   
				else   
					m_osinfo = "Windows 98";   
			}   
			break;   
		case VER_PLATFORM_WIN32_NT:   
			if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion"), 0, KEY_READ,   &hKey) == ERROR_SUCCESS)   
			{   
				RegQueryValueExA(hKey, "ProductName", NULL, &dwDataType, name, &len);   
				RegQueryValueExA(hKey, "CSDVersion", NULL, &dwDataType, version, &len);    
				RegCloseKey(hKey);    
				strncat(allinfo, (char*)name, strlen((char*)name));
				strncat(allinfo, "  ", strlen("  "));
				strncat(allinfo, (char*)version, strlen((char*)version));
				m_osinfo = allinfo;
			}
			else
			{
				m_osinfo = m_unknownResult;
			}
			break;   
		default:   
			m_osinfo = m_unknownResult;
			break;   
		}  
	}
	// this function would never fail.
	return true;
}

/*
 * 获取系统磁盘基本信息
 */
bool BasicInformation::_getVolumeInformation()
{
	string singleItem;

	const char* UNKNOWNTYPE = " UNKNOWN";
	const char* SOFTDISK = " SOFTDISK";
	const char* REMOVABLEDISK = " REMOVABLE";
	const char* LOCALDISK = " LOCAL";
	const char* NETDISK = " REMOTE";
	const char* CDROM = " CDROM";
	const char* RAMDISK = " RAMDISK";
	const int DISKINFO_LEN = 64;
	const int LABELITEM_LEN = 4;   //每个盘符占4个字符
	const int FILESYSTEM_LEN = 10;

	char diskInfo[DISKINFO_LEN] = {'\0'};
	char cItem[DISKINFO_LEN] = {'\0'};
	char fmt[DISKINFO_LEN] = {'\0'};
	char FileSystemNameBuffer[FILESYSTEM_LEN] = {'\0'};
	char VolumeNameBuffer[DISKINFO_LEN] = {'\0'};
	GetLogicalDriveStringsA(DISKINFO_LEN, diskInfo);
	char* index = diskInfo;
	unsigned int ret;

	while (*index)
	{
		memset(cItem, 0, strlen(cItem));
		memset(fmt, 0, strlen(fmt));
		memset(FileSystemNameBuffer, 0, strlen(FileSystemNameBuffer));
		memset(VolumeNameBuffer, 0, strlen(VolumeNameBuffer));
		strncat(cItem, index, strlen(index));
		ret = GetDriveTypeA(index);
		switch(ret)
		{
		case DRIVE_UNKNOWN:
			strncat(cItem, UNKNOWNTYPE, strlen(UNKNOWNTYPE));
			break;
		case DRIVE_NO_ROOT_DIR:
			strncat(cItem, SOFTDISK, strlen(SOFTDISK));
			break;
		case DRIVE_REMOVABLE:
			strncat(cItem, REMOVABLEDISK, strlen(REMOVABLEDISK));
			break;
		case DRIVE_FIXED:
			strncat(cItem, LOCALDISK, strlen(LOCALDISK));
			break;
		case DRIVE_REMOTE:
			strncat(cItem, NETDISK, strlen(NETDISK));
			break;
		case DRIVE_CDROM:
			strncat(cItem, CDROM, strlen(CDROM));
			break;
		case DRIVE_RAMDISK:
			strncat(cItem, RAMDISK, strlen(RAMDISK));
			break;
		}
		if (ret != DRIVE_CDROM)  // retrive ultra information if other than CDROM
		{
			 DWORD SectorsPerCluster, BytesPerSector, NumberOfFreeClusters, TotalNumberOfClusters;
			 if (!GetDiskFreeSpaceA(index, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters))
			 {
				 return false;
			 }
			 sprintf(fmt, " %5.2f(GB)/%5.2f(GB)", ((NumberOfFreeClusters/DIV)*SectorsPerCluster*(BytesPerSector/DIV))/DIV, ((TotalNumberOfClusters/DIV)*SectorsPerCluster*(BytesPerSector/DIV))/DIV);
			 strncat(cItem, fmt, strlen(fmt));
			 
			 DWORD VolumeSerialNumber;
			 DWORD MaximumComponentLength;
			 DWORD FileSystemFlags;
			 if (!GetVolumeInformationA(index, VolumeNameBuffer, DISKINFO_LEN, &VolumeSerialNumber, &MaximumComponentLength, &FileSystemFlags, FileSystemNameBuffer, FILESYSTEM_LEN))
			 {
				 return false;
			 }
			 memset(fmt, 0, strlen(fmt));
			 sprintf(fmt, " %s %s", VolumeNameBuffer, FileSystemNameBuffer);
			 strncat(cItem, fmt, strlen(fmt));
			 
		}
		m_volinfo.push_back(string(cItem));
		index += 4;  // skip to the next record.
	}

	return true;
}