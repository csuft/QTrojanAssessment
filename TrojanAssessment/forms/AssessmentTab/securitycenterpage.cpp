#include "securitycenterpage.h"

SecurityCenterPage::SecurityCenterPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_assessmentTab = new AssessmentTab(this);
	m_sysinfoTab = new SysInfoTab(this);
	m_loadedLibsTab = new LoadedLibTab(this);

	addTab(m_assessmentTab, QStringLiteral("Assessment Center"));
	addTab(m_sysinfoTab, QStringLiteral("System Info"));
	addTab(m_loadedLibsTab, QStringLiteral("Loaded Libraries"));
}

SecurityCenterPage::~SecurityCenterPage()
{
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
	m_vlayout->setContentsMargins(0,0,0,0);
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
// Show the libaries loaded by the program
LoadedLibTab::LoadedLibTab(QWidget *parent)
	: QWidget(parent)
{
	m_layout = new QVBoxLayout(this);
	m_layout->setContentsMargins(0,0,0,0);

	m_model = new CustomItemModel(QVector<int>({2, 3, 4}), QVector<int>(), 0, 5, this);
	m_model->setHeaderData(0, Qt::Horizontal, QStringLiteral("Module Name"));
	m_model->setHeaderData(1, Qt::Horizontal, QStringLiteral("Module Path"));
	m_model->setHeaderData(2, Qt::Horizontal, QStringLiteral("PID"));
	m_model->setHeaderData(3, Qt::Horizontal, QStringLiteral("Base Address"));
	m_model->setHeaderData(4, Qt::Horizontal, QStringLiteral("Size"));

	m_libtable = new QTableView(this);
	m_libtable->setModel(m_model);
	m_libtable->verticalHeader()->hide();
	m_libtable->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_libtable->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_libtable->horizontalHeader()->setStretchLastSection(true);
	m_libtable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_libtable->setSelectionMode(QAbstractItemView::SingleSelection);
	m_libtable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_libtable->setShowGrid(false);
	m_libtable->horizontalHeader()->setHighlightSections(false);
	m_libtable->horizontalHeader()->setDefaultSectionSize(75);
	m_libtable->setItemDelegate(new NoFocusDelegate());

	doLoadlibs();

	m_layout->addWidget(m_libtable);
	setLayout(m_layout);
}

void LoadedLibTab::doLoadlibs()
{
	HANDLE hModuleSnap = INVALID_HANDLE_VALUE; 
	MODULEENTRY32 me32; 
	int index = 0;
	char buffer[256] = {'\0'};

	//  Take a snapshot of all modules in the specified process. 
	hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, GetCurrentProcessId()); 
	if( hModuleSnap == INVALID_HANDLE_VALUE ) 
	{ 
		return ; 
	} 

	//  Set the size of the structure before using it. 
	me32.dwSize = sizeof( MODULEENTRY32 ); 

	//  Retrieve information about the first module, 
	//  and exit if unsuccessful 
	if( !Module32First( hModuleSnap, &me32 ) ) 
	{ 
		CloseHandle( hModuleSnap );     // Must clean up the snapshot object! 
		return ; 
	} 

	//  Now walk the module list of the process, 
	//  and display information about each module 
	do 
	{
		m_model->insertRow(index);
		wcstombs(buffer, me32.szModule, 256);
		m_model->setData(m_model->index(index, 0), buffer);
		wcstombs(buffer, me32.szExePath, 256);
		m_model->setData(m_model->index(index, 1), buffer);
		memset(buffer, 0, 256);
		_snprintf(buffer, 256, "0x%08X(%d)", me32.th32ProcessID, me32.th32ProcessID);
		m_model->setData(m_model->index(index, 2), buffer);
		memset(buffer, 0, 256);
		_snprintf(buffer, 256, "0x%08X", (DWORD)me32.modBaseAddr);
		m_model->setData(m_model->index(index, 3), buffer);
		memset(buffer, 0, 256);
		_snprintf(buffer, 256, "0x%08X", me32.modBaseSize);
		m_model->setData(m_model->index(index, 4), buffer);
		index++;
	} while( Module32Next( hModuleSnap, &me32 ) ); 
	//  Do not forget to clean up the snapshot object. 
	CloseHandle( hModuleSnap ); 
}

LoadedLibTab::~LoadedLibTab()
{

}