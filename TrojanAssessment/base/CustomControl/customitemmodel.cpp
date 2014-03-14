#include "customitemmodel.h"

CustomItemModel::CustomItemModel(QObject *parent)
	: QStandardItemModel(parent)
{

}

CustomItemModel::CustomItemModel(int r, int c, QObject* parent = NULL)
	: QStandardItemModel(r, c, parent), m_columnsAlignCenter(), m_columnsAlignRight()
{
	// NOTHING to do
}


CustomItemModel::CustomItemModel(QVector<int>& colsAlignCenter, QVector<int>& colsAlignRight, int row, int col, QObject* parent)
	: QStandardItemModel(row, col, parent), m_columnsAlignCenter(colsAlignCenter), m_columnsAlignRight(colsAlignRight)
{
	// Nothing to do
}
/*
 * Since the text alignment defaults to Qt::AlignLeft, we only need to reimplement the other
 * two alignments.
 */
QVariant CustomItemModel::data(const QModelIndex& index, int role = Qt::DisplayRole)
{
	if (role == Qt::TextAlignmentRole)
	{
		if (m_columnsAlignCenter.contains(index.column()))
		{
			return Qt::AlignCenter;
		}
		if (m_columnsAlignRight.contains(index.column()))
		{
			return Qt::AlignRight;
		}
	}
	return QStandardItemModel::data(index, role);
}