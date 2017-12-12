#ifndef SECURITYCENTERPAGE_H
#define SECURITYCENTERPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QAbstractButton>
#include <QMessageBox>
#include <QComboBox>
#include <QTableView>
#include <QHeaderView>
#include <QTimer>
#include <QStandardItemModel>

#include "../../base/BusinessLayer/BasicInformation.h"
#include "../../base/CustomControl/nofocusdelegate.h"
#include "../../base/CustomControl/customitemmodel.h"
#include <tlhelp32.h> 

class AssessmentTab;
class SysInfoTab;
class LoadedLibTab;
class ManoMeter;
class RealtimeChart;

class SecurityCenterPage : public QTabWidget
{
	Q_OBJECT

public:
	SecurityCenterPage(QWidget *parent = 0);
	~SecurityCenterPage(){}
private slots:
	void onChangeTab(int index);

private:
	SecurityCenterPage(const SecurityCenterPage& page);
	SecurityCenterPage& operator=(const SecurityCenterPage& page) = delete;

private:
	AssessmentTab* m_assessmentTab;
	SysInfoTab* m_sysinfoTab;
	LoadedLibTab* m_loadedLibsTab;
};

//////////////////////////////////////////////////////////////////////////
//
class AssessmentTab : public QWidget
{
	Q_OBJECT

public:
	AssessmentTab(QWidget* parent = 0);
	~AssessmentTab(){}
private:
	AssessmentTab(const AssessmentTab& obj);
	AssessmentTab& operator=(const AssessmentTab& obj);

private slots:
	void onUpdateTimer();
private:
	ManoMeter* m_cpu;
	QVBoxLayout* m_layout1;
	QLabel* m_cpu_label;
	ManoMeter* m_disk;
	QVBoxLayout* m_layout2;
	QLabel* m_disk_label;
	ManoMeter* m_mem;
	QVBoxLayout* m_layout3;
	QLabel* m_mem_label;
	RealtimeChart* m_chart;
	QHBoxLayout* m_bottomLayout;
	QVBoxLayout* m_mainLayout;

	QTimer* m_timer;
};

//////////////////////////////////////////////////////////////////////////
//
class SysInfoTab : public QWidget
{
	Q_OBJECT

public:
	SysInfoTab(QWidget* parent = 0);
	~SysInfoTab(){}

private:
	SysInfoTab(const SysInfoTab& obj);
	SysInfoTab& operator=(const SysInfoTab& obj);
private:
	QGroupBox* m_softwareBox;
	QGroupBox* m_hardwareBox;
	QFormLayout* m_slayout;  // for software info
	QFormLayout* m_hlayout;  // for hardware info
	QVBoxLayout* m_vlayout;  // the main layout for the tab

	QLabel* m_boottime;
	QLineEdit* m_cpu;
	QLabel* m_hostname;
	QComboBox* m_ip;
	QComboBox* m_mac;
	QLabel* m_memTotalAvail;
	QComboBox* m_ncard;
	QLineEdit* m_osinfo;
	QComboBox* m_volumeinfo;
	QPushButton* m_btn;
};

//////////////////////////////////////////////////////////////////////////
//
class LoadedLibTab : public QWidget
{
	Q_OBJECT

public:
	LoadedLibTab(QWidget* parent = 0);
	~LoadedLibTab(){}
private:
	LoadedLibTab(const LoadedLibTab& obj);
	LoadedLibTab& operator=(const LoadedLibTab& obj);

	void doLoadlibs();
private:
	QTableView* m_libtable;
	CustomItemModel* m_model;
	QVBoxLayout* m_layout;
};

#endif // SECURITYCENTERPAGE_H
