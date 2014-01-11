#ifndef TROJANASSESSMENT_H
#define TROJANASSESSMENT_H

#include <QtWidgets/QMainWindow>
#include "ui_trojanassessment.h"

#include <QMessageBox>
#include <QListView>
#include <QSplitter>
#include <QTreeView>
#include <QTextEdit>
#include <QToolBar>
#include <QList>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QtDebug>
#include <QSettings>
#include <QDateTime>
#include <QLabel>
#include <QCloseEvent>
#include <QStackedWidget>
#include <QSplitterHandle>

#include "filemonitorpage.h"
#include "iepage.h"
#include "memorypage.h"
#include "networkpage.h"
#include "processpage.h"
#include "registerpage.h"
#include "securitycenterpage.h"
#include "about.h"

class TrojanAssessment : public QMainWindow
{
	Q_OBJECT

public:
	explicit TrojanAssessment(QWidget *parent = 0);
	~TrojanAssessment();
	void closeEvent(QCloseEvent* );
private:
	void initTreeWidget();
	void initStackedWidget();
	void makeConnections();
	void storeSettings();
	void restoreSettings();

signals:
	void changeTabFMP(int index);   // it is not necessary to implement a signal function
	void changeTabPP(int index);
	void changeTabMP(int index);
	void changeTabNP(int index);
	void changeTabRP(int index);
	void changeTabIEP(int index);
	void changeTabSCP(int index);
private slots:
	void changePage(QTreeWidgetItem* cur, QTreeWidgetItem* prev);
	void on_action_Exit_triggered();
	void on_actionAbout_Qt_triggered();
	void on_action_Local_Help_triggered();
	void on_actionExport_triggered();
	void on_actionBrowser_triggered();
	void on_actionPlugins_triggered();
	void on_actionFlow_Rank_triggered();
	void on_actionFile_Monitor_triggered();
	void on_action_About_triggered();

private:
	Ui::TrojanAssessmentClass ui;

	QToolBar* miscbar;
	QTreeWidgetItem* file;  // file monitoring top node
	QTreeWidgetItem* process;  // process monitoring top node
	QTreeWidgetItem* flow;  // flow monitoring top node
	QTreeWidgetItem* browser;  // browser plugins etc.
	QTreeWidgetItem* registers; //windows register.
	QTreeWidgetItem* mem;  //memory monitoring
	QTreeWidgetItem* stat;  //statistics of system
	QLabel lineEdit;
	QLabel normalStatus;
	QDateTime login_dt;
	QSettings* settings;  //store and restore information of widgets

	//pages to show
	FileMonitorPage* fmp;
	IEPage* iep;
	MemoryPage* mp;
	NetworkPage* np;
	ProcessPage* pp;
	RegisterPage* rp;
	SecurityCenterPage* scp;
};

#endif // TROJANASSESSMENT_H
