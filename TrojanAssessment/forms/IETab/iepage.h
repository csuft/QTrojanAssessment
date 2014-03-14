#ifndef IEPAGE_H
#define IEPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QComboBox>
#include <QRegExp>
#include <QToolTip>
#include <QMessageBox>
#include <QSysInfo>    // for OS version
#include <fstream>

#include "../../base/BusinessLayer/BasicInformation.h"
#include "../../base/CustomControl/customitemmodel.h"
#include "../../base/CustomControl/nofocusdelegate.h"
#include "../CacheTab/cacheentrydetail.h"

class BrowserCacheTab;
class PluginsTab;
class BrowserCookiesTab;
class IESettingsTab;
using std::ifstream;

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

	void initialModel();
private slots:
	void onFilterExpChanged(const QString& exp);
	void onFilterColChanged(int index);
	void onRefreshClicked();
	void onCleanClicked();
	void onViewPropertyClicked();
private:
	QLineEdit* m_filterExp;
	QComboBox* m_filterCol;
	QPushButton* m_refresh;
	QPushButton* m_clear;
	QPushButton* m_view;
	QTableView* m_viewList;
	CustomItemModel* m_srcModel;
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
// Windows 7/Vista: C:\Users\zzk\AppData\Roaming\Microsoft\Windows\Cookies\index.dat
//                  C:\Users\zzk\AppData\Roaming\Microsoft\Windows\Cookies\Low\index.dat
//                  C:\Users\zzk\AppData\Local\Microsoft\Windows\Temporary Internet Files\Content.IE5\index.dat
//                  C:\Users\zzk\AppData\Local\Microsoft\Windows\Temporary Internet Files\Low\Content.IE5index.dat
// Windows XP/2000: C:\Documents and Settings\<username>\Cookies\index.dat
//                  C:\Documents and Settings\<username>\Local Settings\Temporary Internet Files\Content.IE5\index.dat
class BrowserCookiesTab : public QWidget
{
	Q_OBJECT

public:
	BrowserCookiesTab(QWidget* parent = 0);
	~BrowserCookiesTab();
private:
	BrowserCookiesTab(const BrowserCookiesTab& obj);
	BrowserCookiesTab& operator=(const BrowserCookiesTab& obj);

	void createHeader();
	void createCookieModel();
	void resolveCookies(const char* fileName);
	void createDetailsView(const vector<CookieRecord>& vc);
	void transformTime(const char* low, const char* high, char* dst);
	const char* setCreator(const char* flag);
private slots:
	void onTableViewClicked(const QModelIndex& index);
	void onFilterExpChanged(const QString& text);
	void showToolTips(const QModelIndex& index);
private:
	QLineEdit* m_filterExp;
	QPushButton* m_openWithNotepad;
	QPushButton* m_openWithWordpad;
	QTableView* m_cookiesList;
	QTableWidget* m_detailsList;
	QSortFilterProxyModel* m_proxyModel;
	CustomItemModel* m_model;

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
