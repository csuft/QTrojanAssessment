#include "about.h"

About::About(QWidget *parent)
	: QDialog(parent)
{
	m_layout = new QFormLayout(this);

	m_devs = new QLabel(QStringLiteral("Zhongke Zhang<br>Nan Du<br>Shuyan Qu<br>Min Li"));

	m_cpright = new QLabel(QStringLiteral("Copyright (C) 2014-2015 Hust Information Security Lab."));
	m_website = new QLabel(QStringLiteral("<a href='http://www.cnblogs.com/csuftzzk/'>www.cnblogs.com/csuftzzk/</a>"));

	m_btnbox = new QDialogButtonBox(QDialogButtonBox::Ok);

	m_layout->addRow(QStringLiteral("<b>Developers</b>:"), m_devs);
	m_layout->addRow(QStringLiteral("<b>Copyright</b>:"), m_cpright);
	m_layout->addRow(QStringLiteral("<b>Website</b>:"), m_website);
	m_layout->addRow(m_btnbox);

	setLayout(m_layout);
	connect(m_btnbox, SIGNAL(accepted()), SLOT(accept()));
}

About::~About()
{
	delete m_website;
	delete m_devs;
	delete m_cpright;
	delete m_btnbox;
	delete m_layout;
}
