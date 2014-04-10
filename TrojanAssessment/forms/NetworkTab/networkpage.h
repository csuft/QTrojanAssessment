#ifndef NETWORKPAGE_H
#define NETWORKPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>

#include "base/CustomControl/customitemmodel.h"
#include "3rdParty/ChartDirector/realtimechart.h"

class RealTimeFlowTab;
class AppRankTab;
class PortsStatusTab;
class QGroupBox;
class QFormLayout;

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

protected slots:
	void onTimeout();

private:
	// flow chart
	QTimer* m_global_timer;
	RealtimeChart* m_chart;
	QHBoxLayout* m_bottomLayout;
	QVBoxLayout* m_mainLayout;
	QGroupBox* m_leftGroup;
	QGroupBox* m_rightGroup;
	QFormLayout* m_leftForm;
	QFormLayout* m_rightForm;

	QLabel* m_totalFlow;
	QLabel* m_totalFlow_value;
	QLabel* m_business;
	QLabel* m_business_value;
	QLabel* m_non_business;
	QLabel* m_non_business_value;
	QLabel* m_average;
	QLabel* m_average_value;

	QLabel* m_tcp;
	QLabel* m_tcp_value;
	QLabel* m_icmp;
	QLabel* m_icmp_value;
	QLabel* m_udp;
	QLabel* m_udp_value;
	QLabel* m_packets_average;
	QLabel* m_packets_average_value;
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
	// read operations count, write operations count, other I/O operations count, 
	// number of bytes read, number of bytes write, number of bytes transfered by other I/O operations.
	// typedef struct _IO_COUNTERS {};
	QTableView* m_view;
	CustomItemModel* m_model;
	QHBoxLayout* m_layout;
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
