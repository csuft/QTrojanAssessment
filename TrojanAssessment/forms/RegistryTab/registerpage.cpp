#include "registerpage.h"

RegisterPage::RegisterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_regDetailTab = new RegDetailsTab(this);
	m_regMonitorTab = new RegMonitorTab(this);
	m_regSettingTab = new RegSettingsTab(this);

	addTab(m_regDetailTab, QStringLiteral("Register Details"));
	addTab(m_regMonitorTab, QStringLiteral("Register Monitor"));
	addTab(m_regSettingTab, QStringLiteral("Settings"));
}

RegisterPage::~RegisterPage()
{

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
		setCurrentWidget(m_regSettingTab);
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