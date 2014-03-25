#include "registerpage.h"

RegisterPage::RegisterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_regMonitorTab = new RegMonitorTab(this);
	m_regSettingTab = new RegSettingsTab(this);

	addTab(m_regMonitorTab, QStringLiteral("Register Monitor"));
	addTab(m_regSettingTab, QStringLiteral("Settings"));
}

void RegisterPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_regMonitorTab);
	}
	else
	{
		setCurrentWidget(m_regSettingTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
RegSettingsTab::RegSettingsTab(QWidget *parent)
	: QWidget(parent)
{
	m_group = new QGroupBox(QStringLiteral("Registry Options"), this);
	m_layout = new QVBoxLayout(this);

	m_layout->addWidget(m_group);
	m_layout->setContentsMargins(1, 1, 1, 1);
	setLayout(m_layout);
}

//////////////////////////////////////////////////////////////////////////
//
RegMonitorTab::RegMonitorTab(QWidget *parent)
	: QWidget(parent)
{
	m_mainLayout = new QVBoxLayout(this);
	m_topLayout = new QHBoxLayout(this);
	m_centerLayout = new QHBoxLayout(this);

	// top layout
	m_registryRoot = new QPushButton(QStringLiteral("Reg Root"), this);
	m_registryRoot->setFixedSize(75, 25);
	m_startBtn = new QPushButton(QStringLiteral("Start"), this);
	m_startBtn->setFixedSize(75, 25);
	m_stopBtn = new QPushButton(QStringLiteral("Stop"), this);
	m_stopBtn->setFixedSize(75, 25);
	m_topLayout->addStretch();
	m_topLayout->addWidget(m_registryRoot, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_startBtn, 0, Qt::AlignVCenter);
	m_topLayout->addWidget(m_stopBtn, 0, Qt::AlignVCenter);
	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(0, 1, 1, 1);

	// center layout
	m_filter = new QLineEdit(this);
	m_filter->setPlaceholderText(QStringLiteral("Filter Expression"));
	m_filter->setFixedHeight(25);
	m_clearBtn = new QPushButton(QStringLiteral("Clear"), this);
	m_clearBtn->setFixedSize(75, 25);
	m_exportBtn = new QPushButton(QStringLiteral("Export"), this);
	m_exportBtn->setFixedSize(75, 25);
	m_centerLayout->addWidget(m_filter, 1, Qt::AlignVCenter);
	m_centerLayout->addWidget(m_clearBtn, 0, Qt::AlignVCenter);
	m_centerLayout->addWidget(m_exportBtn, 0, Qt::AlignVCenter);
	m_centerLayout->setSpacing(5);
	m_centerLayout->setContentsMargins(1, 1, 1, 1);

	// main layout
	m_model = new CustomItemModel(0, 5, this); 
	m_proxy = new QSortFilterProxyModel(this);
	m_proxy->setSourceModel(m_model);

	m_view = new QTableView(this);
	m_view->verticalHeader()->hide();
	m_view->setModel(m_proxy);
	m_mainLayout->addLayout(m_topLayout);
	m_mainLayout->addLayout(m_centerLayout);
	m_mainLayout->addWidget(m_view, 1, Qt::AlignCenter);
	m_mainLayout->setSpacing(1);
	m_mainLayout->setContentsMargins(0, 0, 0, 0);

	setLayout(m_mainLayout);
}
