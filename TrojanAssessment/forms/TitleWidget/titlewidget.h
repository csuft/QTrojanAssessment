#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>

#include "../../base/CustomControl/customtoolbutton.h"
#include "../../base/CustomControl/custompushbutton.h"

class TitleWidget : public QWidget
{
	Q_OBJECT

public:
	explicit TitleWidget(QWidget *parent = NULL);
	~TitleWidget();
private:
	TitleWidget& operator=(const TitleWidget& obj);
	TitleWidget(const TitleWidget& obj);

private slots:
	void onToolBtnClicked(const QString& obj);

signals:
	void ShowMinimizedBtnClicked();
	void CloseWindowBtnClicked();
	void ToolBtnClicked(int index);
	void SettingsBtnClicked();
private:
	// top part
	QLabel* m_windowTitle;
	CustomPushButton* m_settings;
	CustomPushButton* m_minBtn;
	CustomPushButton* m_closeBtn;
	// bottom part
	QList<CustomToolButton*> m_toolBtnList;
	// layout managers
	QHBoxLayout* m_topLayout;
	QHBoxLayout* m_bottomLayout;
	QVBoxLayout* m_mainLayout;
};

#endif // TITLEWIDGET_H
