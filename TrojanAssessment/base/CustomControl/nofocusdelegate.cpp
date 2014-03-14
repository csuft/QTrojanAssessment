#include "nofocusdelegate.h"

NoFocusDelegate::NoFocusDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{

}

NoFocusDelegate::~NoFocusDelegate()
{

}
/*
 * Reimplemented the virtual function QStyledItemDelegate::paint()
 */
void NoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QStyleOptionViewItem itemOption(option);
	// remove the focus state
	if (itemOption.state & QStyle::State_HasFocus)
	{
		itemOption.state ^= QStyle::State_HasFocus;
	}
	QStyledItemDelegate::paint(painter, itemOption, index);
}
