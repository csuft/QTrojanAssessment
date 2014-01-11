#include "securitycenterpage.h"

SecurityCenterPage::SecurityCenterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_assessmentTab = new AssessmentTab;
	m_sysinfoTab = new SysInfoTab;
	m_loadedLibsTab = new LoadedLibTab;

	addTab(m_assessmentTab, QStringLiteral("Assessment Center"));
	addTab(m_sysinfoTab, QStringLiteral("System Info"));
	addTab(m_loadedLibsTab, QStringLiteral("Loaded Libraries"));
}

SecurityCenterPage::~SecurityCenterPage()
{
	if (m_assessmentTab) { delete m_assessmentTab; m_assessmentTab = NULL;}
	if (m_sysinfoTab) { delete m_sysinfoTab; m_sysinfoTab = NULL;}
	if (m_loadedLibsTab) { delete m_loadedLibsTab; m_loadedLibsTab = NULL;}
}

void SecurityCenterPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_sysinfoTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_loadedLibsTab);
	}
	else // Assessment
	{
		setCurrentWidget(m_assessmentTab);
	}
}

//////////////////////////////////////////////////////////////////////////
//
AssessmentTab::AssessmentTab(QWidget *parent)
	: QWidget(parent)
{

}

AssessmentTab::~AssessmentTab()
{

}


//////////////////////////////////////////////////////////////////////////
//
SysInfoTab::SysInfoTab(QWidget *parent)
	: QWidget(parent)
{
	BasicInformation info;
	vector<string>::const_iterator it;
	m_softwareBox = new QGroupBox(QStringLiteral("Software"), this);
	m_hardwareBox = new QGroupBox(QStringLiteral("Hardware"), this);
	m_slayout = new QFormLayout(this);
	m_vlayout = new QVBoxLayout(this);
	m_hlayout = new QFormLayout(this);
	// system boot time
	m_boottime = new QLabel(QString::fromStdString(info.getSystemBootTime()), this);
	m_slayout->addRow(QStringLiteral("Boot Time:"), m_boottime);
	// computer name
	m_hostname = new QLabel(QString::fromStdString(info.getHostName()), this);
	m_slayout->addRow(QStringLiteral("Host Name:"), m_hostname);
	// ip address
	m_ip = new QComboBox(this);
	vector<string> tmp = info.getIPAddress();
	for (it = tmp.cbegin(); it != tmp.cend(); ++it)
	{
		m_ip->addItem(QString::fromStdString(*it));
	}
	m_slayout->addRow(QStringLiteral("IP Address:"), m_ip);
	// mac address
	m_mac = new QComboBox(this);
	tmp = info.getMACAddress();
	for (it = tmp.cbegin(); it != tmp.cend(); ++it)
	{
		m_mac->addItem(QString::fromStdString(*it));
	}
	m_slayout->addRow(QStringLiteral("MAC address:"), m_mac);
	// operating system information
	m_osinfo = new QLineEdit(this);
	m_osinfo->setReadOnly(true);
	m_osinfo->setText(QString::fromStdString(info.getOSInformation()));
	m_slayout->addRow(QStringLiteral("OS Details:"), m_osinfo);
	m_softwareBox->setLayout(m_slayout);
	// network card information
	m_ncard = new QComboBox(this);
	tmp = info.getNetworkCard();
	for (it = tmp.cbegin(); it != tmp.cend(); ++it)
	{
		m_ncard->addItem(QString::fromLocal8Bit((*it).c_str()));  //convert to local character set
	}
	m_hlayout->addRow("NIC:", m_ncard);
	// CPU information
	m_cpu = new QLineEdit(this);
	m_cpu->setReadOnly(true);
	m_cpu->setText(QString::fromStdString(info.getCPUInfos()));
	m_hlayout->addRow(QStringLiteral("CPU:"), m_cpu);
	// memory information
	m_memTotalAvail = new QLabel(this);
	m_memTotalAvail->setText(QString::fromStdString(info.getMemAvailTotal()));
	m_hlayout->addRow(QStringLiteral("Memory infos: "), m_memTotalAvail);
	// disk information
	m_volumeinfo = new QComboBox(this);
	tmp = info.getVolumeInformation();
	for (it = tmp.cbegin(); it != tmp.cend(); ++it)
	{
		m_volumeinfo->addItem(QIcon(QStringLiteral(":images/25.ico")), QString::fromLocal8Bit((*it).c_str()));  // the same as above
	}
	m_hlayout->addRow(QStringLiteral("Disk infos: "), m_volumeinfo);
	m_hardwareBox->setLayout(m_hlayout);

	m_vlayout->addWidget(m_softwareBox);
	m_vlayout->addWidget(m_hardwareBox);
	m_clipboard = new QDialogButtonBox(Qt::Horizontal, this);
	m_clipboard->addButton("Copy to clipboard", QDialogButtonBox::ActionRole);
	m_vlayout->addWidget(m_clipboard);

	setLayout(m_vlayout);

	connect(m_clipboard, SIGNAL(clicked(QAbstractButton*)), SLOT(onCopytoClipboard(QAbstractButton*)));
}

void SysInfoTab::onCopytoClipboard(QAbstractButton* btn)
{
	QMessageBox::information(this, "Tips", "Not Done!", QMessageBox::Ok);
}

SysInfoTab::~SysInfoTab()
{

}

//////////////////////////////////////////////////////////////////////////
//
LoadedLibTab::LoadedLibTab(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QVBoxLayout(this);
	m_filterExp = new QLineEdit(this);
	m_filterExp->setPlaceholderText("Filter expression");
	m_dllList = new QListView(this);
	m_filterModel = new QSortFilterProxyModel;
	m_layout->addWidget(m_filterExp);
	m_layout->addWidget(m_dllList);

	setLayout(m_layout);
}

LoadedLibTab::~LoadedLibTab()
{

}