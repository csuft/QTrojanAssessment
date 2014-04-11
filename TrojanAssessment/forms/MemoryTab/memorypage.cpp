#include "memorypage.h"
#include "3rdParty/ChartDirector/realtimechart.h"
#include "3rdParty/Manometer/manometer.h"
#include <QLineEdit>
#include <QHeaderView>

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
	m_mainLayout = new QVBoxLayout(this);
	m_filter = new QLineEdit(this);
	m_filter->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_filter->setFixedHeight(25);

	m_procList = new QTableView(this);
	m_procModel = new CustomItemModel(0, 9, this);
	m_proxy = new QSortFilterProxyModel(this);
	m_proxy->setSourceModel(m_procModel);
	m_procList->setModel(m_proxy);
	m_procList->verticalHeader()->hide();
	m_procList->horizontalHeader()->setStretchLastSection(true);
	m_procList->setShowGrid(false);
	m_procList->setAlternatingRowColors(true);
	m_procList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_procList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_procList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_procList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_procList->setItemDelegate(new NoFocusDelegate(this));
	m_procList->setFrameShape(QFrame::NoFrame);
	m_procList->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_completer = new QCompleter(this);
	m_completer->setModel(m_procModel);
	m_filter->setCompleter(m_completer);

	m_mainLayout->addWidget(m_filter);
	m_mainLayout->addWidget(m_procList, 1);
	m_mainLayout->setSpacing(1);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}

SysUsageTab::~SysUsageTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
MemMonitorTab::MemMonitorTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout(this);
	m_formLayout = new QFormLayout(this);
	m_bottomLayout = new QHBoxLayout(this);

	m_chart = new RealtimeChart("Primary Memory", "Memory Usage Monitor", "Used", "Available", this);
	m_memusage = new ManoMeter(this);
	m_memusage->setValue(0);
	m_memusage->setMaximum(80);
	m_memusage->setSuffix("%");
	m_memusage->setFixedSize(150, 150);
	m_total_mem = new QLabel(this);
	m_avail_mem = new QLabel(this);
	m_used_mem = new QLabel(this);

	m_formLayout->addRow(QStringLiteral("Total Memory: "), m_total_mem);
	m_formLayout->addRow(QStringLiteral("Available Memory: "), m_avail_mem);
	m_formLayout->addRow(QStringLiteral("Used Memory: "), m_used_mem);

	m_bottomLayout->addWidget(m_memusage);
	m_bottomLayout->addLayout(m_formLayout);
	m_bottomLayout->setSpacing(5);
	m_bottomLayout->setContentsMargins(15, 5, 5, 5);

	m_mainLayout->addWidget(m_chart);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(5);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}

MemMonitorTab::~MemMonitorTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
MemProtectionTab::MemProtectionTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_layout = new QVBoxLayout(this);
	m_view = new QTableView(this);
	m_model = new CustomItemModel(0, 9, this);

	m_view->setShowGrid(false);
	m_view->setAlternatingRowColors(true);
	m_view->verticalHeader()->hide();
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setModel(m_model);
	m_view->setSortingEnabled(false);
	m_view->setWordWrap(false);
	m_view->setFrameShape(QFrame::NoFrame);
	m_view->setItemDelegate(new NoFocusDelegate(this));
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

	m_layout->addWidget(m_view);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}

MemProtectionTab::~MemProtectionTab()
{

}