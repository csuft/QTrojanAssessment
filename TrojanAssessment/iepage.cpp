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
	m_filterExp->setPlaceholderText(QStringLiteral("Filter"));
	m_find = new QPushButton(QStringLiteral("Find..."), this);
	m_delete = new QPushButton(QStringLiteral("Delete"), this);
	m_clear = new QPushButton(QStringLiteral("Clear All"), this);
	m_view = new QPushButton(QStringLiteral("View"), this);
	m_viewList = new QTableView(this);
	m_proxyModel = new QSortFilterProxyModel(this);

	m_mainLayout = new QVBoxLayout(this);  // the main layout widget should be initialized first.
	m_topLayout = new QHBoxLayout(this);

	m_topLayout->addWidget(m_filterExp, 1);
	m_topLayout->addWidget(m_find);
	m_topLayout->addWidget(m_delete);
	m_topLayout->addWidget(m_clear);
	m_topLayout->addWidget(m_view);

	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addWidget(m_viewList, 1);

	setLayout(m_mainLayout);
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
