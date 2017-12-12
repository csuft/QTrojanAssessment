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
	~CustomToolButton(){}
	void setButtonPressed(bool isPressed);

private:
	CustomToolButton(const CustomToolButton& obj);
	CustomToolButton& operator=(const CustomToolButton& obj);
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void doPaintStuff(int topColor, int centerColor, int bottomColor);
private:
	bool m_mousePressed;
	bool m_mouseHover;
	QString m_filePath;
};

#endif // CUSTOMTOOLBUTTON_H
