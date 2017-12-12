#ifndef CACHEENTRYDETAIL_H
#define CACHEENTRYDETAIL_H

#include <QDateTime>
#include <QWidget>
#include <QDialog>
#include <QModelIndex>
#include <QAbstractItemModel>

namespace Ui {class CacheEntryDetail;};

class CacheEntryDetail : public QDialog
{
	Q_OBJECT

public:
	CacheEntryDetail(QWidget *parent = 0);
	CacheEntryDetail(QWidget *parent, QModelIndex& cindex, QAbstractItemModel* model);
	~CacheEntryDetail();

private:
	CacheEntryDetail(const CacheEntryDetail& obj);
	CacheEntryDetail& operator=(const CacheEntryDetail& obj);

private:
	Ui::CacheEntryDetail *ui;
};

#endif // CACHEENTRYDETAIL_H
