#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <string>
#include <vector>

using std::vector;
using std::wstring;

typedef struct _ServiceItem
{
	wstring service_name;
	wstring display_name;
	wstring service_type;
	wstring service_status;
}ServiceItem, *pServiceItem;


class WindowsServices
{
public:
	explicit WindowsServices(void);
	~WindowsServices(void){}
	const vector<ServiceItem>& getServiceList() const { return m_serviceContainer; }
private:
	void getServiceItems();

private:
	vector<ServiceItem> m_serviceContainer;
};

