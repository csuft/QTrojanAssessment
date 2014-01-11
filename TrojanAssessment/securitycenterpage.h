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
#include <QPushButton>
#include <QFormLayout>
#include <QAbstractButton>
#include <QMessageBox>
#include <QComboBox>
#include <QSortFilterProxyModel>

#include "BasicInformation.h"

class AssessmentTab;
class SysInfoTab;
class LoadedLibTab;

class SecurityCenterPage : public QTabWidget
{
	Q_OBJECT

public:
	SecurityCenterPage(QWidget *parent = 0);
	~SecurityCenterPage();
private slots:
	void onChangeTab(int index);

private:
	SecurityCenterPage(const SecurityCenterPage& page);
	SecurityCenterPage& operator=(const SecurityCenterPage& page);

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
	~AssessmentTab();
private:
	AssessmentTab(const AssessmentTab& obj);
	AssessmentTab& operator=(const AssessmentTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class SysInfoTab : public QWidget
{
	Q_OBJECT

public:
	SysInfoTab(QWidget* parent = 0);
	~SysInfoTab();

private slots:
	void onCopytoClipboard(QAbstractButton* btn);

private:
	SysInfoTab(const SysInfoTab& obj);
	SysInfoTab& operator=(const SysInfoTab& obj);
private:
	QGroupBox* m_softwareBox;
	QGroupBox* m_hardwareBox;
	QDialogButtonBox* m_clipboard;
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
	~LoadedLibTab();
private:
	LoadedLibTab(const LoadedLibTab& obj);
	LoadedLibTab& operator=(const LoadedLibTab& obj);
private:
	QListView* m_dllList;
	QDialogButtonBox* m_export;
	QSortFilterProxyModel* m_filterModel;
	QLineEdit* m_filterExp;
	QVBoxLayout* m_layout;
};

#endif // SECURITYCENTERPAGE_H
