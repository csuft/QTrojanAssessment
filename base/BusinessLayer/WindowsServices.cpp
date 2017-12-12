#include "WindowsServices.h"


WindowsServices::WindowsServices(void)
{
	getServiceItems();
}

void WindowsServices::getServiceItems()
{
	SC_HANDLE hHandle = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (NULL == hHandle) {
		return ;
	}
	ENUM_SERVICE_STATUS service;
	ServiceItem item;
	DWORD dwBytesNeeded = 0;
	DWORD dwServicesReturned = 0;
	DWORD dwResumedHandle = 0;
	DWORD dwServiceType = SERVICE_WIN32 | SERVICE_DRIVER;
	// Query services
	BOOL retVal = EnumServicesStatus(hHandle, dwServiceType, SERVICE_STATE_ALL, 
		&service, sizeof(ENUM_SERVICE_STATUS), &dwBytesNeeded, &dwServicesReturned, &dwResumedHandle);
	if (!retVal) {
		// Need big buffer
		if (ERROR_MORE_DATA == GetLastError()) {
			// Set the buffer
			DWORD dwBytes = sizeof(ENUM_SERVICE_STATUS) + dwBytesNeeded;
			ENUM_SERVICE_STATUS* pServices = new ENUM_SERVICE_STATUS [dwBytes];
			// Now query again for services
			EnumServicesStatus(hHandle, SERVICE_WIN32 | SERVICE_DRIVER, SERVICE_STATE_ALL, 
				pServices, dwBytes, &dwBytesNeeded, &dwServicesReturned, &dwResumedHandle);
			// now traverse each service to get information
			for (unsigned iIndex = 0; iIndex < dwServicesReturned; iIndex++) {
				item.display_name = (pServices + iIndex)->lpDisplayName;
				item.service_name = (pServices + iIndex)->lpServiceName ; 
				switch ((pServices + iIndex)->ServiceStatus.dwServiceType)
				{
				case 0x00000001:
					item.service_type = TEXT("KERNEL_DRIVER");
					break;
				case 0x00000002:
					item.service_type = TEXT("FILE_SYSTEM_DRIVER");
					break;
				case 0x00000010:
					item.service_type = TEXT("WIN32_OWN_PROCESS");
					break;
				case 0x00000020:
					item.service_type = TEXT("WIN32_SHARE_PROCESS");
					break;
				default:
					item.service_type = TEXT("UNKNOWN");
					break;
				}

				switch ((pServices + iIndex)->ServiceStatus.dwCurrentState)
				{
				case 0x00000001:
					item.service_status = TEXT("STOPPED");
					break;
				case 0x00000003:
					item.service_status = TEXT("STOP_PENDING");
					break;
				case 0x00000002:
					item.service_status = TEXT("START_PENDING");
					break;
				case 0x00000004:
					item.service_status = TEXT("RUNNING");
					break;
				case 0x00000007:
					item.service_status = TEXT("PAUSED");
					break;
				case 0x00000006:
					item.service_status = TEXT("PAUSE_PENDING");
					break;
				case 0x00000005:
					item.service_status = TEXT("CONTINUE_PENDING");
					break;
				default:
					item.service_status = TEXT("UNKNOWN");
				}
				m_serviceContainer.push_back(item);
			}
			delete [] pServices;
			pServices = NULL;
		}

	}
	CloseServiceHandle(hHandle);
}