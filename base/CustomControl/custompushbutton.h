#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QPushButton>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

class CustomPushButton : public QPushButton
{
	Q_OBJECT

public:
	explicit CustomPushButton(QWidget *parent = NULL);
	~CustomPushButton(){}
	enum BtnStatus{NORMAL, PRESSED, HOVER};

	void setBtnBackground(const QString& path);
private:
	CustomPushButton(const CustomPushButton& obj);
	CustomPushButton& operator=(const CustomPushButton& obj);

protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

private:
	BtnStatus m_status;  // record the status to take different painting action
	bool isPressed;   // whether the button is pressed.
	QString m_imagePath;
};

#endif // CUSTOMPUSHBUTTON_H
