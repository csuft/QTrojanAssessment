#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QIcon>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QEvent>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:
    explicit SystemTray(QWidget *parent = 0);
	~SystemTray(){}

private:
	SystemTray& operator=(const SystemTray& obj);
	SystemTray(const SystemTray& obj);

	void createTopWidget();
	void createBottomWidget();
	void createTrayMenu();

signals:
	void visitHomeBtnClicked();
	void updateBtnClicked();
	void aboutBtnClicked();
	void exitBtnClicked();
	void runOSBTriggered();
	void helpOnlineTriggered();
	void homePageTriggered();
	void notificationTriggered();
	void settingsTriggered();
	void restoreWindowTriggered();

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	QMenu* m_trayMenu;

	QWidget* m_topWidget;
	QWidgetAction* m_topWidgetAction;
	QLabel* m_topLabel;
	QLabel* m_homeBtn;

	QWidget* m_bottomWidget;
	QWidgetAction* m_bottomWidgetAction;
	QPushButton* m_updateBtn;
	QPushButton* m_aboutBtn;
	QPushButton* m_exitBtn;

	QAction* m_runOnSystemBoot;
	QAction* m_helpOnline;
	QAction* m_homePage;
	QAction* m_notification;
	QAction* m_settings;
	QAction* m_restoreWindow;
	
};

#endif // SYSTEMTRAY_H
