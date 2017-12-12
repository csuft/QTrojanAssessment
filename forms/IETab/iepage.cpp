#include "iepage.h"

IEPage::IEPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_cacheTab = new BrowserCacheTab(this);
	m_pluginsTab = new PluginsTab(this);
	m_cookieTab = new BrowserCookiesTab(this);
	m_settingsTab = new IESettingsTab(this);

	addTab(m_cacheTab, QStringLiteral("IE Caches"));
	addTab(m_pluginsTab, QStringLiteral("Browser Plugins"));
	addTab(m_cookieTab, QStringLiteral("Host Cookies"));
	addTab(m_settingsTab, QStringLiteral("Browser Settings"));
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
//BrowserCacheTab contains a list of Cache files used by Internet Explorer.
BrowserCacheTab::BrowserCacheTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText(QStringLiteral("Filter expression"));
	m_filterExp->setFixedHeight(25);
	m_filterCol = new QComboBox(this);
	m_filterCol->setFixedHeight(25);
	//add items
	m_filterCol->addItem(QStringLiteral("By File Name"), 0);
	m_filterCol->addItem(QStringLiteral("By URL Name"), 1);
	m_filterCol->addItem(QStringLiteral("By Access Time"), 7);
	m_filterCol->addItem(QStringLiteral("By Modified Time"), 8);

	m_refresh = new QPushButton(QStringLiteral("Refresh"), this);
	m_refresh->setFixedSize(75, 25);
	m_clear = new QPushButton(QStringLiteral("Clean Cache"), this);
	m_clear->setFixedSize(75, 25);
	m_view = new QPushButton(QStringLiteral("Properties"), this);
	m_view->setFixedSize(75, 25);
	// initialize model proxy and connect with the source model.
	m_proxyModel = new QSortFilterProxyModel(this);
	// specify which columns align center;
	QVector<int> center; 
	center.push_back(3);
	center.push_back(5);
	center.push_back(6);
	m_srcModel = new CustomItemModel(center, QVector<int>(), 0, 10, this);
	m_proxyModel->setSourceModel(m_srcModel);

	m_viewList = new QTableView(this);
	m_viewList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_viewList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_viewList->setSortingEnabled(false);
	m_viewList->verticalHeader()->hide();
	m_viewList->setWordWrap(false);
	m_viewList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_viewList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_viewList->setShowGrid(false);
	m_viewList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_viewList->horizontalHeader()->setHighlightSections(false);
	m_viewList->setItemDelegate(new NoFocusDelegate());
	m_viewList->setModel(m_proxyModel);
	m_viewList->setAlternatingRowColors(true);  // alternative colors 
	m_viewList->setFrameShape(QFrame::NoFrame);

	// column width
	m_viewList->setColumnWidth(0, 85);
	m_viewList->setColumnWidth(1, 180);
	m_viewList->setColumnWidth(2, 90);
	m_viewList->setColumnWidth(3, 80);
	m_viewList->setColumnWidth(4, 80);
	m_viewList->setColumnWidth(5, 30);
	m_viewList->setColumnWidth(6, 40);
	m_viewList->setColumnWidth(7, 120);
	m_viewList->setColumnWidth(8, 120);
	m_viewList->setColumnWidth(9, 120);

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
	m_topLayout->addWidget(m_filterExp, 1, Qt::AlignVCenter);
	m_topLayout->addWidget(m_filterCol, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_refresh, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_clear, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_view, 0, Qt::AlignVCenter);
	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(1, 1, 2, 1);

	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_viewList, 1);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(0,0,0,0);
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


//////////////////////////////////////////////////////////////////////////
// The tab contains the list of plugins installed on IE
PluginsTab::PluginsTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText("Filter expression");
	m_filterExp->setFixedHeight(25);
	m_viewList = new QTableView(this);
	m_model = new QSortFilterProxyModel(this);
	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_filterExp);
	m_layout->addWidget(m_viewList, 1);
	m_layout->setSpacing(1);
	m_layout->setContentsMargins(0,1,0,1);

	setLayout(m_layout);
}

//////////////////////////////////////////////////////////////////////////
// To list all cookie files generated by website and client
BrowserCookiesTab::BrowserCookiesTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText("Filter");
	m_filterExp->setFixedHeight(25);
	m_openWithNotepad = new QPushButton(QStringLiteral("Open..."), this);
	m_openWithNotepad->setFixedSize(75, 25);
	m_openWithNotepad->setToolTip(QStringLiteral("Open with notepad"));
	m_openWithWordpad = new QPushButton(QStringLiteral("Open..."), this);
	m_openWithWordpad->setFixedSize(75, 25);
	m_openWithWordpad->setToolTip(QStringLiteral("Open with wordpad"));

	m_detailsList = new QTableWidget(this);
	QVector<int> alignCols;
	int cols[] = {1, 2, 3, 4, 5, 6, 7};
	for (int i = 0; i < 7; ++i)
	{
		alignCols.push_back(cols[i]);
	}
	m_model = new CustomItemModel(alignCols, QVector<int>(), 0, 9, this);

	createHeader();
	createCookieModel();
	m_proxyModel = new QSortFilterProxyModel(this);
	m_proxyModel->setSourceModel(m_model);
	
	m_cookiesList = new QTableView(this);
	m_cookiesList->setWordWrap(false);
	m_cookiesList->setMouseTracking(true);
	m_cookiesList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_cookiesList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_cookiesList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_cookiesList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_cookiesList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_cookiesList->setShowGrid(false);
	m_cookiesList->horizontalHeader()->setHighlightSections(false);
	m_cookiesList->setItemDelegate(new NoFocusDelegate());
	m_cookiesList->verticalHeader()->hide();
	m_cookiesList->setFrameShape(QFrame::NoFrame);
	m_cookiesList->setAlternatingRowColors(true);
	m_cookiesList->setModel(m_proxyModel);

	// specify the width of columns
	int width[] = {105, 40, 115, 115, 105, 50, 55, 50};
	for (int i = 0; i < 8; ++i)
	{
		m_cookiesList->setColumnWidth(i, width[i]);
	}
	
	// the main layout widget should be initialized first.
	m_mainLayout = new QVBoxLayout(this);   
	m_topLayout = new QHBoxLayout(this);
	m_topLayout->addWidget(m_filterExp, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_openWithNotepad, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_openWithWordpad, 0, Qt::AlignVCenter);
	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(1, 1, 1, 1);

	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_cookiesList);
	m_mainLayout->addWidget(m_detailsList);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(0,0,0,0);

	setLayout(m_mainLayout);	
	connect(m_cookiesList, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onTableViewClicked(const QModelIndex&)));
	connect(m_cookiesList, SIGNAL(entered(const QModelIndex&)), this, SLOT(showToolTips(const QModelIndex&)));
	connect(m_filterExp, SIGNAL(textChanged(const QString&)), this, SLOT(onFilterExpChanged(const QString&)));
}

void BrowserCookiesTab::createHeader()
{
	// for View/Model architecture
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("Website"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Hits"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("Last Access"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Last Modified"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Cookie File"));
	m_model->setHeaderData(5, Qt::Horizontal, QStringLiteral("Size"));
	m_model->setHeaderData(6, Qt::Horizontal, QStringLiteral("User"));
	m_model->setHeaderData(7, Qt::Horizontal, QStringLiteral("Order"));
	m_model->setHeaderData(8, Qt::Horizontal, QStringLiteral("Local Path"));

	// for Table view widget
	QStringList labelList;
	labelList << "Key" << "Value" << "Domain" << "Expiration" << "Creation" << "Creator";
	m_detailsList->setColumnCount(6);
	m_detailsList->setHorizontalHeaderLabels(labelList);
	m_detailsList->setWordWrap(false);
	m_detailsList->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_detailsList->setSelectionMode(QAbstractItemView::SingleSelection);
	m_detailsList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_detailsList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_detailsList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_detailsList->verticalHeader()->hide();
	m_detailsList->horizontalHeader()->setStretchLastSection(true);
	m_detailsList->setAlternatingRowColors(true);
	m_detailsList->setShowGrid(false);
	m_detailsList->setFrameShape(QFrame::NoFrame);
}

void BrowserCookiesTab::createCookieModel()
{
	int count = 0;
	const int ROW = 0;
	IECookieInfo chelper; 
	vector<CookieEntry> vc = chelper.getCacheEntVec();
	for (vector<CookieEntry>::const_iterator ci = vc.cbegin(); ci != vc.cend(); ++ci)
	{
		count += 1;
		m_model->insertRow(0);
		m_model->setData(m_model->index(ROW, 0), (*ci).m_website.c_str());
		m_model->setData(m_model->index(ROW, 1), (*ci).m_hits);
		m_model->setData(m_model->index(ROW, 2), (*ci).m_lastAccess.c_str());
		m_model->setData(m_model->index(ROW, 3), (*ci).m_lastModified.c_str());
		m_model->setData(m_model->index(ROW, 4), (*ci).m_fileName.c_str());
		m_model->setData(m_model->index(ROW, 5), (*ci).m_cookieSize);
		m_model->setData(m_model->index(ROW, 6), (*ci).m_user.c_str());
		m_model->setData(m_model->index(ROW, 7), (*ci).m_recordNum);
		m_model->setData(m_model->index(ROW, 8), (*ci).m_localPath.c_str());
	}
}

void BrowserCookiesTab::resolveCookies(const char* fileName)
{
	CookieRecord entry;
	vector<CookieRecord> vc;
	char buffer[1024] = {'\0'};
	char low[16] = {'\0'};
	char high[16] = {'\0'};
	char* chStart = NULL;
	char* chEnd = NULL;
	ifstream cookie(IECookieInfo::getCookiePath(fileName));
	while (cookie.getline(buffer, 1024, '*'))
	{
		memset(&entry, 0, sizeof(CookieRecord));
		// key
		chStart = buffer;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_key, chStart, chEnd-chStart);
		// value
		chStart = chEnd + 1;  // skip the single newline
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_value, chStart, chEnd-chStart);
		// domain
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_domain, chStart, chEnd-chStart);
		// flag
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(entry.m_flag, chStart, chEnd-chStart);
		// the length of "Server" is the same as "Client", 6 bytes.
		strncpy(entry.m_creator, setCreator(entry.m_flag), 6);
		// low expiration time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(low, chStart, chEnd-chStart);
		// high expiration time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(high, chStart, chEnd-chStart);
		transformTime(low, high, entry.m_expiration);
		// low creation time
		memset(low, 0, 16);
		memset(high, 0, 16);
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(low, chStart, chEnd-chStart);
		// low creation time
		chStart = chEnd + 1;
		chEnd = strchr(chStart, '\n');
		strncpy(high, chStart, chEnd-chStart);
		transformTime(low, high, entry.m_creation);

		vc.push_back(entry);
		memset(buffer, 0, 512);
		cookie.ignore();
	}
	cookie.close();
	createDetailsView(vc);
}

void BrowserCookiesTab::createDetailsView(const vector<CookieRecord>& vc)
{
	int index = 0;
	int total = vc.size();
	m_detailsList->clearContents();
	m_detailsList->setRowCount(total);
	for (vector<CookieRecord>::const_iterator ci = vc.cbegin(); ci != vc.cend(); ++ci, ++index)
	{
		m_detailsList->setItem(index, 0, new QTableWidgetItem(QString((*ci).m_key)) );
		m_detailsList->setItem(index, 1, new QTableWidgetItem(QString((*ci).m_value)) );
		m_detailsList->setItem(index, 2, new QTableWidgetItem(QString((*ci).m_domain)) );
		m_detailsList->setItem(index, 3, new QTableWidgetItem(QString((*ci).m_expiration)) );
		m_detailsList->setItem(index, 4, new QTableWidgetItem(QString((*ci).m_creation)) );
		m_detailsList->setItem(index, 5, new QTableWidgetItem(QString((*ci).m_creator)) );
	}
}

void BrowserCookiesTab::transformTime(const char* low, const char* high, char* dst)
{
	FILETIME ft;
	SYSTEMTIME st;
	const int BUFFER_SIZE = 32;
	char chBuffer[BUFFER_SIZE] = {'\0'};

	ft.dwLowDateTime = atol(low);
	ft.dwHighDateTime = atol(high);
	FileTimeToLocalFileTime(&ft, &ft);
	FileTimeToSystemTime(&ft, &st);
	_snprintf(chBuffer, BUFFER_SIZE,"%04d-%02d-%02d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	strncpy(dst, chBuffer, BUFFER_SIZE);
}

const char* BrowserCookiesTab::setCreator(const char* flag)
{
	long val = atol(flag);
	// if the remainder is nonzero, then the cookie is created by browser scripts(such as js, vb).
	// Otherwise, it is created by web server.
	return val%0x100?"Client":"Server";
}

void BrowserCookiesTab::onTableViewClicked(const QModelIndex& index)
{
	// Retrieve the cookie file name from the fifth column
	QString cookieName = m_proxyModel->data(m_proxyModel->index(index.row(), 4)).toString();
	resolveCookies(cookieName.toStdString().c_str());
}

void BrowserCookiesTab::onFilterExpChanged(const QString& text)
{
	QRegExp regexp(m_filterExp->text(), Qt::CaseInsensitive, QRegExp::FixedString);
	m_proxyModel->setFilterRegExp(regexp);
}

void BrowserCookiesTab::showToolTips(const QModelIndex& index)
{
	if (index.isValid())
	{
		QToolTip::showText(QCursor::pos(), index.data().toString());
	}
}

//////////////////////////////////////////////////////////////////////////
// Shows IE options for users.
IESettingsTab::IESettingsTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	m_IEsettings = new QGroupBox(QStringLiteral("IE Settings"), this);
	m_dlgBtnBox = new QDialogButtonBox(this);
	m_apply = new QPushButton(QStringLiteral("Apply"), this);
	m_apply->setFixedSize(75, 25);
	m_dlgBtnBox->addButton(m_apply, QDialogButtonBox::AcceptRole);

	m_layout = new QVBoxLayout(this);
	m_layout->addWidget(m_IEsettings, 1);
	m_layout->addWidget(m_dlgBtnBox, 0, Qt::AlignVCenter);
	m_layout->setSpacing(3);
	m_layout->setContentsMargins(0,0,0,1);
	setLayout(m_layout);
}
