/********************************************************************************
** Form generated from reading UI file 'aboutprogram.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPROGRAM_H
#define UI_ABOUTPROGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AboutProgram
{
public:
    QVBoxLayout *verticalLayout_2;

    void setupUi(QDialog *AboutProgram)
    {
        if (AboutProgram->objectName().isEmpty())
            AboutProgram->setObjectName(QStringLiteral("AboutProgram"));
        AboutProgram->resize(269, 156);
        verticalLayout_2 = new QVBoxLayout(AboutProgram);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));

        retranslateUi(AboutProgram);

        QMetaObject::connectSlotsByName(AboutProgram);
    } // setupUi

    void retranslateUi(QDialog *AboutProgram)
    {
        AboutProgram->setWindowTitle(QApplication::translate("AboutProgram", "AboutProgram", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutProgram: public Ui_AboutProgram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPROGRAM_H
