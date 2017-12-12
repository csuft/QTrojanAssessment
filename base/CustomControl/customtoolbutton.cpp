#include "customtoolbutton.h"

CustomToolButton::CustomToolButton(const QString& path, QWidget *parent)
	: QToolButton(parent), m_filePath(path)
{
	// Get the widget's palette, we do have to change the color of the tool button.
	QPalette text_palette = palette();
	text_palette.setColor(QPalette::ButtonText, QColor(230, 230, 230));
	setPalette(text_palette);
	// set the style of QToolButton.
	setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	// set the font style of tool buttons
	// since the return value has the type of const, we have to remove the
	// constness if we want to modify.
	QFont text_font = const_cast<QFont&>(font());
	text_font.setBold(true);
	setFont(text_font);
	// set the fixed size for tool buttons.
	QPixmap background(m_filePath);
	setIcon(background);
	setIconSize(background.size());
	setFixedSize(background.width()+25, background.height()+25);

	setAutoRaise(true);
	m_mousePressed = false;
	m_mouseHover = false;
}
/*
 * Arguments topColor, centerColor, bottomColor are alpha values for QColor.
 */
void CustomToolButton::doPaintStuff(int topColor, int centerColor, int bottomColor)
{
	QPainter painter(this);
	QPen p(Qt::NoBrush, 1);
	painter.setPen(p);
	// create linear gradient brush to draw the widget
	QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
	linear.setColorAt(0, QColor(230, 230, 230, topColor));
	linear.setColorAt(0.5, QColor(230, 230, 230, centerColor));
	linear.setColorAt(1, QColor(230, 230, 230, bottomColor));

	// paint the widget.
	painter.setBrush(linear);
	painter.drawRect(rect());
}

void CustomToolButton::setButtonPressed(bool isPressed)
{
	m_mousePressed = isPressed;
	update();
}

void CustomToolButton::enterEvent(QEvent *)
{
	m_mouseHover = true;
	update();
}

void CustomToolButton::leaveEvent(QEvent *)
{
	m_mouseHover = false;
	update();
}

void CustomToolButton::paintEvent(QPaintEvent *event)
{
	if (m_mouseHover)
	{
		doPaintStuff(0, 100, 150);
	}
	else
	{
		if (m_mousePressed)
		{
			doPaintStuff(0, 100, 150);
		}
	}
	QToolButton::paintEvent(event);
}

void CustomToolButton::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit clicked();
	}
}