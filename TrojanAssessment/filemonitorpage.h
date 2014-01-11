#ifndef FILEMONITORPAGE_H
#define FILEMONITORPAGE_H

#include <QWidget>
#include <QTabWidget>

class DataFileTab;
class ExecFileTab;
class FileBrowserTab;

class FileMonitorPage : public QTabWidget
{
	Q_OBJECT

public:
	FileMonitorPage(QWidget *parent = 0);
	~FileMonitorPage();
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
	~DataFileTab();

private:
	DataFileTab(const DataFileTab& obj);
	DataFileTab& operator=(const DataFileTab& obj);
private:
	
};

//////////////////////////////////////////////////////////////////////////
// Tab for executable file monitoring
class ExecFileTab : public QWidget
{
	Q_OBJECT

public:
	ExecFileTab(QWidget* parent = 0);
	~ExecFileTab();

private:
	ExecFileTab(const ExecFileTab& obj);
	ExecFileTab& operator=(const ExecFileTab& obj);
private:
	
};

//////////////////////////////////////////////////////////////////////////
// Tab for file browser file monitoring
class FileBrowserTab : public QWidget
{
	Q_OBJECT

public:
	FileBrowserTab(QWidget* parent = 0);
	~FileBrowserTab();

private:
	FileBrowserTab(const FileBrowserTab& obj);
	FileBrowserTab& operator=(const FileBrowserTab& obj);
private:
	
};

#endif // FILEMONITORPAGE_H
