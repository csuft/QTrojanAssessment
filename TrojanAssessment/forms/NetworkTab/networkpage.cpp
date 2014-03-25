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
	m_layout = new QVBoxLayout(this);
	m_infoLabel = new QLabel(QStringLiteral("Loading..."), this);

	m_model = new CustomItemModel(0, 5, this);

	m_view = new QTableView(this);
	m_view->verticalHeader()->hide();
	m_view->horizontalHeader()->setHighlightSections(false);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->setShowGrid(false);
	m_view->setAlternatingRowColors(true);
	m_view->verticalHeader()->setDefaultSectionSize(25);
	m_view->setModel(m_model);

	m_layout->addWidget(m_view, 1, Qt::AlignCenter);
	m_layout->addWidget(m_infoLabel, 0, Qt::AlignLeft);
	m_layout->setSpacing(2);
	m_layout->setContentsMargins(1, 1, 1, 1);
	setLayout(m_layout);
}

