#include "trojanassessment.h"

TrojanAssessment::TrojanAssessment(QWidget *parent)
	: ShadowWindow(parent)
{
	// layout for main widget
	m_mainLayout = new QVBoxLayout(this);
	/* set window icon */
	setWindowIcon(QIcon(QStringLiteral(":/background/logo")));
	/* set the width and height of the window fixed. */
	setFixedSize(900, 600);
	// create tree widget and stacked widget
	treeWidget = new QTreeWidget(this);
	treeWidget->setFrameShape(QFrame::NoFrame);
	stackedWidget = new QStackedWidget(this);
	stackedWidget->resize(680, 500);
	stackedWidget->setFrameShape(QFrame::NoFrame);
	initStackedWidget();
	initTreeWidget();
	
	splitter = new QSplitter(Qt::Horizontal, this);
	splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	splitter->setHandleWidth(1);
	splitter->addWidget(treeWidget);
	splitter->addWidget(stackedWidget);
	splitter->handle(1)->setDisabled(true);

	// create title widget and status bar
	titleWidget = new TitleWidget(this);
	icon_label = new QLabel(this);
	icon_label->setPixmap(QPixmap(":/menu/cloud"));
	icon_label->setFixedSize(QPixmap(":/menu/cloud").size());
	lastrun_label = new QLabel(this);
	m_bottomLayout = new QHBoxLayout(this);
	m_bottomLayout->addStretch();
	m_bottomLayout->addWidget(icon_label, 0, Qt::AlignCenter);
	m_bottomLayout->addWidget(lastrun_label, 0, Qt::AlignCenter);
	m_bottomLayout->setSpacing(5);
	m_bottomLayout->setContentsMargins(0, 3, 10, 3);

	// remember the time when the program start
	login_dt = QDateTime::currentDateTime();
	restoreSettings();

	QPalette plt;
	plt.setBrush(QPalette::Window, QBrush(Qt::white));
	treeWidget->setPalette(plt);
	treeWidget->setAutoFillBackground(true);
	stackedWidget->setPalette(plt);
	stackedWidget->setAutoFillBackground(true);

	// settings for main layout
	m_mainLayout->addWidget(titleWidget);
	m_mainLayout->addWidget(splitter);
	m_mainLayout->addLayout(m_bottomLayout);
	m_mainLayout->setSpacing(0);
	m_mainLayout->setContentsMargins(5, 5, 5, 5);
	setLayout(m_mainLayout);
	/* take responding actions when the user clicked any items in the tree widget */
	connect(treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), SLOT(changePage(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(treeWidget, SIGNAL(toolButtonChangePage(QTreeWidgetItem*, QTreeWidgetItem*)), SLOT(changePage(QTreeWidgetItem*, QTreeWidgetItem*)));
	connect(titleWidget, SIGNAL(ShowMinimizedBtnClicked()), SLOT(showMinimized()));
	connect(titleWidget, SIGNAL(CloseWindowBtnClicked()), SLOT(close()));
	connect(titleWidget, SIGNAL(SettingsBtnClicked()), SLOT(onShowSettingsMenu()));
	connect(titleWidget, SIGNAL(ToolBtnClicked(int)), SLOT(onToolBtnClicked(int)));
}

void TrojanAssessment::initTreeWidget()
{
	treeWidget->setColumnCount(1);
	treeWidget->setHeaderHidden(true);
	QList<QTreeWidgetItem*> childs;

	/* top level node has no parent, so we set it as NULL */
	file = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("File Monitors")));
	childs.clear();
	childs.append(new QTreeWidgetItem(file, QStringList(QString("Data files"))));
	childs.append(new QTreeWidgetItem(file, QStringList(QString("Executable files"))));
	childs.append(new QTreeWidgetItem(file, QStringList(QString("File Browser"))));
	file->addChildren(childs);
	treeWidget->addTopLevelItem(file);

	/* add the fiveth top level node with children filled */
	browser = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Internet Explorer")));
	childs.clear();
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Browser Cache"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("IE Plugins"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Cookies"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Monitor Settings"))));
	browser->addChildren(childs);
	treeWidget->addTopLevelItem(browser);

	/* add the third top level node with children filled */
	mem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("System Memory")));
	childs.clear();
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("System Usage"))));
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("Memory Monitor"))));
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("Memory Protection"))));
	mem->addChildren(childs);
	treeWidget->addTopLevelItem(mem);

	/* add the fourth top level node with children filled */
	flow = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Network Flow")));
	childs.clear();
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Real Time"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("History Trend"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Flow Rank"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Netflow Filter"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Ports Status"))));
	flow->addChildren(childs);
	treeWidget->addTopLevelItem(flow);

	/* add the second top level node with children filled */
	process = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Process Center")));
	childs.clear();
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Runtime Monitor"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Windows Services"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Process Running"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Software Installed"))));
	process->addChildren(childs);
	treeWidget->addTopLevelItem(process);

	/* add the sixth top level node with children filled */
	registers = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Windows Register")));
	childs.clear();
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Register Details"))));
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Settings"))));
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Monitor Settings"))));
	registers->addChildren(childs);
	treeWidget->addTopLevelItem(registers);

	/* add the seventh top level node with children filled */
	stat = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Security Center")));
	childs.clear();
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("Assessment"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("System Info"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("Loaded Libraries"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("About"))));
	stat->addChildren(childs);
	treeWidget->addTopLevelItem(stat);

	/* set icons for every child tree widgets item */
	QTreeWidgetItemIterator iterator(treeWidget, QTreeWidgetItemIterator::NoChildren);
	while (*iterator)
	{
		(*iterator)->setIcon(0, QIcon(":images/23.ico"));
		++iterator;
	}
	/* expand all top level items after created the window */
	treeWidget->expandAll();

}

void TrojanAssessment::initStackedWidget()
{
	/* initialize the stacked pages */
	fmp = new FileMonitorPage(this);
	iep = new IEPage(this);
	mp = new MemoryPage(this);
	np = new NetworkPage(this);
	pp = new ProcessPage(this);
	rp = new RegisterPage(this);
	scp = new SecurityCenterPage(this);

	//add page widgets to StackedWidgets
	stackedWidget->addWidget(fmp);
	stackedWidget->addWidget(iep);
	stackedWidget->addWidget(mp);
	stackedWidget->addWidget(np);
	stackedWidget->addWidget(pp);
	stackedWidget->addWidget(rp);
	stackedWidget->addWidget(scp);
	// set File Monitoring as the default page.
	stackedWidget->setCurrentWidget(fmp);

	connect(this, SIGNAL(changeTabFMP(int)), fmp, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabPP(int)), pp, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabMP(int)), mp, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabNP(int)), np, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabRP(int)), rp, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabSCP(int)), scp, SLOT(onChangeTab(int)));
	connect(this, SIGNAL(changeTabIEP(int)), iep, SLOT(onChangeTab(int)));
}

void TrojanAssessment::changePage(QTreeWidgetItem* cur, QTreeWidgetItem* prev)
{
	if (cur && cur != prev)
	{
		QString str;
		// to determine which kind of page user clicked.
		QTreeWidgetItem* ptr = cur->parent();   
		if (!ptr)  //it is a top level item
		{
			str = cur->text(0);
			if (str == "File Monitors")
			{
				stackedWidget->setCurrentWidget(fmp);	
			}
			else if (str == "Process Center")
			{
				stackedWidget->setCurrentWidget(pp);	
			}
			else if (str == "System Memory")
			{
				stackedWidget->setCurrentWidget(mp);	
			}
			else if (str == "Network Flow")
			{
				stackedWidget->setCurrentWidget(np);	
			}
			else if (str == "Internet Explorer")
			{
				stackedWidget->setCurrentWidget(iep);	
			}
			else if (str == "Windows Register")
			{
				stackedWidget->setCurrentWidget(rp);	
			}
			else  // Assessment page
			{
				stackedWidget->setCurrentWidget(scp);	
			}
		}
		else  //children items
		{
			str = ptr->text(0);
			if (str == "File Monitors")
			{
				stackedWidget->setCurrentWidget(fmp);	
				if (cur->text(0) == "Data files")
				{
					emit changeTabFMP(1);
				}
				else if (cur->text(0) == "Executable files")
				{
					emit changeTabFMP(2);
				}
				else  // file browser
				{
					emit changeTabFMP(3);
				}
			}
			else if (str == "Process Center")
			{
				stackedWidget->setCurrentWidget(pp);	
				if (cur->text(0) == "Runtime Monitor")
				{
					emit changeTabPP(1);
				}
				else if (cur->text(0) == "Windows Services")
				{
					emit changeTabPP(2);
				}
				else if (cur->text(0) == "Process Running")
				{
					emit changeTabPP(3);
				}
				else  // software installed
				{
					emit changeTabPP(4);
				}
			}
			else if (str == "System Memory")
			{
				stackedWidget->setCurrentWidget(mp);	
				if (cur->text(0) == "System Usage")
				{
					emit changeTabMP(1);
				}
				else if (cur->text(0) == "Memory Monitor")
				{
					emit changeTabMP(2);
				}
				else  // Memory protection
				{
					emit changeTabMP(3);
				}
			}
			else if (str == "Network Flow")
			{
				stackedWidget->setCurrentWidget(np);	
				if (cur->text(0) == "Real Time")
				{
					emit changeTabNP(1);
				}
				else if (cur->text(0) == "History Trend")
				{
					emit changeTabNP(2);
				}
				else if (cur->text(0) == "Flow Rank")
				{
					emit changeTabNP(3);
				}
				else if (cur->text(0) == "Netflow Filter")
				{
					emit changeTabNP(4);
				}
				else  //ports status
				{
					emit changeTabNP(5);
				}
			}
			else if (str == "Internet Explorer")
			{
				stackedWidget->setCurrentWidget(iep);	
				if (cur->text(0) == "Browser Cache")
				{
					emit changeTabIEP(1);
				}
				else if (cur->text(0) == "IE Plugins")
				{
					emit changeTabIEP(2);
				}
				else if (cur->text(0) == "Cookies")
				{
					emit changeTabIEP(3);
				}
				else //settings
				{
					emit changeTabIEP(4);
				}
			}
			else if (str == "Windows Register")
			{
				stackedWidget->setCurrentWidget(rp);	
				if (cur->text(0) == "Register Details")
				{
					emit changeTabRP(1);
				}
				else if (cur->text(0) == "Settings")
				{
					emit changeTabRP(2);
				}
				else // monitor settings
				{
					emit changeTabRP(3);
				}
			}
			else  // Assessment center
			{
				stackedWidget->setCurrentWidget(scp);	
				if (cur->text(0) == "System Info")
				{
					emit changeTabSCP(1);
				}
				else if (cur->text(0) == "Loaded Libraries")
				{
					emit changeTabSCP(2);
				}
				else if (cur->text(0) == "Assessment")
				{
					emit changeTabSCP(3);
				}
				else //about
				{
					About about(this);
					about.exec();
				}
			}
		}
	}
}

void TrojanAssessment::onToolBtnClicked(int index)
{
	QTreeWidgetItem* prev = treeWidget->currentItem();
	// Get the widget item in tree widget corresponding to the
	// tool button the user clicked.
	QTreeWidgetItem* cur = treeWidget->topLevelItem(index);
	emit toolButtonChangePage(cur, prev);
}

void TrojanAssessment::onShowSettingsMenu()
{
	
}

void TrojanAssessment::paintEvent(QPaintEvent* event)
{
	// First, we pass the paint event to parent widget to draw window shadow.
	// Then, we do our specific painting stuff.
	ShadowWindow::paintEvent(event);
	// draw the background using the specified image.
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPixmap(5, 5, width()-10, height()-10, QPixmap(":/background/title_background"));
}

void TrojanAssessment::storeSettings()
{
	QString dt = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-M-d h:m"));
	settings->beginGroup(QStringLiteral("UI"));
	settings->setValue(QStringLiteral("Geometry"), saveGeometry());
	settings->setValue(QStringLiteral("Login"), login_dt.toString(QStringLiteral("yyyy-M-d h:m")));
	settings->endGroup();

	settings->beginGroup(QStringLiteral("Configuration"));
	settings->setValue(QStringLiteral("Database"), QStringLiteral("Mysql"));
	settings->endGroup();
}

void TrojanAssessment::restoreSettings()
{
	/* set status bar*/
	settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, QStringLiteral("HUST"), QStringLiteral("TrojanDetector"));
	settings->beginGroup(QStringLiteral("UI"));
	restoreGeometry(settings->value(QStringLiteral("Geometry")).toByteArray());
	QString dt = QString("[Last run]: <b><font color=blue>%1</font></b>").arg(settings->value("Login", "/").toString());
	lastrun_label->setText(dt);
	settings->endGroup();

	settings->beginGroup(QStringLiteral("Configuration"));
	settings->endGroup();

}

void TrojanAssessment::closeEvent(QCloseEvent *event)
{
	int ret = QMessageBox::question(this,
		QStringLiteral("Warning"),
		QStringLiteral("Are you sure you want to exit?"),
		QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		storeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

TrojanAssessment::~TrojanAssessment()
{
	if (file) { delete file; file = NULL;}
	if (process) { delete process; process = NULL; }
	if (mem) { delete mem; mem = NULL; }
	if (flow) { delete flow; flow = NULL; }
	if (browser) { delete browser; browser = NULL; }
	if (registers) { delete registers; registers = NULL; }
	if (stat) { delete stat; stat = NULL; }
	if (settings) { delete settings; settings = NULL; }
}