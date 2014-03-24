#include "networkpage.h"

NetworkPage::NetworkPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_realtimeTab = new RealTimeFlowTab(this);
	m_rankTab = new AppRankTab(this);
	m_portsTab = new PortsStatusTab(this);

	addTab(m_realtimeTab, QStringLiteral("Real Time"));
	addTab(m_rankTab, QStringLiteral("Flow Rank"));
	addTab(m_portsTab, QStringLiteral("Ports Status"));
}

void NetworkPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_realtimeTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_rankTab);
	}
	else
	{
		setCurrentWidget(m_portsTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
RealTimeFlowTab::RealTimeFlowTab(QWidget *parent)
	: QWidget(parent)
{

}

//////////////////////////////////////////////////////////////////////////
//
AppRankTab::AppRankTab(QWidget *parent)
	: QWidget(parent)
{

}

//////////////////////////////////////////////////////////////////////////
//
PortsStatusTab::PortsStatusTab(QWidget *parent)
	: QWidget(parent)
{

}

