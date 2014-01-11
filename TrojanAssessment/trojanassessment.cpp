#include "trojanassessment.h"

TrojanAssessment::TrojanAssessment(QWidget *parent)
	: QMainWindow(parent), lineEdit(QStringLiteral("Reading settings...")), normalStatus(QStringLiteral("Version: 1.1(Beta)"))
{
	ui.setupUi(this);
	setWindowTitle(QStringLiteral("System Security Assessment Platform"));
	setStyleSheet(QString("font-family:Î¢ÈíÑÅºÚ; font-size: 9pt;"));
	/* disable the maximum button */
	Qt::WindowFlags flag = windowFlags();
	flag &= ~Qt::WindowMaximizeButtonHint;
	setWindowFlags(flag);
	/* initialize the stacked pages */
	fmp = new FileMonitorPage;
	iep = new IEPage;
	mp = new MemoryPage;
	np = new NetworkPage;
	pp = new ProcessPage;
	rp = new RegisterPage;
	scp = new SecurityCenterPage;

	initStackedWidget();
	/* set the splitter stretch factor */
	ui.splitter->addWidget(ui.treeWidget);
	ui.splitter->addWidget(ui.stackedWidget);
	ui.splitter->setStretchFactor(0, 2);
	ui.splitter->setStretchFactor(1, 2);
	//ui.splitter->setOpaqueResize(true);
	// disable stretch behaviour of QSplitter container widget.
	QSplitterHandle* qsh = ui.splitter->handle(1);
	qsh->setDisabled(false);

	/* set window icon */
	setWindowIcon(QIcon(QStringLiteral(":images/4.ico")));

	/* set the width and height of the window fixed. */
	setMaximumSize(800, 500);
	setMinimumSize(800, 500);

	/* initialize tool bar */
	ui.toolBar->addAction(ui.actionExport);
	ui.toolBar->addAction(ui.actionIE_Browser);
	ui.toolBar->addAction(ui.actionIE_Plugins);
	ui.toolBar->addAction(ui.actionFlow_Rank);
	ui.toolBar->addAction(ui.actionFile_Monitors);
	miscbar = addToolBar(QStringLiteral("Misc"));
	miscbar->setObjectName(QStringLiteral("MiscToolBar"));
	miscbar->addAction(ui.actionLocal_Help);
	miscbar->addAction(ui.actionAbout_Program);
	miscbar->addAction(ui.actionAbout_Qt);
	miscbar->addAction(ui.actionExit);

	login_dt = QDateTime::currentDateTime();
	ui.statusBar->addPermanentWidget(&lineEdit);
	ui.statusBar->addWidget(&normalStatus);

	restoreSettings();
	initTreeWidget();

	/* take responding actions when the user clicked any items in the tree widget */
	connect(ui.actionExit, SIGNAL(triggered()), SLOT(on_action_Exit_triggered()));
	connect(ui.actionFile_Monitors, SIGNAL(triggered()), SLOT(on_actionFile_Monitor_triggered()));
	connect(ui.actionFlow_Rank, SIGNAL(triggered()), SLOT(on_actionFlow_Rank_triggered()));
	connect(ui.actionIE_Plugins, SIGNAL(triggered()), SLOT(on_actionPlugins_triggered()));
	connect(ui.actionIE_Browser, SIGNAL(triggered()), SLOT(on_actionBrowser_triggered()));
	connect(ui.actionAbout_Program, SIGNAL(triggered()), SLOT(on_action_About_triggered()));
	connect(ui.actionLocal_Help, SIGNAL(triggered()), SLOT(on_action_Local_Help_triggered()));
	connect(ui.treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), SLOT(changePage(QTreeWidgetItem*, QTreeWidgetItem*)));
}

void TrojanAssessment::initTreeWidget()
{
	ui.treeWidget->setColumnCount(1);
	ui.treeWidget->setHeaderHidden(true);
	QList<QTreeWidgetItem*> childs;

	/* top level node has no parent, so we set it as NULL */
	file = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("File Monitors")));
	childs.clear();
	childs.append(new QTreeWidgetItem(file, QStringList(QString("Data files"))));
	childs.append(new QTreeWidgetItem(file, QStringList(QString("Executable files"))));
	childs.append(new QTreeWidgetItem(file, QStringList(QString("File Browser"))));
	file->addChildren(childs);
	ui.treeWidget->addTopLevelItem(file);
	/* add the second top level node with children filled */
	process = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Process Center")));
	childs.clear();
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Runtime Monitor"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Windows Services"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Process Running"))));
	childs.append(new QTreeWidgetItem(process, QStringList(QString("Software Installed"))));
	process->addChildren(childs);
	ui.treeWidget->addTopLevelItem(process);
	/* add the third top level node with children filled */
	mem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("System Memory")));
	childs.clear();
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("Application Usage"))));
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("System Usage"))));
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("Memory Monitor"))));
	childs.append(new QTreeWidgetItem(mem, QStringList(QString("Memory Protection"))));
	mem->addChildren(childs);
	ui.treeWidget->addTopLevelItem(mem);
	/* add the fourth top level node with children filled */
	flow = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Network Flow")));
	childs.clear();
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Real Time"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("History Trend"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Flow Rank"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Netflow Filter"))));
	childs.append(new QTreeWidgetItem(flow, QStringList(QString("Ports Status"))));
	flow->addChildren(childs);
	ui.treeWidget->addTopLevelItem(flow);
	/* add the fiveth top level node with children filled */
	browser = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Internet Explorer")));
	childs.clear();
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Browser Cache"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("IE Plugins"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Cookies"))));
	childs.append(new QTreeWidgetItem(browser, QStringList(QString("Monitor Settings"))));
	browser->addChildren(childs);
	ui.treeWidget->addTopLevelItem(browser);
	/* add the sixth top level node with children filled */
	registers = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Windows Register")));
	childs.clear();
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Register Details"))));
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Settings"))));
	childs.append(new QTreeWidgetItem(registers, QStringList(QString("Monitor Settings"))));
	registers->addChildren(childs);
	ui.treeWidget->addTopLevelItem(registers);
	/* add the seventh top level node with children filled */
	stat = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Security Center")));
	childs.clear();
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("Assessment"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("System Info"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("Loaded Libraries"))));
	childs.append(new QTreeWidgetItem(stat, QStringList(QString("About"))));
	stat->addChildren(childs);
	ui.treeWidget->addTopLevelItem(stat);
	/* set icons for every child tree widgets item */
	QTreeWidgetItemIterator iterator(ui.treeWidget, QTreeWidgetItemIterator::NoChildren);
	while (*iterator)
	{
		(*iterator)->setIcon(0, QIcon(":images/23.ico"));
		++iterator;
	}
	/* expand all top level items after created the window */
	ui.treeWidget->expandAll();

}

void TrojanAssessment::initStackedWidget()
{
	//add page widgets to StackedWidgets
	ui.stackedWidget->addWidget(fmp);
	ui.stackedWidget->addWidget(iep);
	ui.stackedWidget->addWidget(mp);
	ui.stackedWidget->addWidget(np);
	ui.stackedWidget->addWidget(pp);
	ui.stackedWidget->addWidget(rp);
	ui.stackedWidget->addWidget(scp);
	// set File Monitoring as the default page.
	ui.stackedWidget->setCurrentWidget(fmp);

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
		QTreeWidgetItem* ptr = cur->parent();   // to determine which kind of page user clicked.
		if (!ptr)  //it is a top level item
		{
			str = cur->text(0);
			if (str == "File Monitors")
			{
				ui.stackedWidget->setCurrentWidget(fmp);	
			}
			else if (str == "Process Center")
			{
				ui.stackedWidget->setCurrentWidget(pp);	
			}
			else if (str == "System Memory")
			{
				ui.stackedWidget->setCurrentWidget(mp);	
			}
			else if (str == "Network Flow")
			{
				ui.stackedWidget->setCurrentWidget(np);	
			}
			else if (str == "Internet Explorer")
			{
				ui.stackedWidget->setCurrentWidget(iep);	
			}
			else if (str == "Windows Register")
			{
				ui.stackedWidget->setCurrentWidget(rp);	
			}
			else  // Assessment page
			{
				ui.stackedWidget->setCurrentWidget(scp);	
			}
		}
		else  //children items
		{
			str = ptr->text(0);
			if (str == "File Monitors")
			{
				ui.stackedWidget->setCurrentWidget(fmp);	
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
				ui.stackedWidget->setCurrentWidget(pp);	
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
				ui.stackedWidget->setCurrentWidget(mp);	
				if (cur->text(0) == "Application Usage")
				{
					emit changeTabMP(1);
				}
				else if (cur->text(0) == "System Usage")
				{
					emit changeTabMP(2);
				}
				else if (cur->text(0) == "Memory Monitor")
				{
					emit changeTabMP(3);
				}
				else  // Memory protection
				{
					emit changeTabMP(4);
				}
			}
			else if (str == "Network Flow")
			{
				ui.stackedWidget->setCurrentWidget(np);	
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
				ui.stackedWidget->setCurrentWidget(iep);	
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
				ui.stackedWidget->setCurrentWidget(rp);	
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
				ui.stackedWidget->setCurrentWidget(scp);	
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
					on_action_About_triggered();
				}
			}
		}
	}
}

void TrojanAssessment::storeSettings()
{
	QString dt = QDateTime::currentDateTime().toString(QStringLiteral("yyyy-M-d h:m"));
	settings->beginGroup(QStringLiteral("UI"));
	settings->setValue(QStringLiteral("State"), saveState());
	settings->setValue(QStringLiteral("Geometry"), saveGeometry());
	settings->setValue(QStringLiteral("Logout"), dt);
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
	restoreState(settings->value(QStringLiteral("State")).toByteArray());
	restoreGeometry(settings->value(QStringLiteral("Geometry")).toByteArray());
	QString dt = QString("[Last On]: <b><font color=blue>%1</font></b>  [Last Off]:<b><font color=red>%2</font></b>").arg(
						settings->value("Login", "/").toString(),
						settings->value("Logout", "/").toString());
	lineEdit.setText(dt);
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
	if (fmp) { delete fmp; fmp = NULL;}
	if (iep) { delete iep; iep = NULL;}
	if (mp) { delete mp; mp = NULL;}
	if (np) { delete np; np = NULL;}
	if (pp) { delete pp; pp = NULL;}
	if (rp) { delete rp; rp = NULL;}
	if (scp) { delete scp; scp = NULL;}

	if (file) { delete file; file = NULL;}
	if (process) { delete process; process = NULL; }
	if (mem) { delete mem; mem = NULL; }
	if (flow) { delete flow; flow = NULL; }
	if (browser) { delete browser; browser = NULL; }
	if (registers) { delete registers; registers = NULL; }
	if (stat) { delete stat; stat = NULL; }
	if (settings) { delete settings; settings = NULL; }
}

void TrojanAssessment::on_action_Exit_triggered()
{
	close();
}

void TrojanAssessment::on_actionAbout_Qt_triggered()
{
	qApp->aboutQt();
}

void TrojanAssessment::on_action_Local_Help_triggered()
{
	QMessageBox::information(this, "Help", "comming soon...");
}

void TrojanAssessment::on_actionExport_triggered()
{
	QMessageBox::information(this, "Help", "Output a pdf.");
}

void TrojanAssessment::on_actionBrowser_triggered()
{
	ui.stackedWidget->setCurrentWidget(iep);
}

void TrojanAssessment::on_actionPlugins_triggered()
{
	ui.stackedWidget->setCurrentWidget(iep);
}

void TrojanAssessment::on_actionFlow_Rank_triggered()
{
	ui.stackedWidget->setCurrentWidget(np);
}

void TrojanAssessment::on_actionFile_Monitor_triggered()
{
	ui.stackedWidget->setCurrentWidget(fmp);
}

void TrojanAssessment::on_action_About_triggered()
{
	About ab(this);
	// To prompt a modal dialog, we call exec() method.
	// To prompt a modeless dialog, we should call show() method.
	ab.exec();  
}