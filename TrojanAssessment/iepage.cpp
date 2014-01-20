#include "iepage.h"

IEPage::IEPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_cacheTab = new BrowserCacheTab;
	m_pluginsTab = new PluginsTab;
	m_cookieTab = new BrowserCookiesTab;
	m_settingsTab = new IESettingsTab;

	
	addTab(m_cacheTab, QStringLiteral("IE Caches"));
	addTab(m_pluginsTab, QStringLiteral("Browser Plugins"));
	addTab(m_cookieTab, QStringLiteral("Host Cookies"));
	addTab(m_settingsTab, QStringLiteral("Browser Settings"));
}

IEPage::~IEPage()
{
	if (m_cacheTab) { delete m_cacheTab; m_cacheTab = NULL; }
	if (m_pluginsTab) { delete m_pluginsTab; m_pluginsTab = NULL; }
	if (m_cookieTab) { delete m_cookieTab; m_cookieTab = NULL; }
	if (m_settingsTab) { delete m_settingsTab; m_settingsTab = NULL; }
}

void IEPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_cacheTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_pluginsTab);
	}
	else if (index == 3)
	{
		setCurrentWidget(m_cookieTab);
	}
	else  // IE settings
	{
		setCurrentWidget(m_settingsTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
BrowserCacheTab::BrowserCacheTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText(QStringLiteral("Filter expression"));
	m_filterCol = new QComboBox(this);
	//add items
	m_filterCol->addItem(QStringLiteral("By File Name"), 0);
	m_filterCol->addItem(QStringLiteral("By URL Name"), 1);
	m_filterCol->addItem(QStringLiteral("By Access Time"), 7);
	m_filterCol->addItem(QStringLiteral("By Modified Time"), 8);
	m_refresh = new QPushButton(QStringLiteral("Refresh"), this);
	m_clear = new QPushButton(QStringLiteral("Clean Cache"), this);
	m_view = new QPushButton(QStringLiteral("Properties"), this);
	m_viewList = new QTableView(this);
	m_viewList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_viewList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_viewList->setSortingEnabled(true);
	m_viewList->sortByColumn(0, Qt::AscendingOrder);
	m_viewList->verticalHeader()->hide();
	m_viewList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	m_viewList->setWordWrap(false);
	m_proxyModel = new QSortFilterProxyModel(this);
	m_viewList->setModel(m_proxyModel);
	m_srcModel = new QStandardItemModel(0, 10, this);
	m_proxyModel->setSourceModel(m_srcModel);
	// initialize and create the header of model.
	m_srcModel->setHeaderData(0, Qt::Horizontal, QStringLiteral("File Name"));
	m_srcModel->setHeaderData(1, Qt::Horizontal, QStringLiteral("Cache URL"));
	m_srcModel->setHeaderData(2, Qt::Horizontal, QStringLiteral("Local Path"));
	m_srcModel->setHeaderData(3, Qt::Horizontal, QStringLiteral("Sub Folder"));
	m_srcModel->setHeaderData(4, Qt::Horizontal, QStringLiteral("Header Info"));
	m_srcModel->setHeaderData(5, Qt::Horizontal, QStringLiteral("Hits"));
	m_srcModel->setHeaderData(6, Qt::Horizontal, QStringLiteral("Size"));
	m_srcModel->setHeaderData(7, Qt::Horizontal, QStringLiteral("Last Access"));
	m_srcModel->setHeaderData(8, Qt::Horizontal, QStringLiteral("Last Modified"));
	m_srcModel->setHeaderData(9, Qt::Horizontal, QStringLiteral("Expiration"));
	initialModel();

	m_mainLayout = new QVBoxLayout(this);  // the main layout widget should be initialized first.
	m_topLayout = new QHBoxLayout(this);

	m_topLayout->addWidget(m_filterExp, 1);
	m_topLayout->addWidget(m_filterCol);
	m_topLayout->addWidget(m_refresh);
	m_topLayout->addWidget(m_clear);
	m_topLayout->addWidget(m_view);

	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_viewList, 1);
	setLayout(m_mainLayout);

	connect(m_filterExp, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterExpChanged(const QString&)));
	connect(m_filterCol, SIGNAL(currentIndexChanged(int)), this, SLOT(onFilterColChanged(int)));
	connect(m_refresh, SIGNAL(clicked()), this, SLOT(onRefreshClicked()));
	connect(m_clear, SIGNAL(clicked()), this, SLOT(onCleanClicked()));
	connect(m_view, SIGNAL(clicked()), this, SLOT(onViewPropertyClicked()));
}

void BrowserCacheTab::initialModel()
{
	m_srcModel->removeRows(0, m_srcModel->rowCount());
	const int ROW = 0;
	IECacheInfo cache;
	vector<CacheEntry> vc = cache.getCacheEntVec();
	for (vector<CacheEntry>::const_iterator ci = vc.cbegin(); ci != vc.cend(); ++ci)
	{
		m_srcModel->insertRow(0);
		m_srcModel->setData(m_srcModel->index(ROW, 0), (*ci).m_fileName.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 1), (*ci).m_urlStr.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 2), (*ci).m_localPath.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 3), (*ci).m_subFolder.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 4), (*ci).m_headerInfo.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 5), (*ci).m_hits);
		m_srcModel->setData(m_srcModel->index(ROW, 6), (*ci).m_entrySize);
		m_srcModel->setData(m_srcModel->index(ROW, 7), (*ci).m_lastAccess.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 8), (*ci).m_lastModified.c_str());
		m_srcModel->setData(m_srcModel->index(ROW, 9), (*ci).m_expiration.c_str());
	}
}

void BrowserCacheTab::onFilterExpChanged(const QString& e)
{
	QRegExp exp(m_filterExp->text(), Qt::CaseInsensitive, QRegExp::FixedString);
	m_proxyModel->setFilterRegExp(exp);
}

void BrowserCacheTab::onFilterColChanged(int index)
{
	m_proxyModel->setFilterKeyColumn(m_filterCol->itemData(index).toInt());
}

void BrowserCacheTab::onRefreshClicked()
{
	initialModel();
}

void BrowserCacheTab::onCleanClicked()
{
	QMessageBox::information(this, QStringLiteral("Tips"), QStringLiteral("Coming"), QMessageBox::Ok|QMessageBox::Cancel);
}

void BrowserCacheTab::onViewPropertyClicked()
{
	QItemSelectionModel* selModel = m_viewList->selectionModel();
	// make sure the current index is valid.
	if (selModel->hasSelection())
	{
		QModelIndex cindex = selModel->currentIndex();
		CacheEntryDetail cd(this, cindex, m_srcModel);
		cd.exec();
	}
	else
	{
		QMessageBox::critical(this, QStringLiteral("Error"), QStringLiteral("You have to choose at least one row!"), QMessageBox::Ok);
	}
}

BrowserCacheTab::~BrowserCacheTab()
{


}

//////////////////////////////////////////////////////////////////////////
//
PluginsTab::PluginsTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText("Filter expression");
	m_viewList = new QTableView(this);
	m_model = new QSortFilterProxyModel(this);
	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_filterExp);
	m_layout->addWidget(m_viewList, 1);

	setLayout(m_layout);
}

PluginsTab::~PluginsTab()
{


}

//////////////////////////////////////////////////////////////////////////
//
BrowserCookiesTab::BrowserCookiesTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText("Filter");
	m_openWithNotepad = new QPushButton(QIcon(QStringLiteral(":images/26.ico")), QStringLiteral("Open..."), this);
	m_openWithNotepad->setToolTip(QStringLiteral("Open with notepad"));
	m_openWithWordpad = new QPushButton(QIcon(QStringLiteral(":images/24.ico")), QStringLiteral("Open..."), this);
	m_openWithWordpad->setToolTip(QStringLiteral("Open with wordpad"));
	m_viewProperties = new QPushButton(QStringLiteral("Properties"), this);
	m_cookiesList = new QTableView(this);
	m_detailsList = new QTableView(this);
	m_model = new QSortFilterProxyModel(this);
	m_dlgBtnBox = new QDialogButtonBox(this);
	m_dlgBtnBox->addButton(m_viewProperties, QDialogButtonBox::AcceptRole);

	m_mainLayout = new QVBoxLayout(this);   // the main layout widget should be initialized first.
	m_topLayout = new QHBoxLayout(this);
	
	
	m_topLayout->addWidget(m_filterExp);
	m_topLayout->addWidget(m_openWithNotepad);
	m_topLayout->addWidget(m_openWithWordpad);

	
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_cookiesList);
	m_mainLayout->addWidget(m_detailsList, 1);
	m_mainLayout->addWidget(m_dlgBtnBox);

	setLayout(m_mainLayout);	
	connect(m_dlgBtnBox, SIGNAL(accepted()), this, SLOT(accept()));
}

BrowserCookiesTab::~BrowserCookiesTab()
{


}

//////////////////////////////////////////////////////////////////////////
//
IESettingsTab::IESettingsTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_IEsettings = new QGroupBox(QStringLiteral("IE Settings"), this);
	m_dlgBtnBox = new QDialogButtonBox(this);
	m_apply = new QPushButton(QStringLiteral("Apply"), this);
	m_dlgBtnBox->addButton(m_apply, QDialogButtonBox::AcceptRole);

	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_IEsettings, 1);
	m_layout->addWidget(m_dlgBtnBox);

	setLayout(m_layout);
}

IESettingsTab::~IESettingsTab()
{


}
