/********************************************************************************
** Form generated from reading UI file 'Builder.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDER_H
#define UI_BUILDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BuilderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BuilderClass)
    {
        if (BuilderClass->objectName().isEmpty())
            BuilderClass->setObjectName(QString::fromUtf8("BuilderClass"));
        BuilderClass->resize(600, 400);
        menuBar = new QMenuBar(BuilderClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        BuilderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BuilderClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BuilderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(BuilderClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        BuilderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(BuilderClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BuilderClass->setStatusBar(statusBar);

        retranslateUi(BuilderClass);

        QMetaObject::connectSlotsByName(BuilderClass);
    } // setupUi

    void retranslateUi(QMainWindow *BuilderClass)
    {
        BuilderClass->setWindowTitle(QApplication::translate("BuilderClass", "Builder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BuilderClass: public Ui_BuilderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDER_H
