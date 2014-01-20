#include "cacheentrydetail.h"
#include "ui_cacheentrydetail.h"

CacheEntryDetail::CacheEntryDetail(QWidget *parent)
	: QDialog(parent)
{
}

CacheEntryDetail::~CacheEntryDetail()
{
	delete ui;
}

CacheEntryDetail::CacheEntryDetail(QWidget *parent, QModelIndex& cindex, QAbstractItemModel* model)
	: QDialog(parent)
{
	ui = new Ui::CacheEntryDetail();
	ui->setupUi(this);
	int row = cindex.row();
	ui->fileNameEdit->setText(model->data(model->index(row, 0)).toString());
	ui->urlLinkEdit->setText(model->data(model->index(row, 1)).toString());
	ui->pathEdit->setText(model->data(model->index(row, 2)).toString());
	ui->subdirLabel->setText(model->data(model->index(row, 3)).toString());
	ui->headerTextEdit->setText(model->data(model->index(row, 4)).toString());
	ui->histLabel->setText(model->data(model->index(row, 5)).toString());
	ui->sizeLabel->setText(model->data(model->index(row, 6)).toString());

	QDateTime dt = QDateTime::fromString(model->data(model->index(row, 7)).toString(), QStringLiteral("yyyy-MM-dd HH:mm:ss"));
	ui->accessDateTimeEdit->setDateTime(dt);
	dt = QDateTime::fromString(model->data(model->index(row, 8)).toString(), QStringLiteral("yyyy-MM-dd HH:mm:ss"));
	ui->modifiedDateTimeEdit->setDateTime(dt);
	dt = QDateTime::fromString(model->data(model->index(row, 9)).toString(), QStringLiteral("yyyy-MM-dd HH:mm:ss"));
	ui->expDateTimeEdit->setDateTime(dt);
}


