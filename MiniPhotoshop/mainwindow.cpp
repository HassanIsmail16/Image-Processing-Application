#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
// #include "Image_Class.h"
#include <QFileDialog>
#include <QMessageBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}



void MainWindow::on_openImage_clicked() {
    // Gets image from user
    QString filename = QFileDialog::getOpenFileName(this, tr("Select an image to be edited"), "./", "Images (*.png *.bmp *.jpg *.jpeg)");

    // Exception Handling Here //
    if (QString::compare(filename, QString()) == 0) {

    }

    QImage image;
    bool validImage = image.load(filename);

    // Exception Handling Here //
    if (!validImage) {

    }

    // Display Image
    image = image.scaledToHeight(ui -> imageDisplay -> height(), Qt::SmoothTransformation);
    ui -> imageDisplay -> setAlignment(Qt::AlignCenter);
    ui -> imageDisplay -> setPixmap(QPixmap::fromImage(image));

    // Update UI
    ui -> openImage -> hide();
    ui -> createImage -> hide();
    ui -> Heading -> hide();
}

