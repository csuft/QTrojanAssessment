#include "memorypage.h"

MemoryPage::MemoryPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_appUsage = new AppUsageTab;
	m_sysUsage = new SysUsageTab;
	m_memMonitor = new MemMonitorTab;
	m_memProtect = new MemProtectionTab;

	addTab(m_appUsage, QStringLiteral("Application"));
	addTab(m_sysUsage, QStringLiteral("System"));
	addTab(m_memMonitor, QStringLiteral("General"));
	addTab(m_memProtect, QStringLiteral("Protection Policy"));
}

MemoryPage::~MemoryPage()
{
	if (m_appUsage) { delete m_appUsage; m_appUsage = NULL; }
	if (m_sysUsage) { delete m_sysUsage; m_sysUsage = NULL; } 
	if (m_memMonitor) { delete m_memMonitor; m_memMonitor = NULL;}
	if (m_memProtect) { delete m_memProtect; m_memProtect = NULL;}
}

void MemoryPage::onChangeTab(int index)
{
	if (index == 1)  // show the app memory usage tab
	{
		setCurrentWidget(m_appUsage);
	}
	else if (index == 2)  // show the system memory usage tab
	{
		setCurrentWidget(m_sysUsage);
	}
	else if (index == 3)  // show the memory monitoring tab
	{
		setCurrentWidget(m_memMonitor);
	}
	else  // show the memory protection tab
	{
		setCurrentWidget(m_memProtect);
	}
}

//////////////////////////////////////////////////////////////////////////
// Implementation of system memory usage class .
SysUsageTab::SysUsageTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{

}

SysUsageTab::~SysUsageTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
MemMonitorTab::MemMonitorTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{

}

MemMonitorTab::~MemMonitorTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
AppUsageTab::AppUsageTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{

}

AppUsageTab::~AppUsageTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
MemProtectionTab::MemProtectionTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{

}

MemProtectionTab::~MemProtectionTab()
{

}