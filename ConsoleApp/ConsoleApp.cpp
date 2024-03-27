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

// Darken and Lighten Image
void darkFilter(Image &image);
void lightFilter(Image &image);

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

        int intChoice;
        string choice;
        cin >> choice;
        cin.clear();
        cin.ignore();

        if (isInteger(choice)) {
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
    return 0;
}

// General Helper Functions
Image imageInput() {
    // Input prompt
    cout << "Insert an image name with the extension (.g img.png)" << el
         << "Allowed extensions are .png, .bmp, .tga, .jpg" << el;

    // Initialize variables
    string imageName;
    Image image;

    // Exception handling loop.
    while (true) {
        // File name input
        cin >> imageName;
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
             << "4) Merge Images" << el
             << "5) Flip Image" << el
             << "6) Rotate Image" << el
             << "7) Darken and Lighten Image" << el
             << "8) Crop Images" << el
             << "9) Adding a Frame to the Picture" << el
             << "10) Detect Image Edges" << el
             << "11) Resizing Images" << el
             << "12) Blur Images" << el
             << "13) Save current Image" << el
             << "14) Return to previous menu" << el;

        int intChoice;
        string choice;
        cin >> choice;
        cin.clear();
        cin.ignore();

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
                
                int intFlipChoice;
                string flipChoice;
                cin >> flipChoice;
                cin.clear();
                cin.ignore();

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
                     << "1) 90°" << el
                     << "2) 180°" << el
                     << "3) 270°" << el;

                int rotationChoice;
                cin >> rotationChoice;
                cin.clear();
                cin.ignore();

                switch (rotationChoice) {
                    case 1: {
                        rotate90(image);
                        image.loadNewImage("temp.png", 0);
                        break;
                    }
                    case 2: {
                        // 180
                        break;
                    }
                    case 3: {
                        // 270
                        break;
                    }
                    default: {
                        cout << "Invalid choice. Returning to main menu..." << el;
                        break;
                    }
                }
                break;
            }
            case 7: {
                cout << "Please select one of the following choices:" << el
                     << "1) Darken Image" << el
                     << "2) Lighten Image" << el;

                int intDarkorLightChoice;
                string DarkorLightChoice;
                cin >> DarkorLightChoice;
                cin.clear();
                cin.ignore();

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
                // Aِdding a Frame to the Picture
                break;
            }
            case 10: {
                // Detect Image Edges
                break;
            }
            case 11: {
                // Resizing Images
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
                cout << "Returning to previous menu... " << el;
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

string saveImage(Image &image) {
    // New file name input
    cout << "Enter the name of the new image with the extension (e.g img.png):" << el;

    string saveName;
    cin >> saveName;

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
    string imgName; cin >> imgName;
    Image imageToMegre(imgName);

    unsigned int merge = 0;

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
