#ifndef PROCESSPAGE_H
#define PROCESSPAGE_H

#include <QWidget>
#include <QTabWidget>

class RuntimeMonitorTab;
class WinServicesTab;
class ProcessListTab;
class SoftwareInstalledTab;

class ProcessPage : public QTabWidget
{
	Q_OBJECT
		
public:
	ProcessPage(QWidget *parent = 0);
	~ProcessPage();

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
	~RuntimeMonitorTab();
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
	~WinServicesTab();
private:
	WinServicesTab(const WinServicesTab& obj);
	WinServicesTab& operator=(const WinServicesTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class ProcessListTab : public QWidget
{
	Q_OBJECT

public:
	ProcessListTab(QWidget* parent = 0);
	~ProcessListTab();
private:
	ProcessListTab(const ProcessListTab& obj);
	ProcessListTab& operator=(const ProcessListTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class SoftwareInstalledTab : public QWidget
{
	Q_OBJECT

public:
	SoftwareInstalledTab(QWidget* parent = 0);
	~SoftwareInstalledTab();
private:
	SoftwareInstalledTab(const SoftwareInstalledTab& obj);
	SoftwareInstalledTab& operator=(const SoftwareInstalledTab& obj);
private:

};

#endif // PROCESSPAGE_H
