#include <bits/stdc++.h>
#include "../../Image_Class.h"
#define el '\n'
#define space ' '

using namespace std;

/*
- Image (class)  `Image varName("image.png")` for loading images
- `image.saveImage("newFilename.png")` for saving images
- `image(x, y, channel)` for accessing RGB values
- `Image varName(width, height)` for creating a blank image of width x height
- `varName.loadNewImage("image.png")` to load an image into a blank image
- `.loadNewImage()` and `.saveImage()` can also return booleans
- `varName.setPixel(x, y, channel, value)`
- `varName.getPixel(x, y, channel) = value`
- `varName.width`, `varName.height`, `varName.channels`
 */


// General Functions
void filterSelection();
string saveImage(Image &image);
Image imageInput();

// GrayScale Filtering
void GSfilter(Image &image);

// Image Inversion
void invertImage(Image &image);

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

        int choice;
        cin >> choice;
        cin.clear();
        cin.ignore();

        switch (choice) {
            case 1:
                filterSelection();
                break;
            case 2:
                cout << "Exiting the program..." << el;
                return 0;
            default:
                cout << "Invalid Choice. Please select 1 or 2..." << el;
        }
    }
    return 0;
}

// General Helper Functions
Image imageInput() {
    // File name input
    cout << "Insert an image name with the extension (.g img.png)" << el
         << "Allowed extensions are .png, .bmp, .tga, .jpg" << el;

    string imageName;
    cin >> imageName;

    // Main image loading
    Image image(imageName);
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
             << "4) Merge Images" << el
             << "5) Flip Image" << el
             << "6) Rotate Image" << el
             << "7) Save current Image" << el
             << "8) Return to previous menu" << el;

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                GSfilter(image);
                break;
            }
            case 2: {
                // B&W Filter
                break;
            }
            case 3: {
                invertImage(image);
                break;
            }
            case 4: {
                // Merge Filter
                break;
            }
            case 5: {
                // Flip Filter
                break;
            }
            case 6: {
                // Rotation Filter
                break;
            }
            case 7: {
                saveImage(image);
                loopStatus = false;
                break;
            }
            case 8: {
                cout << "Returning to previous menu... " << el;
                loopStatus = false;
                break;
            }
            default: {
                cout << "Invalid Choice. Please select a number between 1 & 8..." << el;
            }
        }
    }
}

string saveImage(Image &image) {
    // New file name input
    cout << "Enter the name of the new image with the extension (e.g img.png): ";

    string saveName;
    cin >> saveName;

    // Image saving
    image.saveImage(saveName);

    return "Save Current";
}

// GrayScale Filter
void GSfilter(Image &image){
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

// Image Inversion Filter
void invertImage(Image &image) {
    for (int x = 0; x < image.width; x++) {
        for (int y = 0; y < image.height; y++) {
            for (int channel = 0; channel < image.channels; channel++) {
                image(x, y, channel) = 255 - image(x, y, channel);
            }
        }
    }
}