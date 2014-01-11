#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QTabWidget>

class RegDetailsTab;
class RegSettingsTab;
class RegMonitorTab;

class RegisterPage : public QTabWidget
{
	Q_OBJECT

public:
	RegisterPage(QWidget *parent = 0);
	~RegisterPage();
private slots:
	void onChangeTab(int index);
private:
	RegisterPage(const RegisterPage& obj);
	RegisterPage& operator=(const RegisterPage& obj);

private:
	RegDetailsTab* m_regDetailTab;
	RegSettingsTab* m_regSettingTab;
	RegMonitorTab* m_regMonitorTab;
};

//////////////////////////////////////////////////////////////////////////
//
class RegDetailsTab : public QWidget
{
	Q_OBJECT

public:
	RegDetailsTab(QWidget* parent = 0);
	~RegDetailsTab();
private:
	RegDetailsTab(const RegDetailsTab& obj);
	RegDetailsTab& operator=(const RegDetailsTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class RegSettingsTab : public QWidget
{
	Q_OBJECT

public:
	RegSettingsTab(QWidget* parent = 0);
	~RegSettingsTab();
private:
	RegSettingsTab(const RegSettingsTab& obj);
	RegSettingsTab& operator=(const RegSettingsTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
//
class RegMonitorTab : public QWidget
{
	Q_OBJECT

public:
	RegMonitorTab(QWidget* parent = 0);
	~RegMonitorTab();
private:
	RegMonitorTab(const RegMonitorTab& obj);
	RegMonitorTab& operator=(const RegMonitorTab& obj);
private:

};

#endif // REGISTERPAGE_H
