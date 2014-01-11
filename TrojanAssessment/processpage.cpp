#include "processpage.h"

ProcessPage::ProcessPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_processTab = new ProcessListTab;
	m_runtimeTab = new RuntimeMonitorTab;
	m_softTab = new SoftwareInstalledTab;
	m_serviceTab = new WinServicesTab;

	addTab(m_runtimeTab, QStringLiteral("Runtime Monitoring"));
	addTab(m_serviceTab, QStringLiteral("Windows Services"));
	addTab(m_processTab, QStringLiteral("Process Snapshot"));
	addTab(m_softTab, QStringLiteral("Software Installed"));
}

ProcessPage::~ProcessPage()
{
	if (m_processTab) { delete m_processTab; m_processTab = NULL; }
	if (m_runtimeTab) { delete m_runtimeTab; m_runtimeTab = NULL; }
	if (m_softTab) { delete m_softTab; m_softTab = NULL; }
	if (m_serviceTab) { delete m_serviceTab; m_serviceTab = NULL; }
}

void ProcessPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_runtimeTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_serviceTab);
	}
	else if (index == 3)
	{
		setCurrentWidget(m_processTab);
	}
	else
	{
		setCurrentWidget(m_softTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
RuntimeMonitorTab::RuntimeMonitorTab(QWidget *parent)
	: QWidget(parent)
{

}

RuntimeMonitorTab::~RuntimeMonitorTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
WinServicesTab::WinServicesTab(QWidget *parent)
	: QWidget(parent)
{

}

WinServicesTab::~WinServicesTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
ProcessListTab::ProcessListTab(QWidget *parent)
	: QWidget(parent)
{

}

ProcessListTab::~ProcessListTab()
{

}


//////////////////////////////////////////////////////////////////////////
//
SoftwareInstalledTab::SoftwareInstalledTab(QWidget *parent)
	: QWidget(parent)
{

}

SoftwareInstalledTab::~SoftwareInstalledTab()
{

}
