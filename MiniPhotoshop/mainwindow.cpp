#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <bits/stdc++.h>
#include "Image_Class.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QTimer>
#include <QColorDialog>

#define el "\n"
#define space " "

using namespace std;

Image image;
QString filename;
deque<int> footerWidgetStates;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Create a QTimer
    timer = new QTimer(this);

    // Connect the timeout() signal to the slot that updates the stylesheet
    connect(timer, &QTimer::timeout, this, &MainWindow::updateStyleSheet);

    // Set the interval for the timer (in milliseconds)
    int interval = 300; // 1000 milliseconds = 1 second
    timer->setInterval(interval);

    // Start the timer
    timer->start();

    // Frame Color Dialog
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
    filename = QFileDialog::getOpenFileName(this, tr("Load Image"), QDir::homePath(), "Images (*.png *.bmp *.jpg *.jpeg)");

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
        footerWidgetStates.push_back(0);
    }
}

// Global Back Button Functionality

// Slot implementation to update background color based on condition
void MainWindow::updateStyleSheet() {
    if (footerWidgetStates.size() > 1) {
        ui->globalBackBtn->setStyleSheet("border-radius: 6px; background-color: #ffffff; color: #000000;");
        ui->globalBackBtn->setCursor(Qt::PointingHandCursor);
    } else {
        ui->globalBackBtn->setStyleSheet("border-radius: 6px; background-color: #787878; color: #000000;");
        ui->globalBackBtn->setCursor(Qt::ForbiddenCursor);

    }
}

void MainWindow::on_globalBackBtn_clicked() {
    if (footerWidgetStates.size() > 1) {
        footerWidgetStates.pop_back();
        ui -> FooterNavigationStackedWidget -> setCurrentIndex(footerWidgetStates.back());
    }
}

// Save image button functionality
void MainWindow::on_saveImage_clicked() {
    QString savePath = QFileDialog::getSaveFileName(this, tr("Save Image"), QDir::homePath(), tr("Images (*.png *.jpg *.jpeg *.bmp)"));

    // Check if the user selected a file
    if (!savePath.isEmpty()) {
        // User selected a file, perform save operation
        QPixmap pixmap(updatedImageDisplay(image));
        // Convert QPixmap to QImage
        QImage image = pixmap.toImage();

        // Save the QImage to the selected file
        if (image.save(savePath)) {
            // Image saved successfully
            QMessageBox::information(this, tr("Success"), tr("Image saved successfully."));
        } else {
            // Error saving image
            QMessageBox::critical(this, tr("Error"), tr("Failed to save image."));
        }
    }
}

// Load image button functionality
void MainWindow::on_loadImage_clicked() {
    QMessageBox messageBox;
    messageBox.setText("Do you want to save before loading a new image?");
    messageBox.addButton(tr("Save"), QMessageBox::AcceptRole);
    messageBox.addButton(tr("Don't Save"), QMessageBox::RejectRole);
    messageBox.addButton(tr("Cancel"), QMessageBox::RejectRole);

    int choice = messageBox.exec();

    if (choice == QMessageBox::AcceptRole) {
        on_saveImage_clicked();
        on_openImage_clicked();
    } else if (choice == QMessageBox::RejectRole) {
        on_openImage_clicked();
    } else {
        return;
    }
}

// Effects button functionality
void MainWindow::on_effectsBtn_clicked() {
    // Changes footer to effects navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(1);
    footerWidgetStates.push_back(1);
}

// Tools button functionality
void MainWindow::on_toolsBtn_clicked() {
    // Changes footer to tools navigation
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(2);
    footerWidgetStates.push_back(2);
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
void oilPainting(Image &image, int radius){
    Image result(image.width, image.height);
    int intensityLevels = 20;

    for (int row = 0; row < image.width; ++row) {
        for (int col = 0; col < image.height; ++col) {
            // Analyze the intensity of all pixels within the radius

            // Track the RGB values for each intensity level and the count of each intensity level.
            int sumR[21] = {0}, sumG[21] = {0}, sumB[21] = {0}, levelCount[21] = {0};
            double realIntensity = 0, cappedIntensity;
            int intCappedIntensity;
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
                        cappedIntensity = ceil((realIntensity * intensityLevels) / 255);
                        intCappedIntensity = int(cappedIntensity);

                        /* Count the frequency of each intensity level
                         * Calculate the sum of RGB values to be able to calculate the average later.
                         * All data for an intensity level is stored at index = intensity level.
                         */
                        levelCount[intCappedIntensity]++;
                        sumR[intCappedIntensity] += image(currentX, currentY, 0);
                        sumG[intCappedIntensity] += image(currentX, currentY, 1);
                        sumB[intCappedIntensity] += image(currentX, currentY, 2);
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

    copyImage(result, image);
}

// Oil Painting button functionality
void MainWindow::on_oilBtn_clicked() {
    // Navigate to configuration
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(7);
}

void MainWindow::on_oilPaintingSlider_valueChanged(int value)
{
    // Update label
    ui -> oilPaintingValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    oilPainting(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

void MainWindow::on_oilPaintingApplyBtn_clicked()
{
    // Apply filter
    oilPainting(image, ui -> oilPaintingSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> oilPaintingSlider -> setValue(0);
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
    footerWidgetStates.push_back(3);
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
    footerWidgetStates.push_back(4);
}

// Lighten Button Functionality
void MainWindow::on_lightenBtn_clicked() {
    // Change to lighten configuration footer
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(5);
    footerWidgetStates.push_back(5);
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
    footerWidgetStates.push_back(6);
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

void kernelConvolution(Image &image, double kernelSize, const vector<vector<double>>& gaussianKernel) {
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

            // Adjusts the new pixel values only if kernelWeightSum is not zero
            if (kernelWeightSum != 0) {
                blurredImage.setPixel(col, row, 0, currentPixelR / kernelWeightSum);
                blurredImage.setPixel(col, row, 1, currentPixelG / kernelWeightSum);
                blurredImage.setPixel(col, row, 2, currentPixelB / kernelWeightSum);
            } else {
                // If kernelWeightSum is zero, retain the original pixel values
                blurredImage.setPixel(col, row, 0, image(col, row, 0));
                blurredImage.setPixel(col, row, 1, image(col, row, 1));
                blurredImage.setPixel(col, row, 2, image(col, row, 2));
            }
        }
    }
    copyImage(blurredImage, image);
}

void gaussianBlur(Image &image, double kernelSize) {
    // Gets standard deviation for kernel construction
    double standardDeviation = kernelSize / (2.0 * sqrt(2.0 * log(2.0)));

    // Constructs the kernel
    vector<vector<double>> gaussianKernel = constructGaussianKernel(kernelSize, standardDeviation);

    // Does the kernel convolution process to the image to blur it
    kernelConvolution(image, kernelSize, gaussianKernel);
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

// Purple Filter
void purpleFilter(Image &image){
    // Iterate over each pixel
    unsigned int light = 0;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Reduce green value in the pixel to get purple filter
            image(i,j,1) *= 0.7;
            for (int k = 0; k < 3; ++k) {
                // Increase light in image
                light = image(i,j,k);
                light /= 6;
                if(image(i,j,k) + light < 255)
                    image(i,j,k) += light;
                else
                    image(i,j,k) = 255;
            }
        }
    }
}

// Overlay(purple) button functionality

void MainWindow::on_overlaysBtn_clicked()
{
    // Apply filter on image
    purpleFilter(image);

    // Display new image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

}

// Old TV Filter

void oldTVFilter(Image &image){

    // Create a random number generator
    random_device rd;
    mt19937 generator(rd());

    // Create uniform distribution
    uniform_real_distribution<> distribution(-30, 30);

    for (int row = 0; row < image.width; ++row) {
        for (int col = 0; col < image.height; ++col) {
            // Generate random noise for each channel
            double noiseR = distribution(generator);
            double noiseG = distribution(generator);
            double noiseB = distribution(generator);

            // Add noise to all channels
            image(row, col, 0) = min(image(row, col, 0) + noiseR, 255.0);
            image(row, col, 1) = min(image(row, col, 1) + noiseG, 255.0);
            image(row, col, 2) = min(image(row, col, 2) + noiseB, 255.0);
        }
    }
    darkFilter(image, 5);
}

// TV button functionality

void MainWindow::on_tvBtn_clicked()
{
    // Apply filter on image
    oldTVFilter(image);

    // Display new image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

}


// Flip Image
void flipImageHorizontally(Image &image){
    // Initialize a copy of the original image
    Image copy(image.width, image.height);
    copyImage(image, copy);

    // Loop through all pixels
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // fill the image from right to left.
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = copy(image.width - 1 - i, j, k);
            }
        }
    }
}

void flipImageVertically(Image &image){
    // Initialize a copy of the original image
    Image copy(image.width, image.height);
    copyImage(image, copy);

    // Loop through all pixels
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // fill the image from bottom to top.
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = copy(i, image.height - 1 - j, k);
            }
        }
    }
}

// Flip Buttons Functionality
void MainWindow::on_flipBtn_clicked()
{
    // Navigate to flip page
    ui->FooterNavigationStackedWidget -> setCurrentIndex(12);
    footerWidgetStates.push_back(12);
}


void MainWindow::on_flipVerticallyBtn_clicked()
{
    // Apply filter on image
    flipImageVertically(image);

    // Display new image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

void MainWindow::on_flipHorizontallyBtn_clicked()
{
    // Apply filter on image
    flipImageHorizontally(image);

    // Display new image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}




// Rotate Button Functionality
void MainWindow::on_rotateBtn_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(8);
    footerWidgetStates.push_back(8);
}


void rotate90(Image &image) {
    // Rotates the image using the flipping and a specific traversal pattern
    Image result(image.height, image.width);
    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            for (int channel = 0; channel < image.channels; channel++) {
                result(row, col, channel) = image(col, row, channel);
            }
        }
    }
    flipImageHorizontally(result);
    image = result;
}

void rotate180(Image &image) {
    // Flips the image two times to rotate by 180 degrees
    flipImageVertically(image);
    flipImageHorizontally(image);
}

void rotate270(Image &image) {
    // Rotates it 180 + 90 to get 270 rotation
    rotate180(image);
    rotate90(image);
}

void MainWindow::on_rotate90_clicked() {
    rotate90(image);

    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


void MainWindow::on_rotate180_clicked() {
    rotate180(image);

    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


void MainWindow::on_rotate270_clicked() {
    rotate270(image);

    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}



// Skew Filter
int getTranslationValue(int y, double angle, int height) {
    int translatedCoordinate = (height - y) * tan((angle * M_PI) / 180);
    return translatedCoordinate;
}

void skewImage(Image &image, pair<double, int> skewConfiguration) {
    // Gets the skew angle
    double angle = skewConfiguration.first;

    // Gets the skew direction
    int direction = skewConfiguration.second;

    // Creates a new image to be skewed
    Image skewedImage(image.width + getTranslationValue(0, angle, image.height), image.height);

    for (int row = 0; row < image.height; row++) {
        for (int col = 0; col < image.width; col++) {
            // Gets the current translation distance
            int y = (direction == 1) ? row : image.height - row;

            int currentTranslation = getTranslationValue(y, angle, image.height);
            for (int channel = 0; channel < image.channels; channel++) {
                skewedImage(col + currentTranslation, row, channel) = image(col, row, channel);
            }
        }
    }
    image = skewedImage;
}

void MainWindow::on_skewBtn_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(9);
    footerWidgetStates.push_back(9);
}


void MainWindow::on_skewAngleSlider_valueChanged(int value) {
    // Update label
    ui -> skewAngleValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    pair<double, int> skewConfiguration;

    // Gets skew angle value from slider value
    double skewAngle = ui -> skewAngleSlider -> value();

    // Determines the skew direction
    int skewDirection = (skewAngle >= 0) ? 1 : -1;

    // Specifies skew configuration
    skewConfiguration = {abs(skewAngle), skewDirection};

    // Apply the effect on temp image
    skewImage(tempImage, skewConfiguration);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


void MainWindow::on_skewApplyBtn_clicked() {
    pair<double, int> skewConfiguration;

    // Gets skew angle value from slider value
    double skewAngle = ui -> skewAngleSlider -> value();

    // Determines the skew direction
    int skewDirection = (skewAngle >= 0) ? 1 : -1;

    // Specifies skew configuration
    skewConfiguration = {abs(skewAngle), skewDirection};

    // Apply the effect on temp image
    skewImage(image, skewConfiguration);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset skew angle slider
    ui -> skewAngleSlider -> setValue(0);
}


// Change Saturation
struct RGB{
    double r, g, b;
};
struct HSL{
    double h, s, l;
};

HSL rgbToHsl(RGB rgbColor){
    // Initialize HSL color structure to store the result.
    HSL hslColor;

    // Divide RGB values by 255 to change the range from [0, 255] to [0, 1]
    double R = rgbColor.r / 255, G = rgbColor.g / 255, B = rgbColor.b / 255;

    // Calculate the max and min colors
    double maxC = max(R, max(G, B));
    double minC = min(R, min(G, B));
    double delta = maxC - minC;

    // Calculate the Hue
    if (delta == 0){
        hslColor.h = 0;
    }
    else if (maxC == R){
        hslColor.h = 60 * (fmod((G - B) / delta, 6));
    }
    else if (maxC == G){
        hslColor.h = 60 * (((B - R) / delta) + 2);
    }
    else {
        hslColor.h = 60 * (((R - G) / delta) + 4);
    }
    // Make sure that the hue is positive
    if (hslColor.h < 0) hslColor.h += 360;

    // Calculate Lightness
    hslColor.l = (maxC + minC) / 2;

    // Calculate the saturation
    if (delta == 0){
        hslColor.s = 0;
    }
    else {
        hslColor.s = delta / (1 - fabs(2 * hslColor.l - 1));
    }

    return hslColor;
}

RGB hslToRgb(HSL hslColor){
    // Initialize RGB color structure to store the result.
    RGB rgbColor;

    // Variables used to convert HSL to RGB
    double C, X, m;
    C = (1 - fabs(2 * hslColor.l - 1)) * hslColor.s;
    X = C * (1 - fabs(fmod(hslColor.h / 60, 2) - 1));
    m = hslColor.l - C / 2;

    // Convert HSL to RGB depending on the value of Hue
    if (hslColor.h < 60){
        rgbColor = {C + m, X + m, m};
    }
    else if (hslColor.h < 120){
        rgbColor = {X + m, C + m, m};
    }
    else if (hslColor.h < 180){
        rgbColor = {m, C + m, X +m};
    }
    else if (hslColor.h < 240){
        rgbColor = {m, X + m, C + m};
    }
    else if (hslColor.h < 300){
        rgbColor = {X + m, m, C + m};
    }
    else {
        rgbColor = {C + m, m, X + m};
    }

    // Convert from [0, 1] range to [0, 255]
    rgbColor.r *= 255;
    rgbColor.g *= 255;
    rgbColor.b *= 255;

    return rgbColor;
}

void changeSaturation(Image &image, double changePercentage){

    // Calculate saturation change factor
    double changeFactor = (double) (100 + changePercentage) / 100;

    for (int row = 0; row < image.width; ++row) {
        for (int col = 0; col < image.height; ++col) {
            double r = image(row, col, 0), g = image(row, col, 1), b = image(row, col, 2);
            // Convert RGB color space to HSL color space
            RGB rgbColor = {r, g, b};
            HSL hslColor = rgbToHsl(rgbColor);

            // Increase/decrease saturation in HSL color space
            hslColor.s *= changeFactor;

            // Ensure that the value of the new saturation is between [0, 1]
            hslColor.s = max(min(hslColor.s, 1.0), 0.0);

            // Convert HSL color space back to RGB
            rgbColor = hslToRgb(hslColor);

            // Change the saturation of the image
            image(row, col, 0) = rgbColor.r;
            image(row, col, 1) = rgbColor.g;
            image(row, col, 2) = rgbColor.b;
        }
    }
}


// Frame Filter
int frameType;

void MainWindow::on_frameBtn_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(10);
    footerWidgetStates.push_back(10);
}

void MainWindow::on_frameType1_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(11);
    footerWidgetStates.push_back(11);
    frameType = 1;
}


void MainWindow::on_frameType2_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(11);
    footerWidgetStates.push_back(11);
    frameType = 2;
}


void MainWindow::on_frameType3_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(11);
    footerWidgetStates.push_back(11);
    frameType = 3;
}

vector<int> frameColorValues(3, 0);
bool colorSelected = false;

vector<int> MainWindow::on_frameColorBtn_clicked() {
    QColor frameColor = QColorDialog::getColor(Qt::white, this, "Select Frame Color");
    if (frameColor.isValid()) {
        frameColorValues[0] = frameColor.red();
        frameColorValues[1] = frameColor.green();
        frameColorValues[2] = frameColor.blue();
        colorSelected = true;
    }
    return frameColorValues;
}

void MainWindow::on_frameSizeBtn_clicked() {
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(12);
    footerWidgetStates.push_back(12);
}

void MainWindow::on_frameSizeSlider_valueChanged(int value) {
    ui -> frameSizeValueLabel -> setText(QString::number(value));
    Image tempImage(image.width, image.height);
    tempImage = image;
    //frameFilter
}

void MainWindow::on_frameSizeApplyBtn_clicked() {
    // framefilter(image)
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
    ui -> frameSizeSlider -> setValue(0);
}


void MainWindow::on_saturationBtn_clicked()
{
    // Navigate to configuration
    ui -> FooterNavigationStackedWidget -> setCurrentIndex(10);
    footerWidgetStates.push_back(10);
}

void MainWindow::on_saturationSlider_valueChanged(int value)
{
    // Update label
    ui -> saturationValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    changeSaturation(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}

void MainWindow::on_saturationApplyBtn_clicked()
{
    // Apply filter
    changeSaturation(image, ui -> saturationSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> saturationSlider -> setValue(0);
}

// Change Contrast

void changeContrast(Image &image, int contrast){

    // Calculate contrast change factor
    double changeFactor = (double) (259 * (contrast + 255)) / (255 * (259 - contrast));

    for (int row = 0; row < image.width; ++row) {
        for (int col = 0; col < image.height; ++col) {
            for (int channel = 0; channel < image.channels; ++channel) {
                // Calculate new channel value and make sure it's between 0 and 255
                int newVal = changeFactor * (image(row, col, channel) - 128) + 128;
                image(row, col, channel) = max(0, min(newVal, 255));
            }
        }
    }
}

void MainWindow::on_contrastBtn_clicked()
{
    ui ->FooterNavigationStackedWidget -> setCurrentIndex(11);
    footerWidgetStates.push_back(11);
}


void MainWindow::on_contrastSlider_valueChanged(int value)
{
    // Update label
    ui -> contrastValueLabel -> setText(QString::number(value));

    // Create a temp image for previewing the effect
    Image tempImage(image.width, image.height);
    copyImage(image, tempImage);

    // Apply the effect on temp image
    changeContrast(tempImage, value);

    // Display temp image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(tempImage).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));
}


void MainWindow::on_contrastApplyBtn_clicked()
{
    // Apply filter
    changeContrast(image, ui -> contrastSlider -> value());

    // Display image
    ui -> imageDisplay -> setPixmap(updatedImageDisplay(image).scaledToWidth(min(ui -> imageDisplay -> width() * 5, 400), Qt::SmoothTransformation));

    // Reset slider value
    ui -> contrastSlider -> setValue(0);
}


