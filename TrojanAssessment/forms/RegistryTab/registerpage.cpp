#include "registerpage.h"

RegisterPage::RegisterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_regMonitorTab = new RegMonitorTab(this);
	m_regSettingTab = new RegSettingsTab(this);

	addTab(m_regMonitorTab, QStringLiteral("Register Monitor"));
	addTab(m_regSettingTab, QStringLiteral("Settings"));
}

void RegisterPage::onChangeTab(int index)
{
	if (index == 1)
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
RegSettingsTab::RegSettingsTab(QWidget *parent)
	: QWidget(parent)
{

}

//////////////////////////////////////////////////////////////////////////
//
RegMonitorTab::RegMonitorTab(QWidget *parent)
	: QWidget(parent)
{

}
