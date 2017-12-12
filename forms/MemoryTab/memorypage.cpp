#include "memorypage.h"
#include "../../3rdParty/ChartDirector/realtimechart.h"
#include "../../3rdParty/Manometer/manometer.h"
#include "../../base/BusinessLayer/DynamicMemory.h"
#include <QLineEdit>
#include <QHeaderView>
#include <vector>
using std::vector;

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
	m_memory = new DynamicMemory();
	m_mainLayout = new QVBoxLayout(this);
	m_filter = new QLineEdit(this);
	m_filter->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_filter->setFixedHeight(25);

	m_procList = new QTableView(this);
	QVector<int> vcenter;
	for (int i = 0; i < 9; ++i) vcenter.push_back(i);
	m_procModel = new CustomItemModel(vcenter, QVector<int>(), 0, 9, this);
	createTableHeaders();
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
	m_procList->setWordWrap(false);

	// specify the width of columns
	m_procList->setColumnWidth(0, 45);
	m_procList->setColumnWidth(1, 120);
	m_procList->setColumnWidth(2, 65);
	m_procList->setColumnWidth(3, 60);
	m_procList->setColumnWidth(4, 60);
	m_procList->setColumnWidth(5, 50);
	m_procList->setColumnWidth(6, 50);
	m_procList->setColumnWidth(7, 55);
	m_procList->setColumnWidth(8, 55);

	m_completer = new QCompleter(this);
	m_completer->setModel(m_procModel);
	m_filter->setCompleter(m_completer);
	fulfillTable();
	m_mainLayout->addWidget(m_filter);
	m_mainLayout->addWidget(m_procList, 1);
	m_mainLayout->setSpacing(1);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}

void SysUsageTab::createTableHeaders()
{
	// PageFaultCount, PeakWorkingSetSize, WorkingSetSize, QuotaPeakPagedPoolUsage, QuotaPagedPoolUsage
	// QuotaPeakNonPagedPoolUsage, QuotaNonPagedPoolUsage, PagefileUsage, PeakPagefileUsage
	m_procModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("PID"));
	m_procModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("Name"));
	m_procModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("PageFault"));
	m_procModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("Peak WSS"));
	m_procModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("WSS"));
	m_procModel->setHeaderData(5, Qt::Horizontal, QStringLiteral("QPPPU"));
	m_procModel->setHeaderData(6, Qt::Horizontal, QStringLiteral("QPPU"));
	m_procModel->setHeaderData(7, Qt::Horizontal, QStringLiteral("QPNPPU"));
	m_procModel->setHeaderData(8, Qt::Horizontal, QStringLiteral("QNPPU"));
	m_procModel->setHeaderData(9, Qt::Horizontal, QStringLiteral("PU"));
	m_procModel->setHeaderData(10, Qt::Horizontal, QStringLiteral("PPU"));
}

void SysUsageTab::fulfillTable()
{
	const vector<ProcessMemory> items = m_memory->getProcessMemory();
	for (vector<ProcessMemory>::const_iterator ci = items.cbegin(); ci != items.cend(); ++ci)
	{
		m_procModel->insertRow(0);
		m_procModel->setData(m_procModel->index(0, 0), QString::number(ci->pid, 10));
		m_procModel->setData(m_procModel->index(0, 1), QString::fromStdWString(ci->pname) );
		m_procModel->setData(m_procModel->index(0, 2), QString::number(ci->PageFaultCount, 16));
		m_procModel->setData(m_procModel->index(0, 3), QString::number(ci->PeakWorkingSetSize, 16));
		m_procModel->setData(m_procModel->index(0, 4), QString::number(ci->WorkingSetSize, 16));
		m_procModel->setData(m_procModel->index(0, 5), QString::number(ci->QuotaPeakPagedPoolUsage, 16));
		m_procModel->setData(m_procModel->index(0, 6), QString::number(ci->QuotaPagedPoolUsage, 16));
		m_procModel->setData(m_procModel->index(0, 7), QString::number(ci->QuotaPeakNonPagedPoolUsage, 16));
		m_procModel->setData(m_procModel->index(0, 8), QString::number(ci->QuotaNonPagedPoolUsage, 16));
		m_procModel->setData(m_procModel->index(0, 9), QString::number(ci->PagefileUsage, 16));
		m_procModel->setData(m_procModel->index(0, 10), QString::number(ci->PeakPagefileUsage, 16));
	}
}

SysUsageTab::~SysUsageTab()
{
	delete m_memory;
}

//////////////////////////////////////////////////////////////////////////
// 
MemMonitorTab::MemMonitorTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_timer = new QTimer(this);
	m_mainLayout = new QVBoxLayout(this);
	m_formLayout = new QFormLayout(this);
	m_groupBox = new QGroupBox(QStringLiteral("Statistical"), this);
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
	m_formLayout->setSpacing(10);
	m_groupBox->setLayout(m_formLayout);
	m_groupBox->setFixedHeight(130);
	m_bottomLayout->addWidget(m_memusage);
	m_bottomLayout->addWidget(m_groupBox);
	m_bottomLayout->setSpacing(20);
	m_bottomLayout->setContentsMargins(15, 5, 10, 5);

	m_mainLayout->addWidget(m_chart);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(5);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
	m_timer->start(1000);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdateTimer()));
}

void MemMonitorTab::onUpdateTimer()
{
	int r = qrand();
	m_memusage->setValue(r%80);
}

MemMonitorTab::~MemMonitorTab()
{

}

//////////////////////////////////////////////////////////////////////////
// 
MemProtectionTab::MemProtectionTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_memproperty = new MemoryProps();
	m_layout = new QVBoxLayout(this);
	m_view = new QTableView(this);
	QVector<int> vcenter;
	for (int i = 0; i < 8; ++i) vcenter.push_back(i);
	m_model = new CustomItemModel(vcenter, QVector<int>(), 0, 8, this);
	createTableHeaders();
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

	// specify the width of columns
	m_view->setColumnWidth(0, 50);
	m_view->setColumnWidth(1, 100);
	m_view->setColumnWidth(2, 50);
	m_view->setColumnWidth(3, 110);
	m_view->setColumnWidth(4, 85);
	m_view->setColumnWidth(5, 70);
	m_view->setColumnWidth(6, 55);
	m_view->setColumnWidth(7, 50);

	fulfillTable();
	m_layout->addWidget(m_view);
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
}
void MemProtectionTab::createTableHeaders()
{

	// PID, AllocationBase, State, AllocationProtect, BaseAddress, RegionSize, Type, Protect
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("PID"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Allocation Base"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("State"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Allocation Protect"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Base Address"));
	m_model->setHeaderData(5, Qt::Horizontal, QStringLiteral("Region Size"));
	m_model->setHeaderData(6, Qt::Horizontal, QStringLiteral("Type"));
	m_model->setHeaderData(7, Qt::Horizontal, QStringLiteral("Protect"));

}

void MemProtectionTab::fulfillTable()
{
	const vector<MemoryProperty> citems = m_memproperty->getMemoryState();
	for (vector<MemoryProperty>::const_iterator ci = citems.cbegin(); ci != citems.end(); ++ci)
	{
		m_model->insertRow(0);
		m_model->setData(m_model->index(0, 0), QString::number(ci->pid, 10));
		m_model->setData(m_model->index(0, 1), QString::number(ci->AllocationBase, 16));
		m_model->setData(m_model->index(0, 2), QString::number(ci->State, 16));
		m_model->setData(m_model->index(0, 3), QString::number(ci->AllocationProtect, 16));
		m_model->setData(m_model->index(0, 4), QString::number(ci->BaseAddress, 16));
		m_model->setData(m_model->index(0, 5), QString::number(ci->RegionSize, 16));
		m_model->setData(m_model->index(0, 6), QString::number(ci->Type, 16));
		m_model->setData(m_model->index(0, 7), QString::number(ci->Protect, 16));
	}
}

MemProtectionTab::~MemProtectionTab()
{
	delete m_memproperty;
}