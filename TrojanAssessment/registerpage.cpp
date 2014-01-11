#include "registerpage.h"

RegisterPage::RegisterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_regDetailTab = new RegDetailsTab;
	m_regMonitorTab = new RegMonitorTab;
	m_regSettingTab = new RegSettingsTab;

	addTab(m_regDetailTab, QStringLiteral("Register Details"));
	addTab(m_regMonitorTab, QStringLiteral("Register Monitor"));
	addTab(m_regSettingTab, QStringLiteral("Settings"));
}

RegisterPage::~RegisterPage()
{
	if (m_regDetailTab) { delete m_regDetailTab; m_regDetailTab = NULL; }
	if (m_regMonitorTab) { delete m_regMonitorTab; m_regMonitorTab = NULL; }
	if (m_regSettingTab) { delete m_regSettingTab; m_regSettingTab = NULL; }
}

void RegisterPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_regDetailTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_regMonitorTab);
	}
	else
	{
		setCurrentWidget(m_regDetailTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
RegDetailsTab::RegDetailsTab(QWidget *parent)
	: QWidget(parent)
{

}

RegDetailsTab::~RegDetailsTab()
{

}


//////////////////////////////////////////////////////////////////////////
//
RegSettingsTab::RegSettingsTab(QWidget *parent)
	: QWidget(parent)
{

}

RegSettingsTab::~RegSettingsTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
RegMonitorTab::RegMonitorTab(QWidget *parent)
	: QWidget(parent)
{

}

RegMonitorTab::~RegMonitorTab()
{

}