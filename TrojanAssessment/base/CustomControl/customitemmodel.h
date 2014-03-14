#ifndef CUSTOMITEMMODEL_H
#define CUSTOMITEMMODEL_H

#include <QStandardItemModel>
#include <QVariant>
#include <QVector>

class CustomItemModel : public QStandardItemModel
{
	Q_OBJECT

public:
	explicit CustomItemModel(QObject *parent = NULL){}
	CustomItemModel(int r, int c, QObject* parent = NULL) ;
	CustomItemModel(QVector<int>& colsAlignCenter, QVector<int>& colsAlignRight, int row, int col, QObject* parent);
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole);
	~CustomItemModel(){}

private:
	CustomItemModel& operator=(const CustomItemModel& obj);
	CustomItemModel(const CustomItemModel& obj);

private:
	QVector<int> m_columnsAlignRight;
	QVector<int> m_columnsAlignCenter;
};

#endif // CUSTOMITEMMODEL_H
