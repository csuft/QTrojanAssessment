#include "memorypage.h"

MemoryPage::MemoryPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_sysUsage = new SysUsageTab(this);
	m_memMonitor = new MemMonitorTab(this);
	m_memProtect = new MemProtectionTab(this);

	addTab(m_sysUsage, QStringLiteral("System"));      
	addTab(m_memMonitor, QStringLiteral("General"));   // dynamic charts
	addTab(m_memProtect, QStringLiteral("Protection Policy"));
}

void MemoryPage::onChangeTab(int index)
{
	if (index == 1)   // show the system memory usage tab
	{
		setCurrentWidget(m_sysUsage);
	}
	else if (index == 2) // show the memory monitoring tab
	{
		setCurrentWidget(m_memMonitor);
	}
	else    // show the memory protection tab
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
MemProtectionTab::MemProtectionTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{

}

MemProtectionTab::~MemProtectionTab()
{

}