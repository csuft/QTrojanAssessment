#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QLabel>
#include <QVBoxLayout>

#include "../../base/CustomControl/customitemmodel.h"

class RealTimeFlowTab;
class AppRankTab;
class PortsStatusTab;

class NetworkPage : public QTabWidget
{
	Q_OBJECT

public:
	NetworkPage(QWidget *parent = 0);
	~NetworkPage(){}
private slots:
	void onChangeTab(int index);

private:
	NetworkPage(const NetworkPage& obj);
	NetworkPage& operator=(const NetworkPage& obj);
private:
	QTabWidget* m_tabWidget;

	RealTimeFlowTab* m_realtimeTab;
	AppRankTab* m_rankTab;
	PortsStatusTab* m_portsTab;
};

//////////////////////////////////////////////////////////////////////////
// Definition of real time flow class.
class RealTimeFlowTab : public QWidget
{
	Q_OBJECT

public:
	RealTimeFlowTab(QWidget* parent = 0);
	~RealTimeFlowTab(){}
private:
	RealTimeFlowTab(const RealTimeFlowTab& obj);
	RealTimeFlowTab& operator=(const RealTimeFlowTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
// Definition of real time flow class.
class AppRankTab : public QWidget
{
	Q_OBJECT

public:
	AppRankTab(QWidget* parent = 0);
	~AppRankTab(){}
private:
	AppRankTab(const AppRankTab& obj);
	AppRankTab& operator=(const AppRankTab& obj);
private:

};

//////////////////////////////////////////////////////////////////////////
// Definition of real time flow class.
class PortsStatusTab : public QWidget
{
	Q_OBJECT

public:
	PortsStatusTab(QWidget* parent = 0);
	~PortsStatusTab(){}
private:
	PortsStatusTab(const PortsStatusTab& obj);
	PortsStatusTab& operator=(const PortsStatusTab& obj);
private:
	QTableView* m_view;
	CustomItemModel* m_model;
	QLabel* m_infoLabel;

	QVBoxLayout* m_layout;
};


#endif // NETWORKPAGE_H
