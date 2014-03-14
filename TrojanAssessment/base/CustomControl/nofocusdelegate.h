#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H

#include <QStyledItemDelegate>
/*
 * This class is derived from QStyledItemDelegate and is used to control how to paint view items.
 * We reimplement the virtual function paint() to remove the dot-line frame when one item has focus.
 */
class NoFocusDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	NoFocusDelegate(QObject *parent = NULL);
	~NoFocusDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
	NoFocusDelegate& operator=(const NoFocusDelegate& obj);
	NoFocusDelegate(const NoFocusDelegate& obj);
};

#endif // NOFOCUSDELEGATE_H
