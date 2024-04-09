/*
FCAI – Structured Programming [CS112] – 2024 - Assignment 3
Program Name:			    CS112_A3_Part1_S18_20230347_20230432_20230588.cpp
Program Description:        The program contains: Grayscale filter, Black and White filter, Image inversion filter, Merge image filter (INCOMPLETE), Flip image filter, and Image rotation filter.
Last Modification Date:	    27/03/2024
Author1 (name - ID - Group - Section - Email):	Hassan Ali Hassan Ali                       20230588 B S18  20230588@stud.fci-cu.edu.eg
Author2 (name - ID - Group - Section - Email):	Momen Abd El-Kader Abd El-Naby Abd El-Kader 20230432 B S18  20230432@stud.fci-cu.edu.eg
Author3 (name - ID - Group - Section - Email):	Mohamed Ali Hassan Amin                     20230347 B S18  11410120230347@stud.cu.edu.eg
Teaching Assistant:		    Ahmed Foad Lotfy
Who did what:
    Hassan Ali:         Main Menu, Image Input Function, Image Save Function, Filter Selection Function, Invert Image Filter, Image Rotation Filters, Frame Filter, Blur Filter, Skew Filter.
    Momen Abd El-Kader: Exception Handling, Copy Image Function, Input Validation, Merge Configuration, Black and White Filter, Flip Image Filter, Crop Filter, Resize Filter, Oil Painting Filter, Saturation Configuration, Constrast Configuration.
    Mohamed Ali:        Grayscale Filter, Merge Image Filter (INCOMPLETE), Lighten & Darken Image Filters, Edge Detection Filter, Purple Filter, Infrared Filter.
 */

#include <bits/stdc++.h>
#include "../../Image_Class.h"
#define el '\n'
#define space ' '

using namespace std;

// General Functions
void filterSelection();
int returnMenu();
string saveImage(Image &image);
Image imageInput();
void copyImage(Image &source, Image &destination);
bool isInteger(const string& input);
int choiceSelection(pair<int, int> range);

// GrayScale Filtering
void GSfilter(Image &image);

// Black and White Filter
void blackAndWhiteFilter(Image &image);

// Image Inversion
void invertImage(Image &image);

// Image Merging
void mergeFilter(Image &image, Image &image2);
void mergeFilter2(Image &image, Image &image2, Image &result);
void mergeConfiguration(Image &image, Image &image2);

// Flip Image
void flipImageHorizontally(Image &image);
void flipImageVertically(Image &image);

// Image Rotation
void rotate90(Image &image);
void rotate180(Image &image);
void rotate270(Image &image);

// Darken and Lighten Image
void darkFilter(Image &image, float percentage);
void lightFilter(Image &image, float percentage);

// Crop Images
pair<int, int> coordinatesInput(Image &image);
void cropImage(Image &image, pair <int, int> dimensions, pair<int, int> coordinates);

// Frame Filter
pair<int, vector<int>> frameConfiguration(Image &image);
int frameSizeConfiguration(Image &image);
vector<int> frameColorConfiguration(Image &image);
bool hexCodeValidation(string hexCode);
int hexConversion(string code);
void frameFilter(Image &image, pair<int, vector<int>> configuration);

// Edge Filter
void edgeFilter(Image &image);

// Resize Images
pair<int, int> dimensionsInput();
void resizeImage(Image &image, int newWidth, int newHeight);

// Blur Filter
double getGaussianKernelSize(Image &image);
double getGaussianStandardDeviation(double kernelSize);
double gaussianModel(double x, double y, double standardDeviation);
vector<vector<double>> constructGaussianKernel(double kernelSize, double standardDeviation);
double getConvolutedCell(int value, int kernelX, int kernelY, const vector<vector<double>> &gaussianKernel);
Image kernelConvolution(Image &image, double kernelSize, const vector<vector<double>>& gaussianKernel);
void gaussianBlur(Image &image);

// Sunlight Filter
void sunlightFilter(Image &image);

// Purple Filter
void purpleFilter(Image &image);

// Infrared Filter
void infraredFilter(Image &image);

// Oil Painting Filter
void oilPainting(Image &image);

// Old TV Filter
void oldTVFilter(Image &image);

// Skew Filter
pair<double, int> getSkewAngle();
int getTranslationValue(int y, double angle, int height);
void skewImage(Image &image);

// Change Saturation
struct RGB{
    double r, g, b;
};
struct HSL{
    double h, s, l;
};
double getPercentage();
HSL rgbToHsl(RGB rgbColor);
RGB hslToRgb(HSL hslColor);
void changeSaturation(Image &image, double changePercentage);

// Change Contrast
int contrastConfiguration();
void changeContrast(Image &image, int contrast);

int main() {
    // Display Header
    cout << "---------------------------------------" << el
         << "   " << "Mini Photoshop for Photo Editing!" << "   " << el
         << "---------------------------------------" << el;
    while (true) {
        // First Menu
        cout << "Please select one of the following choices:" << el
             << "1) Load an image " << el
             << "2) Exit the program" << el;

        int choice = choiceSelection({1, 2});

        switch (choice) {
            case 1:
                filterSelection();
                break;
            case 2:
                cout << "Exiting the program..." << el;
                return 0;
            default:
                cout << "Invalid Choice. Please select 1 or 2..." << el;
                cout << "-------------------------------------" << el;
                break;
        }
    }
}

// General Helper Functions
Image imageInput() {
    // Input prompt
    cout << "Insert an image name with the extension (e.g img.png)" << el
         << "Allowed extensions are .png, .bmp, .tga, .jpg" << el;

    // Initialize variables
    string imageName;
    Image image;

    // Exception handling loop.
    while (true) {
        // File name input
        getline(cin, imageName);
        try {
            image.loadNewImage(imageName);
            cout << "Image Loaded Successfully." << el;
            cout << "-------------------------------------" << el;
            break;
        } catch (invalid_argument &exception){
            cout << exception.what() << el;
            cout << "-------------------------------------" << el;
            cout << "Please enter a valid image name..." << el;
        }
    }

    // Main image loading
    image.loadNewImage(imageName);
    return image;
}

void filterSelection() {
    Image image = imageInput();

    bool loopStatus = true;
    while (loopStatus) {
        // Filter Selection Menu
        cout << "Select one of the following filters to apply: " << el
             << "1) Grayscale Conversion" << el
             << "2) Black and White" << el
             << "3) Invert Image" << el
             << "4) Merge Images" << space << el
             << "5) Flip Image" << el
             << "6) Rotate Image" << el
             << "7) Darken and Lighten Image" << el
             << "8) Crop Image" << el
             << "9) Adding a Frame to the Picture" << el
             << "10) Detect Image Edges" << el
             << "11) Resizing Images" << el
             << "12) Blur Images" << space << el
             << "14) Oil Painting Filter" << el
             << "16) Purple Filter" << space << el
             << "17) Infrared Filter" << space << el
             << "11) Resize Image" << el
             << "12) Blur Image" << el
             << "13) Make image warmer (Land of Wano)" << el
             << "14) Apply The Oil Painting Effect" << el
             << "15) Old TV Filter" << el
             << "16) Purple Overlay" << el
             << "17) Infrared Filter" << el
             << "18) Skew Image" << el
             << "19) Change Image Saturation" << el
             << "20) Change Image Contrast" << el
             << "21) Save current Image" << el
             << "22) Return to previous menu" << el;

        // Input
        int choice = choiceSelection({1, 22});

        switch (choice) {
            case 1: {
                GSfilter(image);
                break;
            }
            case 2: {
                blackAndWhiteFilter(image);
                break;
            }
            case 3: {
                invertImage(image);
                break;
            }
            case 4: {
                cout << "First Image Dimensions: " << image.width << " x " << image.height << el
                     << "Please insert the second image to merge" << el;
                Image image2 = imageInput();
                if (image.width == image2.width && image.height == image2.height){
                    mergeFilter(image, image2);
                }
                else {
                    mergeConfiguration(image, image2);
                }
                break;
            }
            case 5: {
                cout << "Please select one of the following choices:" << el
                     << "1) Flip Horizontally " << el
                     << "2) Flip Vertically" << el;

                // Input
                int flipChoice = choiceSelection({1, 2});

                switch (flipChoice) {
                    case 1:
                        flipImageHorizontally(image);
                        break;
                    case 2:
                        flipImageVertically(image);
                        break;
                    default:
                        cout << "Invalid Choice. Please select 1 or 2..." << el;
                        cout << "-------------------------------------" << el;
                        break;
                }
                break;
            }
            case 6: {
                cout << "Please select the angle of rotation:" << el
                     << "1) 90" << el
                     << "2) 180" << el
                     << "3) 270" << el;

                // Input
                int rotationChoice = choiceSelection({1, 3});

                switch (rotationChoice) {
                    case 1:
                        rotate90(image);
                        break;
                    case 2:
                        rotate180(image);
                        break;
                    case 3:
                        rotate270(image);
                        break;
                    default:
                        cout << "Invalid input. Please select an integer between 1 and 3..." << el;
                        cout << "-------------------------------------" << el;
                        break;
                }
                break;
            }
            case 7: {
                // Input
                cout << "Please enter the change percentage (+ve to lighten the image or -ve to darken the image):" << el;
                int percentage = getPercentage();

                if (percentage == 0){
                    break;
                }
                else if (percentage > 0){
                    lightFilter(image, percentage);
                    break;
                }
                else{
                    percentage = abs(percentage);
                    darkFilter(image, percentage);
                    break;
                }
                break;
            }
            case 8: {
                // Input coordinates
                cout << "Current image dimensions: " << image.width << " x " << image.height << el;
                pair <int, int> coordinates = coordinatesInput(image);

                // Calculate crop boundaries
                int horizontalBound = image.width - coordinates.first + 1;
                int verticalBound = image.height - coordinates.second + 1;

                // Input crop dimensions
                cout << "Maximum crop dimensions: " << horizontalBound << " x " << verticalBound << el;
                pair <int, int> dimensions = dimensionsInput();

                // Validate the dimensions according to the boundaries
                if (dimensions.first > horizontalBound || dimensions.second > verticalBound){
                    cerr << "Invalid crop dimensions. please enter dimensions less than or equal to the maximum allowed dimensions.." << el;
                    cout << "-------------------------------------" << el;
                } else{
                    cropImage(image, dimensions, coordinates);
                }
                break;
            }
            case 9: {
                frameFilter(image, frameConfiguration(image));
                break;
            }
            case 10: {
                blackAndWhiteFilter(image);
                edgeFilter(image);
                break;
            }
            case 11: {
                cout << "Current image dimensions: " << image.width << " x " << image.height << el;
                pair <int, int> dimensions = dimensionsInput();
                int newWidth = dimensions.first;
                int newHeight = dimensions.second;
                resizeImage(image, newWidth, newHeight);
                break;
            }
            case 12: {
                gaussianBlur(image);
                break;
            }
            case 13: {
                sunlightFilter(image);
                break;
            }
            case 14: {
                oilPainting(image);
                break;
            }
            case 15: {
                oldTVFilter(image);
                break;
            }
            case 16: {
                purpleFilter(image);
                break;
            }
            case 17: {
                infraredFilter(image);
                break;
            }
            case 18: {
                skewImage(image);
                break;
            }
            case 19: {
                cout << "Please enter the change percentage (+ve to increase saturation or -ve to decrease saturation):" << el;
                double changePercentage = getPercentage();
                changeSaturation(image, changePercentage);
                break;
            }
            case 20: {
                int contrast = contrastConfiguration();
                changeContrast(image, contrast);
                break;
            }
            case 21: {
                saveImage(image);
                loopStatus = false;
                break;
            }
            case 22: {
                if (returnMenu() == 1) {
                    saveImage(image);
                } else {
                    cout << "Returning to previous menu... " << el;
                }
                loopStatus = false;
                break;
            }
            default: {
                cout << "Invalid choice. Please select a number between 1 and 22 (inclusive)..." << el;
                break;
            }
        }
    }
}

bool isInteger(const string& input){
    regex integer(R"([-]*\d+)");
    return regex_match(input, integer);
}

int returnMenu() {
    // User prompt
    cout << "Select one of the following choices:" << el
         << "1) Save current photo then return to previous menu." << el
         << "2) Return without saving." << el;

    // Choice input
    int choice = choiceSelection({1, 2});

    if (!choice) {
        cout << "Invalid choice. Please select 1 or 2..." << el;
        return returnMenu();
    }

    return choice;
}

string saveImage(Image &image) {
    // New file name input
    cout << "Enter the name of the new image with the extension (e.g img.png):" << el;

    string saveName;
    getline(cin, saveName);

    try{
        // Image saving
        image.saveImage(saveName);
        cout << "Image Saved Successfully." << el;
        cout << "-------------------------------------" << el;
        return "Save Current";
    }
    catch(invalid_argument &exception){
        cout << exception.what() << el;
        cout << "-------------------------------------" << el;
        return "Not Saved";
    }
}

// Copy an image
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

int choiceSelection(pair<int, int> range) {
    // Input
    string choice;
    int intChoice;
    getline(cin, choice);

    // Input Validation
    if (isInteger(choice)) {
        intChoice = stoi(choice);
        if (intChoice >= range.first && intChoice <= range.second) {
            return intChoice;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

// GrayScale Filter
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

// Black and white filter
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

// Image Inversion Filter
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

// Merge Filter
void mergeFilter(Image &image, Image &image2) {
    unsigned int merge = 0;
    // Averages each two corresponding pixels from the two images
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merge = image(i, j, k) + image2(i, j, k);
                image(i, j, k) = merge / 2;
            }
            merge = 0;
        }
    }
}

// Merge the common parts of the 2 images into a third image.
void mergeFilter2(Image &image, Image &image2, Image &result){

    unsigned int merge = 0;
    // Averages each two corresponding pixels from the two images
    for (int i = 0; i < result.width; ++i) {
        for (int j = 0; j < result.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                merge = image(i, j, k) + image2(i, j, k);
                result(i, j, k) = merge / 2;
            }
            merge = 0;
        }
    }

    image = result;
}

void mergeConfiguration(Image &image, Image &image2){
    cout << "First Image Dimensions: " << image.width << " x " << image.height << el
         << "Second Image Dimensions: " << image2.width << " x " << image2.height << el
         << "The two images appear to have different dimensions, what would you like to do?" << el
         << "1) Resize both images to the biggest width and biggest height." << el
         << "2) Merge the common area between the smaller width and smaller height." << el;

    int choice = choiceSelection({1, 2});
    switch (choice) {
        case 1:{
            int maxWidth = max(image.width, image2.width);
            int maxHeight = max(image.height, image2.height);
            resizeImage(image, maxWidth, maxHeight);
            resizeImage(image2, maxWidth, maxHeight);
            mergeFilter(image, image2);
        }
        case 2:{
            int minWidth = min(image.width, image2.width);
            int minHeight = min(image.height, image2.height);
            Image result(minWidth, minHeight);
            mergeFilter2(image, image2, result);
        }
        default:
            cout << "Invalid Choice. Please select 1 or 2..." << el;
            cout << "-------------------------------------" << el;
            break;
    }
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

// Rotate Image
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

// Darken and Lighten Image
void darkFilter(Image &image, float percentage) {
    int dark;

    if(percentage < 0 || percentage > 100){
        cout << "Invalid number!" << el << "Please enter a number from 0 to 100!" << el;
        return;
    }

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

void lightFilter(Image &image, float percentage){
    int light;

    if(percentage < 0 || percentage > 100){
        cout << "Invalid number!" << el << "Please enter a number from 0 to 100!" << el;
        return;
    }

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

// Crop Images
void cropImage(Image &image, pair <int, int> dimensions, pair<int, int> coordinates){
    Image result(dimensions.first, dimensions.second);

    // Loop through all result pixels
    for (int resultRow = 0, imageRow = coordinates.first - 1; resultRow < result.width; ++resultRow, ++imageRow) {
        for (int resultCol = 0, imageCol = coordinates.second - 1; resultCol < result.height; ++resultCol, ++imageCol) {
            // Traverse through original image pixels starting from the coordinates and assign them to the result.
            for (int channel = 0; channel < result.channels; ++channel) {
                result(resultRow, resultCol, channel) = image(imageRow, imageCol, channel);
            }
        }
    }

    // Assign result to the image.
    image = result;
}
pair <int, int> coordinatesInput(Image &image){
    // Initialize valid input pattern
    regex validCoordinates(R"((\d+),\s(\d+))");
    smatch matches;

    // Input
    cout << "Please enter coordinates separated by a comma for the starting point (e.g. 300, 400):" << el;
    string coordinates;
    getline(cin, coordinates);

    // Validate input format and store valid input in matches
    if (!regex_match(coordinates, matches, validCoordinates)){
        cout << "Invalid Coordinates. Please enter coordinates in the correct format." << el;
        cout << "-------------------------------------" << el;
        return coordinatesInput(image);
    }

    // Parse input
    int coordinateX = stoi(matches[1]);
    int coordinateY = stoi(matches[2]);

    // Make sure coordinates are inside the image.
    if (coordinateX > image.width || coordinateY > image.height){
        cout << "Invalid Coordinates. Please enter coordinates inside the bounds of the image." << el;
        cout << "-------------------------------------" << el;
        return coordinatesInput(image);
    }

    // Reject 0 coordinates
    if (coordinateX  == 0 || coordinateY == 0){
        cout << "Invalid Coordinates. Coordinates can't be zero..." << el;
        cout << "-------------------------------------" << el;
        return coordinatesInput(image);
    }

    return {coordinateX, coordinateY};
}

// Frame Filter
pair <int, vector <int>> frameConfiguration(Image &image) {
    while (true) {
        // Frame size
        int frameSize = frameSizeConfiguration(image);

        // Frame color
        vector <int> color = frameColorConfiguration(image);

        // Repeats the configuration process if user chooses to return to the size configuration menu
        if (color[0] == color[1] && color[1] == color[2] && color[2] == -1) {
            continue;
        } else { // Returns current configuration if everything goes smoothly
            return {frameSize, color};
        }
    }
}

int frameSizeConfiguration(Image &image) {
    // Frame size configuration prompt
    cout << "Please enter the size of your frame (Note that maximum frame size of for your photo is "
         << min(image.width, image.height) / 2 << "px)" << el;

    string frameSize;
    int intFrameSize;

    getline(cin, frameSize);

    // Size input validation
    if (!isInteger((frameSize))) {
        cout << "Invalid input (NOT AN INTEGER)." << el;
        return frameSizeConfiguration(image);
    }

    intFrameSize = stoi(frameSize);

    if (intFrameSize < 0) {
        cout << "Invalid input (NEGATIVE INTEGER)." << el;
        return frameSizeConfiguration(image);
    }

    if (intFrameSize > min(image.width, image.height) / 2) {
        cout << "Invalid input (MAXIMUM SIZE IS " << min(image.width, image.height) / 2 << "px)." << el;
        return frameSizeConfiguration(image);
    }

    return intFrameSize;
}

vector <int> frameColorConfiguration(Image &image) {
    // Frame color configuration prompt
    cout << "Select one of the following color configurations for your frame:" << el
         << "1) Red" << el
         << "2) Orange" << el
         << "3) Yellow" << el
         << "4) Green" << el
         << "5) Blue" << el
         << "6) Violet" << el
         << "7) Custom (Hex Code)" << el
         << "8) Return to size configuration" << el;

    int colorChoice = choiceSelection({1, 8});

    if (!colorChoice) {
        cout << "Invalid choice. Please select an integer between 1 and 8 (inclusive)." << el;
        return frameColorConfiguration(image);
    }

    vector <int> color;
    switch (colorChoice) {
        case 1: {
            color = {255, 0, 0};
            return color;
        }
        case 2: {
            color = {255, 165, 0};
            return color;
        }
        case 3: {
            color = {255, 255, 0};
            return color;
        }
        case 4: {
            color = {0, 255, 0};
            return color;
        }
        case 5: {
            color = {0, 0, 255};
            return color;
        }
        case 6: {
            color = {160, 32, 240};
            return color;
        }
        case 7: {
            // Hex color input prompt
            cout << "Enter a 6 digit hex code for your desired color (e.g: 00FF00 - without the hash in the beginning - no spaces)." << el;

            // Hex color input
            string hexCode;
            getline(cin, hexCode);

            // Hex color input validation
            if (hexCodeValidation(hexCode)) {
                string currentCode;
                // Takes each two characters and converts them into the corresponding RGB value
                for (int i = 0, j = 0; i < 6; i++) {
                    currentCode.push_back(hexCode[i]);
                    if (currentCode.size() == 2) {
                        color.push_back(hexConversion(currentCode));
                        currentCode.clear();
                        j++;
                    }
                }
                return color;
            }
        }
        case 8: {
            cout << "Returning to size configuration menu..." << el;
            return {-1, -1, -1};
        }
    }
}

bool hexCodeValidation(string hexCode) {
    // Hexadecimal characters mapping
    string hexChars = "0123456789ABCDEF";

    // Validates that the hexCode lies within hexadecimal characters and contains no spaces or special characters
    if (hexCode.size() == 6) {
        for (auto code : hexCode) {
            if (isalpha(code) || isdigit(code)) {
                for (auto hexChar : hexChars) {
                    if (toupper(code) == hexChar) {
                        return true;
                    }
                }
                return false;
            }
        }
    } else {
        return false;
    }
}

int hexConversion(string code) {
    // Mapping hexadecimal characters
    map <char, int> hexChars = {
            {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
            {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
            {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
    };

    // Converting the hex code snippet
    return (hexChars[toupper(code[1])] + hexChars[toupper(code[0])] * 16);
}

void frameFilter(Image &image, pair <int, vector <int>> configuration) {
    // Vertical Borders
    for (int x = 0; x < image.width; x++) {
        for (int y1 = 0, y2 = image.height - configuration.first; y1 < configuration.first; y1++, y2++) {
            for (int channel = 0; channel < image.channels; channel++) {
                image(x, y1, channel) = configuration.second[channel];
                image(x, y2, channel) = configuration.second[channel];
            }
        }
    }

    // Horizontal Borders
    for (int x1 = 0, x2 = image.width - configuration.first; x1 < configuration.first; x1++, x2++) {
        for (int y = 0; y < image.height; y++) {
            for (int channel = 0; channel < image.channels; channel++) {
                image(x1, y, channel) = configuration.second[channel];
                image(x2, y, channel) = configuration.second[channel];
            }
        }
    }
}

// Edge Filter
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

// Resize Image
pair<int, int> dimensionsInput(){
    // Initialize valid input pattern
    regex validDimensions(R"((\d+)\s[*xX]\s(\d+))");
    smatch matches;

    // Input
    cout << "Please enter the new dimensions in the format width * height (e.g. 1920 * 1080 or 1920 x 1080)" << el;
    string dimensions;
    getline(cin, dimensions);

    // Validate input format and store valid input in matches
    if (!regex_match(dimensions, matches, validDimensions)){
        cout << "Invalid Dimensions. Please enter the new dimensions in the correct format." << el;
        cout << "-------------------------------------" << el;
        return dimensionsInput();
    }
    else if (stoi(matches[1]) == 0 || stoi(matches[2]) == 0){
        cout << "Invalid Dimensions. Dimensions can't be zero..." << el;
        cout << "-------------------------------------" << el;
        return dimensionsInput();
    }

    // Parse input
    int width = stoi(matches[1]);
    int height = stoi(matches[2]);

    return {width, height};
}

void resizeImage(Image &image, int newWidth, int newHeight){
    // Initialize an image with the new dimensions
    Image newImage(newWidth, newHeight);

    // Calculate the ration between old and new dimensions
    double widthRatio = double(image.width) / double(newImage.width);
    double heightRatio = double(image.height) / double(newImage.height);

    for (int row = 0; row < newImage.width; ++row) {
        for (int col = 0; col < newImage.height; ++col) {
            // Map each pixel in the resized image to its nearest neighbor in the original image.
            double mappedRow = floor(row * widthRatio);
            double mappedCol = floor(col * heightRatio);
            for (int channel = 0; channel < newImage.channels; ++channel) {
                newImage(row, col, channel) = image(mappedRow, mappedCol, channel);
            }
        }
    }
    // Store the resized image in the original variable to be able to retrieve it in the menus.
    image = newImage;
}

// Blur Filter
double getGaussianKernelSize(Image &image) {
    // Gets and validates the kernel size from the user
    cout << "Please enter the blur radius. Must be a positive ODD integer less than 50px (Higher is more blurred)" << el;

    string kernelSize;
    getline(cin, kernelSize);

    // Validates that the input is numeric
    if (!isInteger(kernelSize)) {
        cout << "Invalid input. Please enter an integer." << el;
        return getGaussianKernelSize(image);
    }

    double numericKernelSize = stod(kernelSize);

    // Validates that the input is positive
    if (numericKernelSize < 1) {
        cout << "Invalid input. Please enter a positive integer." << el;
        return getGaussianKernelSize(image);
    }

    // Validates that the input falls within the image constraint
    if (numericKernelSize > 50) {
        cout << "Invalid input. Please enter a positive integer less than 50px." << el;
        return getGaussianKernelSize(image);
    }

    // Validates that the input is odd
    if ((int) numericKernelSize % 2  == 0) {
        cout << "Invalid input. Please enter an odd integer." << el;
        return getGaussianKernelSize(image);
    }

    return numericKernelSize;
}

double getGaussianStandardDeviation(double kernelSize) {
    cout << "Please select one of the following choices:" << el
         << "1) Keep the default Gaussian Standard Deviation" << el
         << "2) Customize the Gaussian Standard Deviation" << el
         << "3) Return to kernel size configuration menu" << el
         << "NOTE: The higher the standard deviation the more concentrated the blur will be on the center." << el;

    int choice = choiceSelection({1, 3});

    switch (choice) {
        case 1:
            // Default standard deviation
            return kernelSize / (2.0 * sqrt(2.0 * log(2.0)));
        case 2: {
            cout << "Please enter a positive number to be used as the blur standard deviation. (float/double)" << el;

            string standardDeviationString;
            getline(cin, standardDeviationString);

            // Input validation
            double standardDeviation;

            // Validates that it's a valid double value
            try {
                standardDeviation = stod(standardDeviationString);
            } catch (invalid_argument& e) {
                cout << "Invalid input. Your input \"" << standardDeviationString << "\" doesn't represent a float/double." << el;
                return getGaussianStandardDeviation(kernelSize);
            }

            // Validates that the input is positive
            if (standardDeviation <= 0) {
                cout << "Invalid input. Please enter a positive number." << el;
                return getGaussianStandardDeviation(kernelSize);
            }

            return standardDeviation;
        }
        case 3: {
            return 0;
        }
        default:
            cout << "Invalid input. Please enter a number between 1 and 3 (inclusive)." << el;
            return getGaussianStandardDeviation(kernelSize);
    }
}

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

void gaussianBlur(Image &image) {
    // Gets the desired kernel size from user
    double kernelSize = getGaussianKernelSize(image);

    // Gets standard deviation for kernel construction
    double standardDeviation = getGaussianStandardDeviation(kernelSize);

    // Constructs the kernel
    vector<vector<double>> gaussianKernel = constructGaussianKernel(kernelSize, standardDeviation);

    // Does the kernel convolution process to the image to blur it
    image = kernelConvolution(image, kernelSize, gaussianKernel);
}

// Sunlight Filter
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

// Infrared Filter
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

// Oil Painting Filter
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

// Old TV Filter
void oldTVFilter(Image &image){

}

// Skew Filter
pair<double, int> getSkewAngle() {
    cout << "Please enter a skew angle between -89 and 89 to be used. (float/double)" << el;

    string skewAngleString;
    getline(cin, skewAngleString);

    // Input validation
    double skewAngle;

    // Validates that it's a valid double value
    try {
        skewAngle = stod(skewAngleString);
    } catch (invalid_argument& e) {
        cout << "Invalid input. Your input \"" << skewAngleString << "\" doesn't represent a float/double." << el;
        return getSkewAngle();
    }

    // Determines the skew direction
    int skewDirection = (skewAngle >= 0) ? 1 : -1;

    // Validates that the angle is not less than 0
    if (skewAngle < -89) {
        cout << "Invalid input. The angle you entered is less than -89." << el;
        return getSkewAngle();
    }

    // Validates that the angle is not higher than 90
    if (skewAngle > 89) {
        cout << "Invalid input. The angle you entered is higher than 89." << el;
        return getSkewAngle();
    }

    return {abs(skewAngle), skewDirection};
}

int getTranslationValue(int y, double angle, int height) {
    int translatedCoordinate = (height - y) * tan((angle * M_PI) / 180);
    return translatedCoordinate;
}

void skewImage(Image &image) {
    // Gets the skew configuration from user
    pair<double, int> skewConfiguration = getSkewAngle();

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

// Saturation
double getPercentage(){
    // Get change percentage
    string strChangePercentage;
    getline(cin, strChangePercentage);

    // Validate input
    regex number(R"([-]*(\d+)[.]*(\d+))");
    if (!regex_match(strChangePercentage, number)){
        cout << "Invalid Input. Please enter a valid number." << el;
        cout << "-------------------------------------" << el;
        return getPercentage();
    }

    // Validate change percentage value
    double changePercentage = stod(strChangePercentage);
    if (changePercentage < -100 || changePercentage > 100){
        cout << "Invalid Input. Please enter a number within the range -100 and 100." << el;
        cout << "-------------------------------------" << el;
        return getPercentage();
    }

    return changePercentage;
}

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

// Contrast
int contrastConfiguration(){
    // Get new contrast value
    cout << "Please enter a contrast value between -255 and 255 (+ve mean to increase contrast and -ve to decrease contrast):" << el;
    string strContrast;
    getline(cin, strContrast);

    // Validate integer input
    if (!isInteger(strContrast)){
        cout << "Invalid Input. Please enter a valid integer." << el;
        cout << "-------------------------------------" << el;
        return contrastConfiguration();
    }

    // Validate contrast value
    int contrast = stoi(strContrast);
    if (contrast < -255 || contrast > 255){
        cout << "Invalid Input. Please enter an integer within the range -255 and 255." << el;
        cout << "-------------------------------------" << el;
        return contrastConfiguration();
    }

    return contrast;
}

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