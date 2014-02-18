/********************************************************************************
** Form generated from reading UI file 'trojanassessment.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TROJANASSESSMENT_H
#define UI_TROJANASSESSMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrojanAssessmentClass
{
public:
    QAction *actionExport;
    QAction *actionExit;
    QAction *actionFile_Monitors;
    QAction *actionFlow_Rank;
    QAction *actionIE_Plugins;
    QAction *actionIE_Browser;
    QAction *actionAbout_Program;
    QAction *actionAbout_Qt;
    QAction *actionLocal_Help;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTreeWidget *treeWidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QMenuBar *menuBar;
    QMenu *menuStart;
    QMenu *menuMisc;
    QMenu *menuHelp;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TrojanAssessmentClass)
    {
        if (TrojanAssessmentClass->objectName().isEmpty())
            TrojanAssessmentClass->setObjectName(QStringLiteral("TrojanAssessmentClass"));
        TrojanAssessmentClass->resize(595, 405);
        actionExport = new QAction(TrojanAssessmentClass);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/22.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionExport->setIcon(icon);
        actionExit = new QAction(TrojanAssessmentClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/6.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionExit->setIcon(icon1);
        actionFile_Monitors = new QAction(TrojanAssessmentClass);
        actionFile_Monitors->setObjectName(QStringLiteral("actionFile_Monitors"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/5.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionFile_Monitors->setIcon(icon2);
        actionFlow_Rank = new QAction(TrojanAssessmentClass);
        actionFlow_Rank->setObjectName(QStringLiteral("actionFlow_Rank"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/16.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionFlow_Rank->setIcon(icon3);
        actionIE_Plugins = new QAction(TrojanAssessmentClass);
        actionIE_Plugins->setObjectName(QStringLiteral("actionIE_Plugins"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/7.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionIE_Plugins->setIcon(icon4);
        actionIE_Browser = new QAction(TrojanAssessmentClass);
        actionIE_Browser->setObjectName(QStringLiteral("actionIE_Browser"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/20.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionIE_Browser->setIcon(icon5);
        actionAbout_Program = new QAction(TrojanAssessmentClass);
        actionAbout_Program->setObjectName(QStringLiteral("actionAbout_Program"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/11.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionAbout_Program->setIcon(icon6);
        actionAbout_Qt = new QAction(TrojanAssessmentClass);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/21.jpg"), QSize(), QIcon::Normal, QIcon::On);
        actionAbout_Qt->setIcon(icon7);
        actionLocal_Help = new QAction(TrojanAssessmentClass);
        actionLocal_Help->setObjectName(QStringLiteral("actionLocal_Help"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/18.ico"), QSize(), QIcon::Normal, QIcon::On);
        actionLocal_Help->setIcon(icon8);
        centralWidget = new QWidget(TrojanAssessmentClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        treeWidget = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        splitter->addWidget(treeWidget);

        horizontalLayout->addWidget(splitter);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        TrojanAssessmentClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(TrojanAssessmentClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 595, 17));
        menuStart = new QMenu(menuBar);
        menuStart->setObjectName(QStringLiteral("menuStart"));
        menuMisc = new QMenu(menuBar);
        menuMisc->setObjectName(QStringLiteral("menuMisc"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        TrojanAssessmentClass->setMenuBar(menuBar);
        toolBar = new QToolBar(TrojanAssessmentClass);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        TrojanAssessmentClass->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(TrojanAssessmentClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TrojanAssessmentClass->setStatusBar(statusBar);

        menuBar->addAction(menuStart->menuAction());
        menuBar->addAction(menuMisc->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuStart->addAction(actionExport);
        menuStart->addSeparator();
        menuStart->addAction(actionExit);
        menuMisc->addAction(actionFile_Monitors);
        menuMisc->addAction(actionFlow_Rank);
        menuMisc->addSeparator();
        menuMisc->addAction(actionIE_Plugins);
        menuMisc->addAction(actionIE_Browser);
        menuHelp->addAction(actionAbout_Program);
        menuHelp->addAction(actionAbout_Qt);
        menuHelp->addSeparator();
        menuHelp->addAction(actionLocal_Help);

        retranslateUi(TrojanAssessmentClass);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TrojanAssessmentClass);
    } // setupUi

    void retranslateUi(QMainWindow *TrojanAssessmentClass)
    {
        TrojanAssessmentClass->setWindowTitle(QApplication::translate("TrojanAssessmentClass", "TrojanAssessment", 0));
        actionExport->setText(QApplication::translate("TrojanAssessmentClass", "Export...", 0));
#ifndef QT_NO_TOOLTIP
        actionExport->setToolTip(QApplication::translate("TrojanAssessmentClass", "Export to files or databases", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExport->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Export to files or databases", 0));
#endif // QT_NO_STATUSTIP
        actionExport->setShortcut(QApplication::translate("TrojanAssessmentClass", "Ctrl+E", 0));
        actionExit->setText(QApplication::translate("TrojanAssessmentClass", "Exit", 0));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("TrojanAssessmentClass", "Quit the program", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Quit the program", 0));
#endif // QT_NO_STATUSTIP
        actionExit->setShortcut(QApplication::translate("TrojanAssessmentClass", "Ctrl+Q", 0));
        actionFile_Monitors->setText(QApplication::translate("TrojanAssessmentClass", "File Monitors...", 0));
#ifndef QT_NO_TOOLTIP
        actionFile_Monitors->setToolTip(QApplication::translate("TrojanAssessmentClass", "File System Monitor", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFile_Monitors->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Monitor on file system", 0));
#endif // QT_NO_STATUSTIP
        actionFile_Monitors->setShortcut(QApplication::translate("TrojanAssessmentClass", "Alt+M", 0));
        actionFlow_Rank->setText(QApplication::translate("TrojanAssessmentClass", "Flow Rank...", 0));
#ifndef QT_NO_TOOLTIP
        actionFlow_Rank->setToolTip(QApplication::translate("TrojanAssessmentClass", "Network uploading and downloading", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFlow_Rank->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Network uploading and downloading", 0));
#endif // QT_NO_STATUSTIP
        actionIE_Plugins->setText(QApplication::translate("TrojanAssessmentClass", "IE Plugins", 0));
#ifndef QT_NO_TOOLTIP
        actionIE_Plugins->setToolTip(QApplication::translate("TrojanAssessmentClass", "Internet Explorer Browser Plugins", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionIE_Plugins->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Internet Explorer Browser Plugins", 0));
#endif // QT_NO_STATUSTIP
        actionIE_Browser->setText(QApplication::translate("TrojanAssessmentClass", "IE Browser", 0));
#ifndef QT_NO_TOOLTIP
        actionIE_Browser->setToolTip(QApplication::translate("TrojanAssessmentClass", "Internet Explorer Browser", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionIE_Browser->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Internet Explorer Browser", 0));
#endif // QT_NO_STATUSTIP
        actionIE_Browser->setShortcut(QApplication::translate("TrojanAssessmentClass", "Alt+E", 0));
        actionAbout_Program->setText(QApplication::translate("TrojanAssessmentClass", "About Program", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout_Program->setToolTip(QApplication::translate("TrojanAssessmentClass", "About Trojan Assessment Platform", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAbout_Program->setStatusTip(QApplication::translate("TrojanAssessmentClass", "About Trojan Assessment Platform", 0));
#endif // QT_NO_STATUSTIP
        actionAbout_Program->setShortcut(QApplication::translate("TrojanAssessmentClass", "Alt+P", 0));
        actionAbout_Qt->setText(QApplication::translate("TrojanAssessmentClass", "About Qt", 0));
#ifndef QT_NO_TOOLTIP
        actionAbout_Qt->setToolTip(QApplication::translate("TrojanAssessmentClass", "About Qt Framework", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAbout_Qt->setStatusTip(QApplication::translate("TrojanAssessmentClass", "About the Qt framework", 0));
#endif // QT_NO_STATUSTIP
        actionLocal_Help->setText(QApplication::translate("TrojanAssessmentClass", "Local Help", 0));
#ifndef QT_NO_TOOLTIP
        actionLocal_Help->setToolTip(QApplication::translate("TrojanAssessmentClass", "Ask for local Help", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionLocal_Help->setStatusTip(QApplication::translate("TrojanAssessmentClass", "Ask for local Help", 0));
#endif // QT_NO_STATUSTIP
        actionLocal_Help->setShortcut(QApplication::translate("TrojanAssessmentClass", "Ctrl+H", 0));
        menuStart->setTitle(QApplication::translate("TrojanAssessmentClass", "Start", 0));
        menuMisc->setTitle(QApplication::translate("TrojanAssessmentClass", "Misc", 0));
        menuHelp->setTitle(QApplication::translate("TrojanAssessmentClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class TrojanAssessmentClass: public Ui_TrojanAssessmentClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TROJANASSESSMENT_H
