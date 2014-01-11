#include "filemonitorpage.h"

FileMonitorPage::FileMonitorPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_execFileTab = new ExecFileTab;
	m_dataFileTab = new DataFileTab;
	m_browserTab = new FileBrowserTab;

	addTab(m_dataFileTab, QStringLiteral("Data Files"));
	addTab(m_execFileTab, QStringLiteral("Executable Files"));
	addTab(m_browserTab, QStringLiteral("File Browser"));
}

FileMonitorPage::~FileMonitorPage()
{
	if (m_browserTab) { delete m_browserTab; m_browserTab = NULL; }
	if (m_execFileTab) { delete m_execFileTab; m_execFileTab = NULL; }
	if (m_dataFileTab) { delete m_dataFileTab; m_dataFileTab = NULL; }
}

void FileMonitorPage::onChangeTab(int index)
{
	if (index == 1)
	{
		setCurrentWidget(m_dataFileTab);
	}
	else if (index == 2)
	{
		setCurrentWidget(m_execFileTab);
	}
	else
	{
		setCurrentWidget(m_browserTab);
	}
	
}

//////////////////////////////////////////////////////////////////////////
// Implementation of FileMonitorPage class.
DataFileTab::DataFileTab(QWidget* parent)
	: QWidget(parent)
{

}

DataFileTab::~DataFileTab()
{
	
}
//////////////////////////////////////////////////////////////////////////
// Implementation of ExecFileTab class.
ExecFileTab::ExecFileTab(QWidget* parent)
	: QWidget(parent)
{

}

ExecFileTab::~ExecFileTab()
{
	
}

//////////////////////////////////////////////////////////////////////////
// Implementation of FileBrowserTab class.
FileBrowserTab::FileBrowserTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	
}

FileBrowserTab::~FileBrowserTab()
{
	
}