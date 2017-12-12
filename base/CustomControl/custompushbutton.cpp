#include "custompushbutton.h"

CustomPushButton::CustomPushButton(QWidget *parent)
	: QPushButton(parent)
{

}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QString pixmapPath;
	switch (m_status)
	{
	case NORMAL:
		pixmapPath = m_imagePath;
		break;
	case HOVER:
		pixmapPath = m_imagePath+"_hover";
		break;
	case PRESSED:
		pixmapPath = m_imagePath+"_pressed";
		break;
	default:
		pixmapPath = m_imagePath;
		break;
	}
	// draw the button background
	painter.drawPixmap(rect(), QPixmap(pixmapPath));  

}

void CustomPushButton::mousePressEvent(QMouseEvent *event)
{
	// only when the left button is pressed we force the repaint
	if (event->button() == Qt::LeftButton)
	{
		isPressed = true;
		m_status = PRESSED;
		update();
	}
}

void CustomPushButton::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && isPressed)
	{
		isPressed = false;
		m_status = NORMAL;
		emit clicked();
	}
}

void CustomPushButton::enterEvent(QEvent* event)
{
	isPressed = false;
	m_status = HOVER;
}

void CustomPushButton::leaveEvent(QEvent* event)
{
	isPressed = false;
	m_status = NORMAL;
}

void CustomPushButton::setBtnBackground(const QString& path)
{
	m_imagePath = path;
	// resize the button to fit the background picture.
	setFixedSize(QPixmap(m_imagePath).size()); 
}