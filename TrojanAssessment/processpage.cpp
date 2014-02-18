#include "processpage.h"

ProcessPage::ProcessPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_processTab = new ProcessListTab;
	m_runtimeTab = new RuntimeMonitorTab;
	m_softTab = new SoftwareInstalledTab;
	m_serviceTab = new WinServicesTab;

	addTab(m_runtimeTab, QStringLiteral("Runtime Monitoring"));
	addTab(m_serviceTab, QStringLiteral("Windows Services"));
	addTab(m_processTab, QStringLiteral("Process Snapshot"));
	addTab(m_softTab, QStringLiteral("Software Installed"));
}

ProcessPage::~ProcessPage()
{
	if (m_processTab) { delete m_processTab; m_processTab = NULL; }
	if (m_runtimeTab) { delete m_runtimeTab; m_runtimeTab = NULL; }
	if (m_softTab) { delete m_softTab; m_softTab = NULL; }
	if (m_serviceTab) { delete m_serviceTab; m_serviceTab = NULL; }
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

RuntimeMonitorTab::~RuntimeMonitorTab()
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

WinServicesTab::~WinServicesTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
ProcessListTab::ProcessListTab(QWidget *parent)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_srcModel = new QStandardItemModel(0, 6, this);  // initially 0 row and 6 cols.
	// setup view headers
	m_completer = new QCompleter(m_srcModel, this);
	m_completer->setWrapAround(false);
	m_completer->setCompletionMode(QCompleter::PopupCompletion);
	m_completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	m_completer->setMaxVisibleItems(10);
	m_refresh = new QPushButton(QStringLiteral("Refresh"), this);

	m_mainLayout = new QVBoxLayout(this);
	m_topLayout = new QHBoxLayout(this);
	m_topLayout->addWidget(m_filterExp, 1);
	m_topLayout->addWidget(m_refresh);

	m_view = new QTableView(this);
	m_view->setWordWrap(false);
	m_view->verticalHeader()->hide();
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->setGridStyle(Qt::DotLine);
	m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_view, 1);
	setLayout(m_mainLayout);
}

ProcessListTab::~ProcessListTab()
{

}


//////////////////////////////////////////////////////////////////////////
//
SoftwareInstalledTab::SoftwareInstalledTab(QWidget *parent)
	: QWidget(parent)
{
	m_view = new QTableView(this);
	m_view->verticalHeader()->hide();
	m_view->setGridStyle(Qt::DotLine);
	m_view->setWordWrap(false);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	m_model = new QStandardItemModel(0, 6, this);
	// setup view headers
	m_view->setModel(m_model);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_export = new QPushButton(QStringLiteral("Export..."), this);
	m_mainLayout = new QVBoxLayout(this);
	m_bottomLayout = new QHBoxLayout(this);
	m_bottomLayout->addStretch(1);
	m_bottomLayout->addWidget(m_export);

	m_mainLayout->addWidget(m_view, 1);
	m_mainLayout->addLayout(m_bottomLayout);
	setLayout(m_mainLayout);
}

SoftwareInstalledTab::~SoftwareInstalledTab()
{

}
