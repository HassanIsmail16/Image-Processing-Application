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
    Momen Abd El-Kader: Exception Handling, Copy Image Function, Input Validation, Black and White Filter, Flip Image Filter, Resize Filter.
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

// Frame Filter
pair <int, vector <int>> frameConfiguration(Image &image);
int frameSizeConfiguration(Image &image);
vector <int> frameColorConfiguration(Image &image);
bool hexCodeValidation(string hexCode);
int hexConversion(string code);
void frameFilter(Image &image, pair <int, vector <int>> configuration);

// Edge Filter
void edgeFilter(Image &image);

// Resize Images
void resizeImage(Image &image, int newWidth, int newHeight);

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

        // Input
        int intChoice;
        string choice;

        // Input validation
        getline(cin, choice);
        if (isInteger(choice) && (stoi(choice) == 1 || stoi(choice) == 2)) {
            intChoice = stoi(choice);
        } else {
            cout << "Invalid Choice. Please select 1 or 2..." << el;
            cout << "-------------------------------------" << el;
            continue;
        }

        switch (intChoice) {
            case 1:
                filterSelection();
                break;
            case 2:
                cout << "Exiting the program..." << el;
                return 0;
            default:
                cout << "Invalid Choice. Please select 1 or 2..." << el;
                cout << "-------------------------------------" << el;
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
             << "8) Crop Images" << "(NOT ADDED YET)" << space << el
             << "9) Adding a Frame to the Picture" << el
             << "10) Detect Image Edges" << el
             << "11) Resizing Images" << el
             << "12) Blur Images" << space << "(NOT ADDED YET)" << el
             << "13) Save current Image" << el
             << "14) Return to previous menu" << el;

        // Input
        int intChoice;
        string choice;
        getline(cin, choice);

        // Input validation
        if (isInteger(choice)) {
            intChoice = stoi(choice);
        } else {
            cout << "Invalid Choice. Please select 1 or 2..." << el;
            cout << "-------------------------------------" << el;
            continue;
        }

        switch (intChoice) {
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
                int intFlipChoice;
                string flipChoice;
                getline(cin, flipChoice);

                // Input validation
                if (isInteger(flipChoice)){
                    intFlipChoice = stoi(flipChoice);
                } else {
                    cout << "Invalid Choice. Please select 1 or 2..." << el;
                    cout << "-------------------------------------" << el;
                    break;
                }

                switch (intFlipChoice) {
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
                int intRotationChoice;
                string rotationChoice;
                getline(cin, rotationChoice);

                // Input validation
                if (isInteger(rotationChoice) && stoi(rotationChoice) >= 1 && stoi(rotationChoice) <= 3) {
                    intRotationChoice = stoi(rotationChoice);
                } else {
                    cout << "Invalid input. Please select an integer between 1 and 3..." << el;
                    cout << "-------------------------------------" << el;
                    continue;
                }

                switch (intRotationChoice) {
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
                        break;
                }
                break;
            }
            case 7: {
                cout << "Please select one of the following choices:" << el
                     << "1) Darken Image" << el
                     << "2) Lighten Image" << el;

                // Input
                int intDarkorLightChoice;
                string DarkorLightChoice;
                getline(cin, DarkorLightChoice);

                // Input validation
                if (isInteger(DarkorLightChoice)){
                    intDarkorLightChoice = stoi(DarkorLightChoice);
                } else {
                    cout << "Invalid Choice. Please select 1 or 2..." << el;
                    cout << "-------------------------------------" << el;
                    break;
                }

                switch (intDarkorLightChoice) {
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
                // Crop Images
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
                regex validDimensions(R"((\d+)\s[*xX]\s(\d+))");
                smatch matches;
                cout << "Please enter the new dimensions in the format width * height (e.g. 1920 * 1080 or 1920 x 1080)" << el;

                // Input
                string dimensions;
                getline(cin, dimensions);

                // Input validation
                if (regex_match(dimensions, matches, validDimensions)){
                    int newWidth = stoi(matches[1]);
                    int newHeight = stoi(matches[2]);
                    resizeImage(image, newWidth, newHeight);
                } else{
                    cout << "Invalid Dimensions. Please enter the new dimensions in the format width * height (e.g. 1920 * 1080 or 1920 x 1080)." << el;
                    cout << "-------------------------------------" << el;
                }
                break;
            }
            case 12: {
                // Blur Images
                break;
            }
            case 13: {
                saveImage(image);
                loopStatus = false;
                break;
            }
            case 14: {
                if (returnMenu() == 1) {
                    saveImage(image);
                } else {
                    cout << "Returning to previous menu... " << el;
                }
                loopStatus = false;
                break;
            }
            default: {
                cout << "Invalid Choice. Please select a number between 1 & 8..." << el;
                cout << "-------------------------------------" << el;
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
    string choice;
    int intChoice;
    getline(cin, choice);

    // Choice validation
    if (isInteger(choice) && (stoi(choice) == 1 || stoi(choice) == 2)) {
        intChoice = stoi(choice);
        return intChoice;
    } else {
        cout << "Invalid Choice. Please select 1 or 2..." << el;
        cout << "-------------------------------------" << el;
        return returnMenu();
    }
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

void copyImage(Image &source, Image &destination){
    for (int i = 0; i < destination.width; ++i) {
        for (int j = 0; j < destination.height; ++j) {
            for (int k = 0; k < destination.channels; ++k) {
                destination(i, j, k) = source(i, j, k);
            }
        }
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
    Image copy(image.width, image.height);
    copyImage(image, copy);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = copy(image.width - 1 - i, j, k);
            }
        }
    }
}

void flipImageVertically(Image &image){
    Image copy(image.width, image.height);
    copyImage(image, copy);

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
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
    if (isInteger(frameSize)) {
        intFrameSize = stoi(frameSize);
        if (intFrameSize > 0) {
            if (intFrameSize <= min(image.width, image.height) / 2) {
                return intFrameSize;
            } else {
                cout << "Invalid input (MAXIMUM SIZE IS " << min(image.width, image.height) / 2 << "px)." << el;
                return frameSizeConfiguration(image);
            }
        } else {
            cout << "Invalid input (NEGATIVE INTEGER)." << el;
            return frameSizeConfiguration(image);
        }
    } else {
        cout << "Invalid input (NOT AN INTEGER)." << el;
        return frameSizeConfiguration(image);
    }
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

    string colorChoice;
    int intColorChoice;

    getline(cin, colorChoice);

    // Choice validation
    if (isInteger(colorChoice) && stoi(colorChoice) > 0 && stoi(colorChoice) < 9) {
        intColorChoice = stoi(colorChoice);
    } else {
        cout << "Invalid choice. Please select an integer between 1 and 8 (inclusive)." << el;
        return frameColorConfiguration(image);
    }

    vector <int> color;
    switch (intColorChoice) {
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