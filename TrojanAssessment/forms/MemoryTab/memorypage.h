#ifndef MEMORYPAGE_H
#define MEMORYPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QFormLayout>

QT_BEGIN_NAMESPACE
class QTableView;
class QDialogButtonBox;
class QGroupBox;
QT_END_NAMESPACE

class SysUsageTab;
class MemMonitorTab;
class MemProtectionTab;

class MemoryPage : public QTabWidget
{
	Q_OBJECT

public:
	MemoryPage(QWidget *parent = 0);
	~MemoryPage(){}
private slots:
	void onChangeTab(int index);

private:
	MemoryPage& operator=(const MemoryPage& obj);
	MemoryPage(const MemoryPage& obj);
private:
	SysUsageTab* m_sysUsage;   // 操作系统所占用内存使用情况
	MemMonitorTab* m_memMonitor;  // 内存分配状况的动态图和统计图
	MemProtectionTab* m_memProtect;  // 内存保护，高级内容
};

//////////////////////////////////////////////////////////////////////////
// Definition of system memory usage class.
class SysUsageTab : public QWidget
{
	Q_OBJECT

public:
	SysUsageTab(QWidget* parent = 0);
	~SysUsageTab();
private:
	SysUsageTab(const SysUsageTab& obj);
	SysUsageTab& operator=(const SysUsageTab& obj);
private:
	QVBoxLayout* m_mainLayout;
	QTableView* m_procList;
	QStandardItemModel* m_procModel;

	QTableWidget* m_table;
};

//////////////////////////////////////////////////////////////////////////
// Definition of application memory usage class.
class MemMonitorTab : public QWidget
{
	Q_OBJECT

public:
	MemMonitorTab(QWidget* parent = 0);
	~MemMonitorTab();
private:
	MemMonitorTab(const MemMonitorTab& obj);
	MemMonitorTab& operator=(const MemMonitorTab& obj);

private:
	QFormLayout* m_formLayout;
	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_bottomLayout;
};

//////////////////////////////////////////////////////////////////////////
// Definition of memory monitoring class.
class MemProtectionTab : public QWidget
{
	Q_OBJECT

public:
	MemProtectionTab(QWidget* parent = 0);
	~MemProtectionTab();
private:
	MemProtectionTab(const MemProtectionTab& obj);
	MemProtectionTab& operator=(const MemProtectionTab& obj);
private:
	
};

#endif // MEMORYPAGE_H
