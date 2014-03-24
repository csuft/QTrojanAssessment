#ifndef FILEMONITORPAGE_H
#define FILEMONITORPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QTableView>
#include <QTreeView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "base/CustomControl/customitemmodel.h"

class DataFileTab;
class ExecFileTab;
class FileBrowserTab;

class FileMonitorPage : public QTabWidget
{
	Q_OBJECT

public:
	FileMonitorPage(QWidget *parent = 0);
	~FileMonitorPage(){}
private slots:
	void onChangeTab(int index);
private:
	FileMonitorPage& operator=(const FileMonitorPage& obj);
	FileMonitorPage(const FileMonitorPage& obj);
	
private:
	//QTabWidget* m_tabWidget;

	DataFileTab* m_dataFileTab;
	ExecFileTab* m_execFileTab;
	FileBrowserTab* m_browserTab;
};
//////////////////////////////////////////////////////////////////////////
//Tab for data file monitoring
class DataFileTab : public QWidget
{
	Q_OBJECT

public:
	DataFileTab(QWidget* parent = 0);
	~DataFileTab(){}

private:
	DataFileTab(const DataFileTab& obj);
	DataFileTab& operator=(const DataFileTab& obj);
private:
	CustomItemModel* m_model;
	QSortFilterProxyModel* m_proxy;
	QTableView* m_view;
	
	QHBoxLayout* m_statusLayout;
	QLabel* m_status;
	QLineEdit* m_status_info;

	QHBoxLayout* m_topLayout;
	QLineEdit* m_filter;
	QPushButton* m_clearBtn;
	QPushButton* m_exportBtn;

	QHBoxLayout* m_bottomLayout;
	QPushButton* m_chooseDir;
	QPushButton* m_startBtn;
	QPushButton* m_stopBtn;

	QVBoxLayout* m_mainLayout;
};

//////////////////////////////////////////////////////////////////////////
// Tab for executable file monitoring
class ExecFileTab : public QWidget
{
	Q_OBJECT

public:
	ExecFileTab(QWidget* parent = 0);
	~ExecFileTab(){}

private:
	ExecFileTab(const ExecFileTab& obj);
	ExecFileTab& operator=(const ExecFileTab& obj);
private:
	QTableView* m_view;
	QStandardItemModel* m_model;

	QHBoxLayout* m_topLayout;
	QLineEdit* m_filter;
	QPushButton* m_clearBtn;
	QPushButton* m_startBtn;
	QPushButton* m_stopBtn;

	QHBoxLayout* m_mainLayout;
};

//////////////////////////////////////////////////////////////////////////
// Tab for file browser file monitoring
class FileBrowserTab : public QWidget
{
	Q_OBJECT

public:
	FileBrowserTab(QWidget* parent = 0);
	~FileBrowserTab(){}

private:
	FileBrowserTab(const FileBrowserTab& obj);
	FileBrowserTab& operator=(const FileBrowserTab& obj);
private:
	QTreeView* m_view;
	QFileSystemModel* m_model;
	QVBoxLayout* m_layout;
};

#endif // FILEMONITORPAGE_H
