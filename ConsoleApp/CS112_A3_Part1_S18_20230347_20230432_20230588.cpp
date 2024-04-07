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
    Hassan Ali:         Main Menu, Image Input Function, Image Save Function, Filter Selection Function, Invert Image Filter, Image Rotation Filters, Frame Filter.
    Momen Abd El-Kader: Exception Handling, Copy Image Function, Input Validation, Black and White Filter, Flip Image Filter, Crop Filter, Resize Filter.
    Mohamed Ali:        Grayscale Filter, Merge Image Filter (INCOMPLETE), Lighten & Darken Image Filters, Edge Detection Filter.
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
void mergeFilter(Image &image);

// Flip Image
void flipImageHorizontally(Image &image);
void flipImageVertically(Image &image);

// Image Rotation
void rotate90(Image &image);
void rotate180(Image &image);
void rotate270(Image &image);

// Darken and Lighten Image
void darkFilter(Image &image);
void lightFilter(Image &image);

// Crop Images
pair <int, int> coordinatesInput(Image &image);
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
pair <int, int> dimensionsInput();
void resizeImage(Image &image, int newWidth, int newHeight);

// Blur Filter
double getGaussianKernelSize(Image &image);
double getGaussianStandardDeviation(double kernelSize);
double gaussianModel(double x, double y, double variance);
vector<vector<double>> constructGaussianKernel(double kernelSize, double standardDeviation);
double getConvolutedCell(int value, int kernelX, int kernelY, const vector<vector<double>> &gaussianKernel);
Image kernelConvolution(Image &image, double kernelSize, const vector<vector<double>>& gaussianKernel);
void gaussianBlur(Image &image);

// Purple Filter
void purpleFilter(Image &image);

// Infrared Filter
void infraredFilter(Image &image);

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
             << "4) Merge Images" << space << "(NOT COMPLETE)" << el
             << "5) Flip Image" << el
             << "6) Rotate Image" << el
             << "7) Darken and Lighten Image" << el
             << "8) Crop Image" << el
             << "9) Adding a Frame to the Picture" << el
             << "10) Detect Image Edges" << el
             << "11) Resize Image" << el
             << "12) Blur Image" << el
             << "13) Make image warmer (Land of Wano)" << el
             << "14) Apply The Oil Painting Effect" << el
             << "15) CRT Filter (TV Effect)" << el
             << "16) Purple Overlay" << el
             << "17) Infrared Filter" << el
             << "18) Skew Image" << el
             << "19) Saturate Image" << el
             << "20) Decrease Image Opacity" << el
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
                mergeFilter(image);
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
                cout << "Please select one of the following choices:" << el
                     << "1) Darken Image" << el
                     << "2) Lighten Image" << el;

                // Input
                int darkOrLightChoice = choiceSelection({1, 2});

                switch (darkOrLightChoice) {
                    case 1:
                        darkFilter(image);
                        break;
                    case 2:
                        lightFilter(image);
                        break;
                    default:
                        cout << "Invalid Choice. Please select 1 or 2..." << el;
                        cout << "-------------------------------------" << el;
                        break;
                }
                break;
            }
            case 8: {
                // Input coordinates
                cout << "Current image dimensions: " << image.width << " x " << image.height << el;
                pair <int, int> coordinates = coordinatesInput(image);

                // Calculate crop bounderies
                int horizontalBound = image.width - coordinates.first + 1;
                int verticalBound = image.height - coordinates.second + 1;

                // Input crop dimensions
                cout << "Maximum crop dimensions: " << horizontalBound << " x " << verticalBound << el;
                pair <int, int> dimensions = dimensionsInput();

                // Validate the dimensions according to the bounderies
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
                // Warmer Image Land of Wano
                break;
            }
            case 14: {
                // Oil Painting
                break;
            }
            case 15: {
                // CRT Filter TV Effect
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
                // Skew Image
                break;
            }
            case 19: {
                // Saturation
                break;
            }
            case 20: {
                // Transparency
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
                cout << "Invalid choice. Please select a number between 1 and 14 (inclusive)..." << el;
                break;
            }
        }
    }
}

bool isInteger(const string& input){
    regex integer(R"(\d+)");
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

            // If the greyscale intensity is closer to black back the pixel black, otherwise make it white.
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
void mergeFilter(Image &image) {
    cout << "Insert a second image to merge" << el;
    Image imageToMegre = imageInput();

    unsigned int merge = 0;

    // Averages each two corresponding pixels from the two images
    if (image.width == imageToMegre.width && image.height == imageToMegre.height) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    merge = image(i, j, k) + imageToMegre(i, j, k);
                    image(i, j, k) = merge / 2;
                }
                merge = 0;
            }
        }
    } else {
        cout << "Please resize the images to merge." << el;
        return;
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
            // fill the image from buttom to top.
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
void darkFilter(Image &image) {
    int dark;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                dark = image(i, j, k);
                if (image(i, j, k) > dark / 2)
                    image(i, j, k) -= dark / 2;
                else
                    image(i, j, k) = 0;
            }
        }
    }
}

void lightFilter(Image &image){
    int light;

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                light = image(i, j, k);
                if(image(i,j,k) + (light / 2) < 255)
                    image(i, j, k) += light / 2;
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
    for (int reulstRow = 0, imageRow = coordinates.first - 1; reulstRow < result.width; ++reulstRow, ++imageRow) {
        for (int resultCol = 0, imageCol = coordinates.second - 1; resultCol < result.height; ++resultCol, ++imageCol) {
            // Traverse through original image pixels starting from the coordinates and assing them to the result.
            for (int channel = 0; channel < result.channels; ++channel) {
                result(reulstRow, resultCol, channel) = image(imageRow, imageCol, channel);
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
        cout << "Invalid Coordinates. Plase enter coordinates inside the bounds of the image." << el;
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
            // Map each pixel in the resized image to its nearest neighboor in the original image.
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

// Purple Filter
void purpleFilter(Image &image){
    // Iterate over each pixel
    for(int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Add a constant value to red and blue values
            for (int k = 0; k < 3; ++k) {
                if (k == 1)
                    continue;
                if (image(i, j, k) + 55 < 255) {  // 50
                    image(i, j, k) += 55;
                } else
                    image(i, j, k) = 255;
            }
            // Reduce the light in the image
            for (int k = 0; k < 3; ++k) {
                if(image(i,j,k) - 35 > 0) // 40
                    image(i,j,k) -= 35;
                else
                    image(i,j,k) = 0;
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
                //Resverse the value of the image
                image(i, j, k) = -(image(i,j,k) - 255);
            }
        }
    }
}
