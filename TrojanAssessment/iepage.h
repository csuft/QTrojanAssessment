#ifndef IEPAGE_H
#define IEPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QDialogButtonBox>
#include <QGroupBox>

#include "BasicInformation.h"

class BrowserCacheTab;
class PluginsTab;
class BrowserCookiesTab;
class IESettingsTab;

class IEPage : public QTabWidget
{
	Q_OBJECT

public:
	IEPage(QWidget *parent = 0);
	~IEPage();
private slots:
	void onChangeTab(int index);

private:
	IEPage& operator=(const IEPage& obj);
	IEPage(const IEPage& obj);

private:
	BrowserCacheTab* m_cacheTab;
	PluginsTab* m_pluginsTab;
	BrowserCookiesTab* m_cookieTab;
	IESettingsTab* m_settingsTab;
};
//////////////////////////////////////////////////////////////////////////
//
class BrowserCacheTab : public QWidget
{
	Q_OBJECT

public:
	BrowserCacheTab(QWidget* parent = 0);
	~BrowserCacheTab();
private:
	BrowserCacheTab(const BrowserCacheTab& obj);
	BrowserCacheTab& operator=(const BrowserCacheTab& obj);
private:
	QLineEdit* m_filterExp;
	QPushButton* m_find;
	QPushButton* m_delete;
	QPushButton* m_clear;
	QPushButton* m_view;
	QTableView* m_viewList;
	QSortFilterProxyModel* m_proxyModel;

	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_topLayout;
};
//////////////////////////////////////////////////////////////////////////
// Definition of Browser plugins class.
class PluginsTab : public QWidget
{
	Q_OBJECT

public:
	PluginsTab(QWidget* parent = 0);
	~PluginsTab();
private:
	PluginsTab(const PluginsTab& obj);
	PluginsTab& operator=(const PluginsTab& obj);
private:
	QLineEdit* m_filterExp;
	QTableView* m_viewList;
	QSortFilterProxyModel* m_model;
	QVBoxLayout* m_layout;
};
//////////////////////////////////////////////////////////////////////////
// Definition of Internet Explorer Browser cookies class.
class BrowserCookiesTab : public QWidget
{
	Q_OBJECT

public:
	BrowserCookiesTab(QWidget* parent = 0);
	~BrowserCookiesTab();
private:
	BrowserCookiesTab(const BrowserCookiesTab& obj);
	BrowserCookiesTab& operator=(const BrowserCookiesTab& obj);
private:
	QLineEdit* m_filterExp;
	QPushButton* m_openWithNotepad;
	QPushButton* m_openWithWordpad;
	QPushButton* m_viewProperties;
	QTableView* m_cookiesList;
	QTableView* m_detailsList;
	QDialogButtonBox* m_dlgBtnBox;
	QSortFilterProxyModel* m_model;

	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_topLayout;

};

//////////////////////////////////////////////////////////////////////////
// Definition of browser monitoring settings.
class IESettingsTab : public QWidget
{
	Q_OBJECT

public:
	IESettingsTab(QWidget* parent = 0);
	~IESettingsTab();
private:
	IESettingsTab(const IESettingsTab& obj);
	IESettingsTab& operator=(const IESettingsTab& obj);
private:
	QGroupBox* m_IEsettings;
	QDialogButtonBox* m_dlgBtnBox;
	QPushButton* m_apply;
	QVBoxLayout* m_layout;
};

#endif // IEPAGE_H
