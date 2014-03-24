#include "systemtray.h"

SystemTray::SystemTray(QWidget *parent)
	: QSystemTrayIcon(parent)
{
	m_trayMenu = new QMenu();

	createTopWidget();
	createBottomWidget();
	createTrayMenu();
}

void SystemTray::createTopWidget()
{
	m_topWidget = new QWidget();
	m_topWidgetAction = new QWidgetAction(m_trayMenu);
	m_topLabel = new QLabel(QStringLiteral("HUST Information Security Lab"));
	m_topLabel->setObjectName(QStringLiteral("WhiteLabel"));
	m_homeBtn = new QPushButton(QStringLiteral("Details..."));
	m_homeBtn->setCursor(Qt::PointingHandCursor);
	m_homeBtn->setObjectName(QStringLiteral("TrayButton"));

	QVBoxLayout* m_topLayout = new QVBoxLayout();
	m_topLayout->addWidget(m_topLabel, 0, Qt::AlignLeft|Qt::AlignVCenter);
	m_topLayout->addWidget(m_homeBtn, 0, Qt::AlignRight|Qt::AlignVCenter);

	m_topLayout->setSpacing(5);
	m_topLayout->setContentsMargins(10, 5, 0, 5);

	m_topWidget->setLayout(m_topLayout);
	m_topWidget->installEventFilter(this);
	m_topWidgetAction->setDefaultWidget(m_topWidget);
}

void SystemTray::createBottomWidget()
{
	m_bottomWidget = new QWidget();
	m_bottomWidgetAction = new QWidgetAction(m_trayMenu);

	m_updateBtn = new QPushButton(QIcon(":/menu/update"), QStringLiteral("Update"));
	m_updateBtn->setObjectName(QStringLiteral("TrayButton"));

	m_aboutBtn = new QPushButton(QIcon(":/menu/about"), QStringLiteral("About"));
	m_aboutBtn->setObjectName(QStringLiteral("TrayButton"));

	m_exitBtn = new QPushButton(QIcon(":/menu/exit"), QStringLiteral("Exit"));
	m_exitBtn->setObjectName(QStringLiteral("TrayButton"));

	QHBoxLayout* m_bottomLayout = new QHBoxLayout();
	m_bottomLayout->addWidget(m_updateBtn, 0, Qt::AlignCenter);
	m_bottomLayout->addWidget(m_aboutBtn, 0, Qt::AlignCenter);
	m_bottomLayout->addWidget(m_exitBtn, 0, Qt::AlignCenter);

	m_bottomLayout->setSpacing(5);
	m_bottomLayout->setContentsMargins(10,0,10,5);

	m_bottomWidget->setLayout(m_bottomLayout);
	m_bottomWidgetAction->setDefaultWidget(m_bottomWidget);
}

void SystemTray::createTrayMenu()
{
	

	m_runOnSystemBoot = new QAction(QIcon(":/menu/autorun"), QStringLiteral("Run on System Boot"), this);
	m_helpOnline = new QAction(QIcon(":/menu/help"), QStringLiteral("Help Online"), this);
	m_homePage = new QAction(QIcon(":/menu/home"), QStringLiteral("Visit Home Page"), this);
	m_notification = new QAction(QIcon(":/menu/notification"), QStringLiteral("Security Notification"), this);
	m_settings = new QAction(QIcon(":/menu/settings"), QStringLiteral("Settings"), this);
	m_restoreWindow = new QAction(QIcon(":/menu/restore"), QStringLiteral("Restore Window"), this);

	m_trayMenu->addAction(m_topWidgetAction);
	m_trayMenu->addSeparator();
	m_trayMenu->addAction(m_helpOnline);
	m_trayMenu->addAction(m_homePage);
	m_trayMenu->addAction(m_notification);
	m_trayMenu->addSeparator();
	m_trayMenu->addAction(m_runOnSystemBoot);
	m_trayMenu->addAction(m_settings);
	m_trayMenu->addAction(m_restoreWindow);
	m_trayMenu->addSeparator();
	m_trayMenu->addAction(m_bottomWidgetAction);

	connect(m_homeBtn, SIGNAL(clicked()), this, SIGNAL(visitHomeBtnClicked()));
	connect(m_runOnSystemBoot, SIGNAL(triggered()), this, SIGNAL(runOSBTriggered()));
	connect(m_helpOnline, SIGNAL(triggered()), this, SIGNAL(helpOnlineTriggered()));
	connect(m_homePage, SIGNAL(triggered()), this, SIGNAL(homePageTriggered()));
	connect(m_notification, SIGNAL(triggered()), this, SIGNAL(notificationTriggered()));
	connect(m_restoreWindow, SIGNAL(triggered()), this, SIGNAL(restoreWindowTriggered()));
	connect(m_updateBtn, SIGNAL(clicked()), this, SIGNAL(updateBtnClicked()));
	connect(m_aboutBtn, SIGNAL(clicked()), this, SIGNAL(aboutBtnClicked()));
	connect(m_exitBtn, SIGNAL(clicked()), this, SIGNAL(exitBtnClicked()));

	setIcon(QIcon(":/background/logo"));
	m_trayMenu->setFixedWidth(200);
	setContextMenu(m_trayMenu);
}

bool SystemTray::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == m_topWidget && event->type() == QEvent::Paint)
	{
		QPainter painter(m_topWidget);
		painter.setPen(Qt::NoPen);
		painter.setBrush(QColor(42, 120, 192));
		painter.drawRect(m_topWidget->rect());
	}
	return QSystemTrayIcon::eventFilter(obj, event);
}