#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>

class About : public QDialog
{
	Q_OBJECT

public:
	About(QWidget *parent = 0);
	~About();

private:
	QLabel* m_devs;
	QLabel* m_cpright;
	QLabel* m_website;
	QDialogButtonBox* m_btnbox;
	QFormLayout* m_layout;
};

#endif // ABOUT_H
