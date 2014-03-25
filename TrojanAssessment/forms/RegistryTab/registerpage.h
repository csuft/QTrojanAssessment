#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>

#include "base/CustomControl/customitemmodel.h"

class RegSettingsTab;
class RegMonitorTab;

class RegisterPage : public QTabWidget
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = 0);
	~RegisterPage(){}
private slots:
	void onChangeTab(int index);
private:
	RegisterPage(const RegisterPage& obj);
	RegisterPage& operator=(const RegisterPage& obj);

private:
	RegSettingsTab* m_regSettingTab;
	RegMonitorTab* m_regMonitorTab;
};

//////////////////////////////////////////////////////////////////////////
//
class RegSettingsTab : public QWidget
{
	Q_OBJECT

public:
	RegSettingsTab(QWidget* parent = 0);
	~RegSettingsTab(){}
private:
	RegSettingsTab(const RegSettingsTab& obj);
	RegSettingsTab& operator=(const RegSettingsTab& obj);
private:
	QGroupBox* m_group;
	QVBoxLayout* m_layout;
};

//////////////////////////////////////////////////////////////////////////
//
class RegMonitorTab : public QWidget
{
	Q_OBJECT

public:
	RegMonitorTab(QWidget* parent = 0);
	~RegMonitorTab(){}
private:
	RegMonitorTab(const RegMonitorTab& obj);
	RegMonitorTab& operator=(const RegMonitorTab& obj);

	void createHeaders();

private:
	CustomItemModel* m_model;
	QSortFilterProxyModel* m_proxy;
	QTableView* m_view;

	QHBoxLayout* m_centerLayout;
	QLineEdit* m_filter;
	QPushButton* m_clearBtn;
	QPushButton* m_exportBtn;
	
	QHBoxLayout* m_topLayout;
	QPushButton* m_registryRoot;
	QPushButton* m_startBtn;
	QPushButton* m_stopBtn;

	QVBoxLayout* m_mainLayout;
};

#endif // REGISTERPAGE_H
