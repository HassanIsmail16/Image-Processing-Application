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

void copyImage(Image &source, Image &destination){
    for (int i = 0; i < destination.width; ++i) {
        for (int j = 0; j < destination.height; ++j) {
            // Copy each pixel from the original image to the copy.
            for (int k = 0; k < destination.channels; ++k) {
                destination(i, j, k) = source(i, j, k);
            }
        }
    }
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

    // Display new image
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



// Darken & Lighten Filter

// Darken & Lighten Button Functionality
void MainWindow::on_darkenAndLightenBtn_clicked() {
    // Change to Darken and Lighten Filter Navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(3);
}

// Darken Algorithm
void darkFilter(Image &image, float percentage) {
    int dark;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                dark = image(i, j, k);
                if (image(i, j, k) > (dark * (percentage / 100)))
                    image(i, j, k) -= (dark * (percentage / 100));
                else
                    image(i, j, k) = 0;
            }
        }
    }
}

// Lighten Algorithm
void lightFilter(Image &image, float percentage){
    int light;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                light = image(i, j, k);
                if(image(i,j,k) + (light * (percentage / 100)) < 255)
                    image(i, j, k) += (light * (percentage / 100));
                else
                    image(i,j,k) = 255;
            }
        }
    }
}

// Darken Button Functionality
void MainWindow::on_darkenBtn_clicked() {
    // Change to darken configuration footer
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(4);
}

// Lighten Button Functionality
void MainWindow::on_lightenBtn_clicked() {
    // Change to lighten configuration footer
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(5);
}

// Darken value slider functionality
void MainWindow::on_darkenSlider_valueChanged(int value) {
    // Update label
    ui -> darkenValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    darkFilter(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}



// Apply darken button functionality
void MainWindow::on_darkenApplyBtn_clicked() {
    // Apply filter
    darkFilter(image, ui -> darkenSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> darkenSlider -> setValue(0);
}


// Lighten Filter Slider functionality
void MainWindow::on_lightenSlider_valueChanged(int value) {
    // Update label
    ui -> lightenValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    lightFilter(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

// Apply lighten filter button functionality
void MainWindow::on_lightenApplyBtn_clicked() {
    // Apply filter
    lightFilter(image, ui -> lightenSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> lightenSlider -> setValue(0);
}

// Blur Filter

// Blur UI Button Functionality
void MainWindow::on_blurBtn_clicked() {
    // Change Footer Navigation to Blur Configuration
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(6);
}

// Blur Filter Algorithm Functions
double gaussianModel(double x, double y, double standardDeviation) {
    // Does the Gaussian equation for kernel construction
    double result = 1.0 / (2.0 * M_PI * pow(standardDeviation, 2)) * exp(- ((pow(x, 2) + pow(y, 2)) / (2.0 * pow(standardDeviation, 2))));
    return result;
}

vector<vector<double>> constructGaussianKernel(double kernelSize, double standardDeviation) {
    vector<vector<double>> gaussianKernel(kernelSize, vector<double>(kernelSize, 0));

    // Gets the weights of the kernel for each cell
    for (int x = 0; x < (int) kernelSize; x++) {
        for (int y = 0; y < (int) kernelSize; y++) {
            gaussianKernel[x][y] = gaussianModel(x - ((kernelSize - 1) / 2), y - ((kernelSize - 1) / 2), standardDeviation);
        }
    }

    return gaussianKernel;
}

double getConvolutedCell(int value, int kernelX, int kernelY, const vector<vector<double>> &gaussianKernel) {
    // Multiplies the value of the pixel by its corresponding kernel value
    double result = value * gaussianKernel[kernelX][kernelY];
    return result;
}

Image kernelConvolution(Image &image, double kernelSize, const vector<vector<double>>& gaussianKernel) {
    // Creates a copy of the image to be blurred
    Image blurredImage(image.width, image.height);
    copyImage(image, blurredImage);

    // Gets the center of the kernel
    int center = (int) (kernelSize - 1) / 2;

    // Loops over the image
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            // Initializes the kernel weight sum to normalize the blur values and initializes the blur value for each channel at 0
            double kernelWeightSum = 0, currentPixelR = 0, currentPixelG = 0, currentPixelB = 0;

            // Loops over each cell of the kernel
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j < kernelSize; j++) {
                    // Gets the pixel that corresponds with the ith row and jth column of the kernel around the current image pixel
                    int x = col - center + i, y = row - center + j;

                    // Checks if there exists a corresponding pixel for the current kernel cell inside the image
                    if (x >= 0 && x < image.width && y >= 0 && y < image.height) {
                        // Gets the resulting blur values for each of the 3 color channels
                        currentPixelR += getConvolutedCell(image(x, y, 0), i, j, gaussianKernel);
                        currentPixelG += getConvolutedCell(image(x, y, 1), i, j, gaussianKernel);
                        currentPixelB += getConvolutedCell(image(x, y, 2), i, j, gaussianKernel);

                        // Gets the weight sum of the used kernel to be used in normalization
                        kernelWeightSum += gaussianKernel[i][j];
                    }
                }
            }

            // Adjusts the new pixel values
            blurredImage.setPixel(col, row, 0, currentPixelR / kernelWeightSum);
            blurredImage.setPixel(col, row, 1, currentPixelG / kernelWeightSum);
            blurredImage.setPixel(col, row, 2, currentPixelB / kernelWeightSum);
        }
    }
    return blurredImage;
}

void gaussianBlur(Image &image, double kernelSize) {
    // Gets standard deviation for kernel construction
    double standardDeviation = kernelSize / (2.0 * sqrt(2.0 * log(2.0)));

    // Constructs the kernel
    vector<vector<double>> gaussianKernel = constructGaussianKernel(kernelSize, standardDeviation);

    // Does the kernel convolution process to the image to blur it
    image = kernelConvolution(image, kernelSize, gaussianKernel);
}

// Blur Slider Functionality
void MainWindow::on_blurSlider_valueChanged(int value) {
    // Update label
    ui -> blurValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    gaussianBlur(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

// Blur apply button functionality
void MainWindow::on_blurApplyBtn_clicked() {
    // Apply filter
    gaussianBlur(image, ui -> blurSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> blurSlider -> setValue(1);
}


void MainWindow::on_tvBtn_clicked()
{

}

