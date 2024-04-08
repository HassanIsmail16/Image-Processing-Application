/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *openImage;
    QLabel *Heading;
    QPushButton *createImage;
    QLabel *imageDisplay;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(28, 29, 32);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        openImage = new QPushButton(centralwidget);
        openImage->setObjectName("openImage");
        openImage->setGeometry(QRect(280, 290, 131, 51));
        openImage->setCursor(QCursor(Qt::PointingHandCursor));
        openImage->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 50, 96);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 9pt \"Poppins\";\n"
"border-radius: 25px;"));
        Heading = new QLabel(centralwidget);
        Heading->setObjectName("Heading");
        Heading->setGeometry(QRect(100, 200, 641, 81));
        Heading->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Poppins\";"));
        createImage = new QPushButton(centralwidget);
        createImage->setObjectName("createImage");
        createImage->setGeometry(QRect(430, 290, 131, 51));
        createImage->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 50, 96);\n"
"color: rgb(255, 255, 255);\n"
"font: 700 9pt \"Poppins\";\n"
"border-radius: 25px;"));
        imageDisplay = new QLabel(centralwidget);
        imageDisplay->setObjectName("imageDisplay");
        imageDisplay->setGeometry(QRect(60, 60, 701, 391));
        MainWindow->setCentralWidget(centralwidget);
        imageDisplay->raise();
        openImage->raise();
        Heading->raise();
        createImage->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(tooltip)
        openImage->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Open the image you want to edit</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        openImage->setText(QCoreApplication::translate("MainWindow", "Open an Image", nullptr));
        Heading->setText(QCoreApplication::translate("MainWindow", "Welcome to the MiniPhotoshop Photo Editor!", nullptr));
#if QT_CONFIG(tooltip)
        createImage->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Create a blank image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        createImage->setText(QCoreApplication::translate("MainWindow", "Create an Image", nullptr));
        imageDisplay->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
