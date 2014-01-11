#include "networkpage.h"

NetworkPage::NetworkPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_realtimeTab = new RealTimeFlowTab;
	m_histTab = new HistoryFlowTab;
	m_rankTab = new AppRankTab;
	m_filterTab = new FlowFilterTab;
	m_portsTab = new PortsStatusTab;

	addTab(m_realtimeTab, QStringLiteral("Real Time"));
	addTab(m_histTab, QStringLiteral("History Trend"));
	addTab(m_rankTab, QStringLiteral("Flow Rank"));
	addTab(m_filterTab, QStringLiteral("Flow Filters"));
	addTab(m_portsTab, QStringLiteral("Ports Status"));
}

NetworkPage::~NetworkPage()
{
	if (m_realtimeTab) { delete m_realtimeTab; m_realtimeTab = NULL; }
	if (m_histTab) { delete m_histTab; m_histTab = NULL; }
	if (m_rankTab) { delete m_rankTab; m_rankTab = NULL; }
	if (m_filterTab) { delete m_filterTab; m_filterTab = NULL; }
	if (m_portsTab) { delete m_portsTab; m_portsTab = NULL; }
}

void NetworkPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_realtimeTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_histTab);
	}
	else if (index == 3)
	{
		setCurrentWidget(m_rankTab);
	}
	else if (index == 4)
	{
		setCurrentWidget(m_filterTab);
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

RealTimeFlowTab::~RealTimeFlowTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
HistoryFlowTab::HistoryFlowTab(QWidget *parent)
	: QWidget(parent)
{

}

HistoryFlowTab::~HistoryFlowTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
FlowFilterTab::FlowFilterTab(QWidget *parent)
	: QWidget(parent)
{

}

FlowFilterTab::~FlowFilterTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
AppRankTab::AppRankTab(QWidget *parent)
	: QWidget(parent)
{

}

AppRankTab::~AppRankTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
PortsStatusTab::PortsStatusTab(QWidget *parent)
	: QWidget(parent)
{

}

PortsStatusTab::~PortsStatusTab()
{

}
