#include "networkpage.h"
#include "base/CustomControl/nofocusdelegate.h"
#include <QFormLayout>
#include <QGroupBox>

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
	m_chart = new RealtimeChart("Network flow(KB/s)", "Network Flow Monitor", "Business", "Non-business", this);
	m_mainLayout = new QVBoxLayout(this);
	m_bottomLayout = new QHBoxLayout(this);
	m_leftGroup = new QGroupBox(QStringLiteral("Statistical"), this);
	m_rightGroup = new QGroupBox(QStringLiteral("Classification"), this);

	m_leftForm = new QFormLayout(this);
	m_rightForm = new QFormLayout(this);

	m_totalFlow_value = new QLabel(this);
	m_business_value = new QLabel(this);
	m_non_business_value = new QLabel(this);
	m_average_value = new QLabel(this);
	m_leftForm->addRow(QStringLiteral("Total:"), m_totalFlow_value);
	m_leftForm->addRow(QStringLiteral("Business:"), m_business_value);
	m_leftForm->addRow(QStringLiteral("Non-business:"), m_non_business_value);
	m_leftForm->addRow(QStringLiteral("Average:"), m_average_value);
	m_leftForm->setSpacing(10);
	m_leftForm->setContentsMargins(5, 5, 5, 3);

	m_tcp_value = new QLabel(this);
	m_udp_value = new QLabel(this);
	m_icmp_value = new QLabel(this);
	m_packets_average_value = new QLabel(this);
	m_rightForm->addRow(QStringLiteral("TCP packets: "), m_tcp_value);
	m_rightForm->addRow(QStringLiteral("UDP packets: "), m_tcp_value);
	m_rightForm->addRow(QStringLiteral("ICMP packets: "), m_tcp_value);
	m_rightForm->addRow(QStringLiteral("Packets Speed: "), m_tcp_value);
	m_rightForm->setSpacing(10);
	m_rightForm->setContentsMargins(5, 5, 5, 3);
	m_leftGroup->setFixedHeight(140);
	m_rightGroup->setFixedHeight(140);
	m_leftGroup->setLayout(m_leftForm);
	m_rightGroup->setLayout(m_rightForm);
	m_bottomLayout->addWidget(m_leftGroup);
	m_bottomLayout->addWidget(m_rightGroup);
	m_bottomLayout->setSpacing(5);
	m_bottomLayout->setContentsMargins(20, 0, 5, 5);
	m_mainLayout->addWidget(m_chart, 1);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(5);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
	m_global_timer = new QTimer(this);
	m_global_timer->start(1000);
	connect(m_global_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void RealTimeFlowTab::onTimeout()
{


}

//////////////////////////////////////////////////////////////////////////
//
AppRankTab::AppRankTab(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QHBoxLayout(this);
	m_model = new CustomItemModel(0, 6, this);
	m_view = new QTableView(this);
	m_view->setShowGrid(false);
	m_view->setAlternatingRowColors(true);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->verticalHeader()->hide();
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setItemDelegate(new NoFocusDelegate(this));
	m_view->setModel(m_model);

	m_layout->addWidget(m_view);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}

//////////////////////////////////////////////////////////////////////////
//
PortsStatusTab::PortsStatusTab(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QVBoxLayout(this);
	m_infoLabel = new QLabel(QStringLiteral("Loading..."), this);
	m_infoLabel->setObjectName(QStringLiteral("BlueLabel"));

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
	m_view->setItemDelegate(new NoFocusDelegate(this));
	m_view->setModel(m_model);

	m_layout->addWidget(m_view, 1);
	m_layout->addWidget(m_infoLabel, 0, Qt::AlignLeft);
	m_layout->setSpacing(2);
	m_layout->setContentsMargins(0,0,0,0);
	setLayout(m_layout);
}

