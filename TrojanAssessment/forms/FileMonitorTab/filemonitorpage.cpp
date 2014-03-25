#include "filemonitorpage.h"

FileMonitorPage::FileMonitorPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_execFileTab = new ExecFileTab(this);
	m_dataFileTab = new DataFileTab(this);
	m_browserTab = new FileBrowserTab(this);

	addTab(m_dataFileTab, QStringLiteral("Data Files"));
	addTab(m_execFileTab, QStringLiteral("Executable Files"));
	addTab(m_browserTab, QStringLiteral("File Browser"));
}

void FileMonitorPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_dataFileTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_execFileTab);
	}
	else
	{
		setCurrentWidget(m_browserTab);
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Implementation of FileMonitorPage class.
DataFileTab::DataFileTab(QWidget* parent)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout(this);
	m_statusLayout = new QHBoxLayout(this);
	m_topLayout = new QHBoxLayout(this);
	m_bottomLayout = new QHBoxLayout(this);

	// top layout
	m_filter = new QLineEdit(this);
	m_filter->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_filter->setFixedHeight(25);
	m_clearBtn = new QPushButton(QStringLiteral("Clear"), this);
	m_clearBtn->setFixedSize(75, 25);
	m_exportBtn = new QPushButton(QStringLiteral("Export"), this);
	m_exportBtn->setFixedSize(75, 25);
	m_topLayout->addWidget(m_filter, 1, Qt::AlignCenter);
	m_topLayout->addWidget(m_clearBtn, 0, Qt::AlignCenter);
	m_topLayout->addWidget(m_exportBtn, 0, Qt::AlignCenter);
	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(1, 1, 1, 1);

	// table view 
	m_model = new CustomItemModel(0, 6, this);
	m_proxy = new QSortFilterProxyModel(this);
	m_proxy->setSourceModel(m_model);
	m_view = new QTableView(this);
	m_view->horizontalHeader()->setStretchLastSection(true);
	m_view->horizontalHeader()->setHighlightSections(false);
	m_view->verticalHeader()->hide();
	m_view->setShowGrid(false);
	m_view->setAlternatingRowColors(true);
	m_view->setSelectionMode(QAbstractItemView::SingleSelection);
	m_view->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_view->setModel(m_proxy);

	// bottom layout
	m_chooseDir = new QPushButton(QStringLiteral("Choose..."), this);
	m_chooseDir->setFixedSize(75, 25);
	m_startBtn = new QPushButton(QStringLiteral("Start"), this);
	m_startBtn->setFixedSize(75, 25);
	m_stopBtn = new QPushButton(QStringLiteral("Stop"), this);
	m_stopBtn->setFixedSize(75, 25);
	m_bottomLayout = new QHBoxLayout(this);
	m_bottomLayout->addStretch();
	m_bottomLayout->addWidget(m_chooseDir, 0, Qt::AlignVCenter);
	m_bottomLayout->addWidget(m_startBtn, 0, Qt::AlignVCenter);
	m_bottomLayout->addWidget(m_stopBtn, 0, Qt::AlignVCenter);
	m_bottomLayout->setSpacing(5);
	m_bottomLayout->setContentsMargins(1, 1, 1, 1);

	// status information label
	m_status = new QLabel(QStringLiteral("Directory: "), this);
	m_status->setFixedHeight(25);
	m_status_info = new QLineEdit(this);
	m_status_info->setPlaceholderText(QStringLiteral("Please first choose monitoring directory"));
	m_status_info->setReadOnly(true);
	m_status_info->setFixedHeight(25);
	m_status->setBuddy(m_status_info);
	m_statusLayout->addWidget(m_status, 0, Qt::AlignVCenter);
	m_statusLayout->addWidget(m_status_info, 1, Qt::AlignVCenter);
	m_statusLayout->setSpacing(5);
	m_statusLayout->setContentsMargins(1, 1, 1, 1);

	// main layout
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_view, 1, Qt::AlignCenter);
	m_mainLayout->addLayout(m_statusLayout);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(1);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}

//////////////////////////////////////////////////////////////////////////
// Implementation of ExecFileTab class.
ExecFileTab::ExecFileTab(QWidget* parent)
	: QWidget(parent)
{

}

//////////////////////////////////////////////////////////////////////////
// Implementation of FileBrowserTab class.
FileBrowserTab::FileBrowserTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_model = new QFileSystemModel(this);
	m_model->setRootPath(QDir::currentPath());
	
	m_view = new QTreeView(this);
	m_view->setModel(m_model);
	m_view->setSortingEnabled(true);
	m_view->setIndentation(20);
	m_view->setFrameShape(QFrame::NoFrame);
	m_view->setAnimated(true);

	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_view, 1);
	m_layout->setContentsMargins(0,0,0,0);
	setLayout(m_layout);
}