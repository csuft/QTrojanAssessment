#ifndef PROCESSPAGE_H
#define PROCESSPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QTabWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QSortFilterProxyModel>
#include <QAbstractItemView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCompleter>
#include <QFileIconProvider>

#include "../../base/CustomControl/customitemmodel.h"
#include "../../base/CustomControl/nofocusdelegate.h"
#include "../../base/BusinessLayer/BasicInformation.h"

#include <vector>
using std::vector;

class RuntimeMonitorTab;
class WinServicesTab;
class ProcessListTab;
class SoftwareInstalledTab;

class ProcessPage : public QTabWidget
{
	Q_OBJECT
		
public:
	ProcessPage(QWidget *parent = 0);
	~ProcessPage(){}

private slots:
	void onChangeTab(int index);
private:
	ProcessPage(const ProcessPage& obj);
	ProcessPage& operator=(const ProcessPage& obj);
private:
	RuntimeMonitorTab* m_runtimeTab;
	WinServicesTab* m_serviceTab;
	ProcessListTab* m_processTab;
	SoftwareInstalledTab* m_softTab;
};

//////////////////////////////////////////////////////////////////////////
//
class RuntimeMonitorTab : public QWidget
{
	Q_OBJECT

public:
	RuntimeMonitorTab(QWidget* parent = 0);
	~RuntimeMonitorTab(){}
private:
	RuntimeMonitorTab(const RuntimeMonitorTab& obj);
	RuntimeMonitorTab& operator=(const RuntimeMonitorTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class WinServicesTab : public QWidget
{
	Q_OBJECT

public:
	WinServicesTab(QWidget* parent = 0);
	~WinServicesTab(){}
private:
	WinServicesTab(const WinServicesTab& obj);
	WinServicesTab& operator=(const WinServicesTab& obj);
private:
	QTableView* m_view;
	CustomItemModel* m_srcModel;
	QVBoxLayout* m_layout;
};

//////////////////////////////////////////////////////////////////////////
//
class ProcessListTab : public QWidget
{
	Q_OBJECT

public:
	ProcessListTab(QWidget* parent = 0);
	~ProcessListTab(){ delete m_helper; }
private:
	ProcessListTab(const ProcessListTab& obj);
	ProcessListTab& operator=(const ProcessListTab& obj);

private:
	void initProcList();
	void createProcHeader();
	void loadProcessList();

private:
	QTableView* m_view;
	CustomItemModel* m_srcModel;
	QSortFilterProxyModel* m_proxyModel;
	QCompleter* m_completer;
	QLineEdit* m_filterExp;
	QPushButton* m_refresh;

	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_topLayout;

	RetrieveHelper* m_helper;
};

//////////////////////////////////////////////////////////////////////////
//
class SoftwareInstalledTab : public QWidget
{
	Q_OBJECT

public:
	SoftwareInstalledTab(QWidget* parent = 0);
	~SoftwareInstalledTab(){ delete m_helper; }
private:
	SoftwareInstalledTab(const SoftwareInstalledTab& obj);
	SoftwareInstalledTab& operator=(const SoftwareInstalledTab& obj);

private:
	void initAppList();
	void createAppListHeader();
	void loadApplist();

private:
	QTableView* m_view;
	CustomItemModel* m_model;
	QVBoxLayout* m_mainLayout;

	RetrieveHelper* m_helper;
};

#endif // PROCESSPAGE_H
