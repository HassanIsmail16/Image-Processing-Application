#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include "Image_Class.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

using namespace std;

Image mainImage;

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
    QString filename = QFileDialog::getOpenFileName(this, tr("Select an image to be edited"), QDir::homePath(), "Images (*.png *.bmp *.jpg *.jpeg)");

    // Makes sure that the input is valid and loads the image
    if (!filename.isEmpty()) {
        // Image loading
        QImage qImage(filename);
        QPixmap imagePixmap = QPixmap::fromImage(qImage);

        // Get label dimensions
        int width = ui -> imageDisplay -> width();
        int height = ui -> imageDisplay -> height();

        // Display image
        ui -> imageDisplay -> setPixmap(imagePixmap.scaled(width, height, Qt::KeepAspectRatio));
        ui -> imageDisplay -> setAlignment(Qt::AlignCenter); // Center image

        // Hide welcome scree widgets
        ui -> openImage -> hide();
        ui -> createImage -> hide();
        ui -> Heading -> hide();

        // Convert to regular image
        mainImage.loadNewImage(filename.toStdString());
    }
}

