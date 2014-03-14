#ifndef CUSTOMTOOLBUTTON_H
#define CUSTOMTOOLBUTTON_H

#include <QWidget>
#include <QToolButton>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPixmap>
#include <QLinearGradient>
#include <QPalette>

class CustomToolButton : public QToolButton
{
	Q_OBJECT

public:
	CustomToolButton(const QString& path, QWidget *parent = NULL);
	~CustomToolButton();
	void setButtonPressed(bool isPressed);

private:
	CustomToolButton(const CustomToolButton& obj);
	CustomToolButton& operator=(const CustomToolButton& obj);
	
	void doPaintStuff(int topColor, int centerColor, int bottomColor);
protected:
	virtual void enterEvent(QEvent *event);
	virtual void leaveEvent(QEvent *event);
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
private:
	bool m_mousePressed;
	bool m_mouseHover;
	QString m_filePath;
};

#endif // CUSTOMTOOLBUTTON_H
