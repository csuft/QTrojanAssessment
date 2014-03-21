#include "processpage.h"

ProcessPage::ProcessPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_processTab = new ProcessListTab(this);
	m_runtimeTab = new RuntimeMonitorTab(this);
	m_softTab = new SoftwareInstalledTab(this);
	m_serviceTab = new WinServicesTab(this);

	addTab(m_runtimeTab, QStringLiteral("Runtime Monitoring"));
	addTab(m_serviceTab, QStringLiteral("Windows Services"));
	addTab(m_processTab, QStringLiteral("Process Snapshot"));
	addTab(m_softTab, QStringLiteral("Software Installed"));
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

//////////////////////////////////////////////////////////////////////////
//
WinServicesTab::WinServicesTab(QWidget *parent)
	: QWidget(parent)
{
	//m_srcModel = new QStandardItemModel(this);
	m_view = new QTableView(this);
	m_view->verticalHeader()->hide();

	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_view, 1);
	setLayout(m_layout);
}

//////////////////////////////////////////////////////////////////////////
// To show the snapshot of running process
ProcessListTab::ProcessListTab(QWidget *parent)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_filterExp->setFixedHeight(25);
	m_refresh = new QPushButton(QStringLiteral("Refresh"), this);
	m_refresh->setFixedSize(75, 25);

	QVector<int> colsAlignCenter;
	for (int i = 1; i <= 5; ++i)
	{
		colsAlignCenter.push_back(i);
	}
	m_srcModel = new CustomItemModel(colsAlignCenter, QVector<int>(), 0, 6, this);  // initially 0 row and 6 cols.
	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_srcModel);
	// setup completer
	m_completer = new QCompleter(m_srcModel, this);
	m_completer->setWrapAround(false);
	m_completer->setCompletionMode(QCompleter::PopupCompletion);
	m_completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	m_completer->setMaxVisibleItems(10);
	m_filterExp->setCompleter(m_completer);

	m_mainLayout = new QVBoxLayout(this);
	m_topLayout = new QHBoxLayout(this);
	m_topLayout->addWidget(m_filterExp, 1, Qt::AlignVCenter);
	m_topLayout->addWidget(m_refresh, 0, Qt::AlignVCenter);
	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(1, 1, 1, 1);
	
	initProcList();
	m_helper = new RetrieveHelper;
	loadProcessList();
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_view);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}

void ProcessListTab::initProcList()
{
	m_view = new QTableView(this);
	m_view->setWordWrap(false);
	m_view->verticalHeader()->hide();
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->setShowGrid(false);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setItemDelegate(new NoFocusDelegate());
	m_view->horizontalHeader()->setHighlightSections(false);
	m_view->setFrameShape(QFrame::NoFrame);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->setModel(m_proxyModel);
	m_view->setAlternatingRowColors(true);

	// specify the widths of columns
	int widths[] = {180, 50, 80, 55, 70};
	for (int i = 0; i < 5; ++i)
	{
		m_view->setColumnWidth(i, widths[i]);
	}
	createProcHeader();
}

void ProcessListTab::createProcHeader()
{
	m_srcModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("Process Name"));
	m_srcModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("PID"));
	m_srcModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("Thread Count"));
	m_srcModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("PPID"));
	m_srcModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Prior Base"));
	m_srcModel->setHeaderData(5, Qt::Horizontal, QStringLiteral("Prior Class"));
	m_srcModel->setHeaderData(6, Qt::Horizontal, QStringLiteral("Path"));
}

void ProcessListTab::loadProcessList()
{
	const int INSERT_ROW = 0;
	m_srcModel->removeRows(INSERT_ROW, m_srcModel->rowCount());
	const vector<ProcEntry> pec = m_helper->getProclist();
	QFileIconProvider fip;
	for (vector<ProcEntry>::const_iterator ci = pec.cbegin(); ci != pec.cend(); ++ci)
	{
		m_srcModel->insertRow(INSERT_ROW);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 0), QString::fromStdWString((*ci).procName));
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 1), (*ci).procId);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 2), (*ci).ctThread);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 3), (*ci).procPid);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 4), (*ci).priorBase);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 5), (*ci).priorClass);
		m_srcModel->setData(m_srcModel->index(INSERT_ROW, 6), QString::fromStdWString((*ci).exePath));
		QFileInfo file(QString::fromStdWString((*ci).exePath));
		m_srcModel->item(INSERT_ROW, 0)->setIcon(fip.icon(file));
	}
}

//////////////////////////////////////////////////////////////////////////
// The tab contains a list of software installed
SoftwareInstalledTab::SoftwareInstalledTab(QWidget *parent)
	: QWidget(parent)
{
	m_helper = new RetrieveHelper;
	initAppList();
	m_mainLayout = new QVBoxLayout(this);
	m_mainLayout->addWidget(m_view);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_mainLayout);

	loadApplist();
}

void SoftwareInstalledTab::initAppList()
{
	m_model = new CustomItemModel(0, 5, this);
	m_view = new QTableView(this);
	m_view->verticalHeader()->hide();
	m_view->setShowGrid(false);
	m_view->setWordWrap(false);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->horizontalHeader()->setDefaultSectionSize(150);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->horizontalHeader()->setHighlightSections(false);
	m_view->verticalHeader()->setDefaultSectionSize(25);
	m_view->setItemDelegate(new NoFocusDelegate());
	m_view->setFrameShape(QFrame::NoFrame);
	m_view->setModel(m_model);
	m_view->setAlternatingRowColors(true);

	// specify the widths of columns
	int widths[] = {250, 85, 70, 220, 140};
	for (int i = 0; i < 5; ++i)
	{
		m_view->setColumnWidth(i, widths[i]);
	}

	createAppListHeader();
}

void SoftwareInstalledTab::createAppListHeader()
{
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("App Name"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Version"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("Install Date"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Location"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Publisher"));
}

void SoftwareInstalledTab::loadApplist()
{
	const int INSERT_ROW = 0;
	m_model->removeRows(INSERT_ROW, m_model->rowCount());
	const vector<AppEntry> pec = m_helper->getApplist();
	for (vector<AppEntry>::const_iterator ci = pec.cbegin(); ci != pec.cend(); ++ci)
	{
		m_model->insertRow(0);
		m_model->setData(m_model->index(INSERT_ROW, 0), QString::fromStdWString((*ci).appName));
		m_model->setData(m_model->index(INSERT_ROW, 1), QString::fromStdWString((*ci).appVer));
		m_model->setData(m_model->index(INSERT_ROW, 2), QString::fromStdWString((*ci).installDate));
		m_model->setData(m_model->index(INSERT_ROW, 3), QString::fromStdWString((*ci).location));
		m_model->setData(m_model->index(INSERT_ROW, 4), QString::fromStdWString((*ci).publisher));
	}
}