#include "filemonitorpage.h"

FileMonitorPage::FileMonitorPage(QWidget *parent)
	: QTabWidget(parent)
{
	m_execFileTab = new ExecFileTab(this);
	m_dataFileTab = new DataFileTab(this);
	m_browserTab = new FileBrowserTab(this);

	addTab(m_dataFileTab, QStringLiteral("Data Files"));
	addTab(m_execFileTab, QStringLiteral("Executable Files"));
	addTab(m_browserTab, QStringLiteral("File Browser"));
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

//////////////////////////////////////////////////////////////////////////
// Implementation of ExecFileTab class.
ExecFileTab::ExecFileTab(QWidget* parent)
	: QWidget(parent)
{

}

//////////////////////////////////////////////////////////////////////////
// Implementation of FileBrowserTab class.
FileBrowserTab::FileBrowserTab(QWidget* parent /* = 0 */)
	: QWidget(parent)
{
	
}