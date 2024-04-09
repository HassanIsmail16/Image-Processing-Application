#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include "Image_Class.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>

#define el "\n"
#define space " "

using namespace std;

Image image;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Helper Functions
QPixmap updatedImageDisplay(Image &image) {
    // Convert image to QImage
    QImage qImage(image.width, image.height, QImage::Format_RGB888);

    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            vector<int> color(3, 0);
            for (int channel = 0; channel < image.channels; channel++) {
                color[channel] = image(col, row, channel);
            }
            qImage.setPixel(col, row, qRgb(color[0], color[1], color[2]));
        }
    }

    // Update pixmap
    QPixmap imagePixmap = QPixmap::fromImage(qImage);
    return imagePixmap;
}



// UI Functionality

// Open Image Button Welcome Screen
void MainWindow::on_openImage_clicked() {
    // Gets image from user
    QString filename = QFileDialog::getOpenFileName(this, tr("Select an image to be edited"), QDir::homePath(), "Images (*.png *.bmp *.jpg *.jpeg)");

    // Makes sure that the input is valid and loads the image
    if (!filename.isEmpty()) {
        // Image loading
        QImage qImage(filename);
        qImage = qImage.scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation);
        QPixmap imagePixmap = QPixmap::fromImage(qImage);

        // Display image
        ui -> imageDisplay -> setPixmap(imagePixmap);
        ui -> imageDisplay -> setAlignment(Qt::AlignCenter); // Center image

        // Convert to regular image
        image.loadNewImage(filename.toStdString());

        // Switch to main page
        ui -> stackedWidget -> setCurrentIndex(1);
    }
}

// Effects button functionality
void MainWindow::on_effectsBtn_clicked() {
    // Changes footer to effects navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(1);
}

// Tools button functionality
void MainWindow::on_toolsBtn_clicked() {
    // Changes footer to tools navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(2);
}

// Tools back button functionality
void MainWindow::on_backBtn_tools_clicked() {
    // Goes back to main footer navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(0);

}


// Effects back button functionality
void MainWindow::on_backBtn_fx_clicked() {
    // Goes back to main footer navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(0);

}



// Effects


// Grayscale filter

// Grayscale Filter Algorithm
void GSfilter(Image &image){
    // Puts the same values (average) in all channels in one pixel
    for(int i = 0; i < image.width; ++i){
        for(int j = 0; j < image.height; ++j){
            unsigned int avg = 0;
            for(int k = 0; k < 3; ++k){
                avg += image(i, j, k);
            }
            avg = avg/3;
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
            }
        }
    }
}


// Grayscale button functionality
void MainWindow::on_grayScaleBtn_clicked() {
    // Apply filter on image
    GSfilter(image);
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

// Black and White Filter

// Black and White filter algorithm
void blackAndWhiteFilter(Image &image){
    unsigned int greyScaleValue, color;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Calculate greyscale intensity to determine if the color is closer to black or white
            greyScaleValue = (image(i, j, 0) + image(i, j, 1) + image(i, j, 2)) / 3;

            // If the greyscale intensity is closer to black turn the pixel black, otherwise turn it white.
            if (greyScaleValue < 128){
                color = 0;
            }
            else{
                color = 255;
            }

            // Change the color of the pixel
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = color;
            }
        }
    }
}


// Black and White button functionality
void MainWindow::on_blackAndWhiteBtn_clicked() {
    // Apply filter on image
    blackAndWhiteFilter(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


// Invert Image Filter

// Invert Image filter algorithm
void invertImage(Image &image) {
    // Subtracts the current channel value from 255
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            for (int channel = 0; channel < image.channels; channel++) {
                image(x, y, channel) = 255 - image(x, y, channel);
            }
        }
    }
}

// Invert Image button functionality
void MainWindow::on_invertBtn_clicked() {
    // Apply filter on image
    invertImage(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

// Edge Filter

// Edge Filter Algorithm
void edgeFilter(Image &image){
    for (int i = 0; i < image.width - 1; ++i) {
        for (int j = 0; j < image.height - 1; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (abs(image(i, j + 1, k) - image(i, j, k)) > 49) {
                    image(i, j, k) = 0;
                }
                else {
                    image(i, j, k) = 255;
                }
            }
        }
    }
}

// Edge Filter button functionality
void MainWindow::on_edgeDetectionBtn_clicked() {
    // Apply filter on image
    edgeFilter(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


// Sunlight Filter

// Sunlight Filter Algorithm
void sunlightFilter(Image &image){
    // Iterate over each pixel
    unsigned int light = 0;
    for(int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            image(i, j, 2) *= 0.7;
            // Reduce blue value in the pixel to get yellow (sunlight) filter
            for (int k = 0; k < 3; ++k) {
                // Increase light in image
                light = image(i,j,k);
                light /= 5;
                if(image(i,j,k) + light < 255)
                    image(i,j,k) += light;
                else
                    image(i,j,k) = 255;
            }
        }
    }
}

// Sunlight button functionality
void MainWindow::on_warmBtn_clicked() {
    // Apply filter on image
    sunlightFilter(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


// Oil Painting Filter

// Oil Painting Filter Algorithm
void oilPainting(Image &image){
    Image result(image.width, image.height);
    int radius = 5, intensityLevels = 20;

    for (int row = 0; row < image.width; ++row) {
        for (int col = 0; col < image.height; ++col) {
            // Analyze the intensity of all pixels within the radius

            // Track the RGB values for each intensity level and the count of each intensity level.
            int sumR[21] = {0}, sumG[21] = {0}, sumB[21] = {0}, levelCount[21] = {0};
            int cappedIntensity = 0;
            double realIntensity = 0;
            for (int i = - radius; i <= radius; ++i) {
                for (int j = - radius; j <= radius; ++j) {

                    // Calculate the coordinates of the pixels withing the radius.
                    int currentX = i + row;
                    int currentY = j + col;

                    // Work on pixels inside the image border
                    if ((currentX >= 0) && (currentX < image.width) && (currentY >= 0) && (currentY < image.height)){
                        // Real intensity is the average of the RGB Channels
                        realIntensity = (double) (image(currentX, currentY, 0) + image(currentX, currentY, 1) + image(currentX, currentY, 2)) / 3;
                        // Divide the intensity to a certain amount of levels so that the intensity level falls between 1 and number of intensity level.
                        cappedIntensity = (realIntensity * intensityLevels) / 255;

                        /* Count the frequency of each intensity level
                         * Calculate the sum of RGB values to be able to calculate the average later.
                         * All data for an intensity level is stored at index = intensity level.
                         */
                        levelCount[cappedIntensity]++;
                        sumR[cappedIntensity] += image(currentX, currentY, 0);
                        sumG[cappedIntensity] += image(currentX, currentY, 1);
                        sumB[cappedIntensity] += image(currentX, currentY, 2);
                    }
                }
            }

            // Find the most frequent intensity level (most common color within the radius)
            int maxCount = 0, maxIndex = 0;
            for (int j = 1; j <= intensityLevels; ++j) {
                if (maxCount < levelCount[j]) {
                    maxCount = levelCount[j];
                    maxIndex = j;
                }
            }

            // Assign the pixel the average value of the most frequent intensity level
            result(row, col, 0) = sumR[maxIndex] / maxCount;
            result(row, col, 1) = sumG[maxIndex] / maxCount;
            result(row, col, 2) = sumB[maxIndex] / maxCount;
        }
    }

    image = result;
}

// Oil Painting butotn functionality
void MainWindow::on_oilBtn_clicked() {
    // Apply filter on image
    oilPainting(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}



// Infrared Filter

// Infrared Filter Algorithm
void infraredFilter(Image &image){
    // Puts the same values (average) in all channels in one pixel
    for(int i = 0; i < image.width; ++i){
        for(int j = 0; j < image.height; ++j){
            unsigned int avg = 0;
            for(int k = 0; k < 3; ++k){
                avg += image(i, j, k);
            }
            avg = avg/3;
            for (int k = 0; k < 3; ++k) {
                //Increasing red value in the image
                if(k == 0) {
                    if(image(i, j, 0) + avg <= 255)
                        image(i, j, 0) += avg;
                }
                else
                    image(i, j, 0) = 255;

                image(i, j, k) = avg;
                // Reverse the value of the image
                image(i, j, k) = -(image(i,j,k) - 255);
            }
        }
    }
}


// Infrared Filter button functionality
void MainWindow::on_infraredBtn_clicked() {
    // Apply filter on image
    infraredFilter(image);

    // Update Image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

