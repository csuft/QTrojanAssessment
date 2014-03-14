#ifndef SHADOWWINDOW_H
#define SHADOWWINDOW_H

#include <QDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>

class ShadowWindow : public QDialog
{
	Q_OBJECT

public:
	explicit ShadowWindow(QWidget *parent = NULL);
	~ShadowWindow();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	ShadowWindow(const ShadowWindow& obj);
	ShadowWindow& operator=(const ShadowWindow& obj);

private:
	bool m_isPressed;
	QPoint m_point;
};

#endif // SHADOWWINDOW_H
