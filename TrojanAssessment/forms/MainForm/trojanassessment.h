#ifndef TROJANASSESSMENT_H
#define TROJANASSESSMENT_H

#include <QSplitter>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QSettings>
#include <QDateTime>
#include <QLabel>
#include <QCloseEvent>
#include <QStackedWidget>
#include <QSplitterHandle>
#include <QPainter>

#include "../FileMonitorTab/filemonitorpage.h"
#include "../IETab/iepage.h"
#include "../MemoryTab/memorypage.h"
#include "../NetworkTab/networkpage.h"
#include "../ProcessTab/processpage.h"
#include "../RegistryTab/registerpage.h"
#include "../AssessmentTab/securitycenterpage.h"
#include "../AboutDialog/about.h"
#include "../base/CustomControl/shadowwindow.h"
#include "../base/CustomControl/systemtray.h"
#include "../TitleWidget/titlewidget.h"

class TrojanAssessment : public ShadowWindow
{
	Q_OBJECT

public:
	explicit TrojanAssessment(QWidget *parent = 0);
	~TrojanAssessment();
	void closeEvent(QCloseEvent* );

private:
	TrojanAssessment& operator=(const TrojanAssessment& obj);
	TrojanAssessment(const TrojanAssessment& obj);

	void initTreeWidget();
	void initStackedWidget();
	void storeSettings();
	void restoreSettings();
protected:
	void paintEvent(QPaintEvent* event);

signals:
	// it is not necessary to implement a signal function
	void changeTabFMP(int index);   
	void changeTabPP(int index);
	void changeTabMP(int index);
	void changeTabNP(int index);
	void changeTabRP(int index);
	void changeTabIEP(int index);
	void changeTabSCP(int index);
	// Convert signal arguments
	void toolButtonChangePage(QTreeWidgetItem* cur, QTreeWidgetItem* prev);

private slots:
	void changePage(QTreeWidgetItem* cur, QTreeWidgetItem* prev);
	void onToolBtnClicked(int index);
	void onShowSettingsMenu();

private:
	QTreeWidgetItem* file;		    // file monitoring top node
	QTreeWidgetItem* process;		// process monitoring top node
	QTreeWidgetItem* flow;			// flow monitoring top node
	QTreeWidgetItem* browser;		// browser plugins etc.
	QTreeWidgetItem* registers;		// windows register.
	QTreeWidgetItem* mem;			// memory monitoring
	QTreeWidgetItem* stat;			// statistics of system
	SystemTray* m_systemTray;
	// small components
	QLabel* icon_label;
	QLabel* lastrun_label;
	QDateTime login_dt;
	QSettings* settings;			// store and restore information of widgets
	QVBoxLayout* m_mainLayout;		// window layout manager for the main widget
	QHBoxLayout* m_bottomLayout;	// layout manager for widgets in status bar

	// layouts
	QStackedWidget* stackedWidget;
	QTreeWidget* treeWidget;
	QSplitter* splitter;
	TitleWidget* titleWidget;

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
