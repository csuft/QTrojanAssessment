/********************************************************************************
** Form generated from reading UI file 'cacheentrydetail.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CACHEENTRYDETAIL_H
#define UI_CACHEENTRYDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CacheEntryDetail
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *pathEdit;
    QLineEdit *fileNameEdit;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *subdirLabel;
    QLabel *label_4;
    QLineEdit *urlLinkEdit;
    QLabel *label;
    QTextEdit *headerTextEdit;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLabel *histLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLabel *sizeLabel;
    QFormLayout *formLayout;
    QLabel *label_8;
    QDateTimeEdit *accessDateTimeEdit;
    QLabel *label_9;
    QDateTimeEdit *modifiedDateTimeEdit;
    QLabel *label_10;
    QDateTimeEdit *expDateTimeEdit;

    void setupUi(QWidget *CacheEntryDetail)
    {
        if (CacheEntryDetail->objectName().isEmpty())
            CacheEntryDetail->setObjectName(QStringLiteral("CacheEntryDetail"));
        CacheEntryDetail->resize(334, 280);
        verticalLayout = new QVBoxLayout(CacheEntryDetail);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(CacheEntryDetail);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        pathEdit = new QLineEdit(CacheEntryDetail);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));

        gridLayout->addWidget(pathEdit, 2, 2, 1, 1);

        fileNameEdit = new QLineEdit(CacheEntryDetail);
        fileNameEdit->setObjectName(QStringLiteral("fileNameEdit"));

        gridLayout->addWidget(fileNameEdit, 0, 2, 1, 1);

        label_5 = new QLabel(CacheEntryDetail);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(label_5, 4, 0, 1, 2);

        label_2 = new QLabel(CacheEntryDetail);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        subdirLabel = new QLabel(CacheEntryDetail);
        subdirLabel->setObjectName(QStringLiteral("subdirLabel"));

        gridLayout->addWidget(subdirLabel, 3, 2, 1, 1);

        label_4 = new QLabel(CacheEntryDetail);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        urlLinkEdit = new QLineEdit(CacheEntryDetail);
        urlLinkEdit->setObjectName(QStringLiteral("urlLinkEdit"));

        gridLayout->addWidget(urlLinkEdit, 1, 2, 1, 1);

        label = new QLabel(CacheEntryDetail);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        headerTextEdit = new QTextEdit(CacheEntryDetail);
        headerTextEdit->setObjectName(QStringLiteral("headerTextEdit"));
        headerTextEdit->setReadOnly(true);

        gridLayout->addWidget(headerTextEdit, 4, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_6 = new QLabel(CacheEntryDetail);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        histLabel = new QLabel(CacheEntryDetail);
        histLabel->setObjectName(QStringLiteral("histLabel"));

        horizontalLayout->addWidget(histLabel);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_7 = new QLabel(CacheEntryDetail);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_2->addWidget(label_7);

        sizeLabel = new QLabel(CacheEntryDetail);
        sizeLabel->setObjectName(QStringLiteral("sizeLabel"));

        horizontalLayout_2->addWidget(sizeLabel);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(horizontalLayout_3);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_8 = new QLabel(CacheEntryDetail);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_8);

        accessDateTimeEdit = new QDateTimeEdit(CacheEntryDetail);
        accessDateTimeEdit->setObjectName(QStringLiteral("accessDateTimeEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, accessDateTimeEdit);

        label_9 = new QLabel(CacheEntryDetail);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_9);

        modifiedDateTimeEdit = new QDateTimeEdit(CacheEntryDetail);
        modifiedDateTimeEdit->setObjectName(QStringLiteral("modifiedDateTimeEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, modifiedDateTimeEdit);

        label_10 = new QLabel(CacheEntryDetail);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        expDateTimeEdit = new QDateTimeEdit(CacheEntryDetail);
        expDateTimeEdit->setObjectName(QStringLiteral("expDateTimeEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, expDateTimeEdit);


        verticalLayout->addLayout(formLayout);

#ifndef QT_NO_SHORTCUT
        label_3->setBuddy(pathEdit);
        label_5->setBuddy(headerTextEdit);
        label_2->setBuddy(urlLinkEdit);
        label->setBuddy(fileNameEdit);
        label_8->setBuddy(accessDateTimeEdit);
        label_9->setBuddy(modifiedDateTimeEdit);
        label_10->setBuddy(expDateTimeEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(CacheEntryDetail);

        QMetaObject::connectSlotsByName(CacheEntryDetail);
    } // setupUi

    void retranslateUi(QWidget *CacheEntryDetail)
    {
        CacheEntryDetail->setWindowTitle(QApplication::translate("CacheEntryDetail", "CacheEntryDetail", 0));
        label_3->setText(QApplication::translate("CacheEntryDetail", "Local Path:", 0));
        label_5->setText(QApplication::translate("CacheEntryDetail", "Header Info:", 0));
        label_2->setText(QApplication::translate("CacheEntryDetail", "URL Link:", 0));
        subdirLabel->setText(QApplication::translate("CacheEntryDetail", "TextLabel", 0));
        label_4->setText(QApplication::translate("CacheEntryDetail", "Subdirs:", 0));
        label->setText(QApplication::translate("CacheEntryDetail", "File Name:", 0));
        label_6->setText(QApplication::translate("CacheEntryDetail", "Hits:", 0));
        histLabel->setText(QApplication::translate("CacheEntryDetail", "TextLabel", 0));
        label_7->setText(QApplication::translate("CacheEntryDetail", "Cache Size:", 0));
        sizeLabel->setText(QApplication::translate("CacheEntryDetail", "TextLabel", 0));
        label_8->setText(QApplication::translate("CacheEntryDetail", "Last Access:", 0));
        label_9->setText(QApplication::translate("CacheEntryDetail", "Last Modified:", 0));
        label_10->setText(QApplication::translate("CacheEntryDetail", "Expiration:", 0));
    } // retranslateUi

};

namespace Ui {
    class CacheEntryDetail: public Ui_CacheEntryDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CACHEENTRYDETAIL_H
