//OCR.cpp

//Includes
#include <string>
#include <vector>
#include <gdkmm/pixbuf.h>
#include "image.h"
#include "ocr.h"

//Include numeric constants and reference image resource
#include "averageIntensities.h"
#include "couriernew.pixbuf"

//Constructor
OCR::OCR(Image input) : intensities(averageIntensities),
						reference(Gdk::Pixbuf::create_from_inline(sizeof(couriernew_pixbuf), couriernew_pixbuf)),
						image(input) {
	refImages = cropCharImages(reference);
}

//Desrtructor
OCR::~OCR() {

}

//Functions
//Finds the average intensity of an image
float OCR::averageIntensity(Image croppedImage) {
	float total = 0.0;
	
	for(int i = 0; i < croppedImage.getHeight(); i++) {
		for(int j = 0; j < croppedImage.getWidth(); j++) {
			total += croppedImage.getPixel(j, i, Image::R) + croppedImage.getPixel(j, i, Image::G) + croppedImage.getPixel(j, i, Image::B);
		}
	}
	
	return total / (3 * croppedImage.getHeight() * croppedImage.getWidth());
}


//Takes 30x56 segments of the image and compares to a reference library
std::string OCR::recognize() {
	std::string text;
	std::vector<Image> charImages = cropCharImages(image);
	int newLine = 0; 	

	for(int i = 0; i < charImages.size(); i++) {
		text += imageToChar(charImages.at(i));
		newLine++;
		if(newLine == charImages.at(i).getWidth()) {
			text += "\n";
			newLine = 0;
		}
	}

	return text;
}

//Character cropping function 
std::vector<Image> OCR::cropCharImages(Image input) {
	std::vector<Image> images;

	for(int i = 0; i < input.getHeight(); i += 56) {
		for(int j = 0; j < input.getWidth(); j += 30) {
			Image charImage(30, 56);
			for(int m = 0; m < 56; m++) {
				for(int n = 0; n < 30; n++) {
					charImage.setPixel(n, m, Image::R, input.getPixel(j + n, i + m, Image::R));
					charImage.setPixel(n, m, Image::G, input.getPixel(j + n, i + m, Image::G));
					charImage.setPixel(n, m, Image::B, input.getPixel(j + n, i + m, Image::B));
				}
			}
			images.push_back(charImage);
		}
	}

	return images;
}

//Compares an image to a reference library of characters and outputs the matching character 
char OCR::imageToChar(Image croppedImage) {
	int inputBP = countBlackPixels(croppedImage); //Count black pixels of input image
	int refIndex = -1;	//Default to an invalid value, which translates to ' '
	int currDiff = 0;
	int bestDiff = abs(countBlackPixels(refImages[0]) - inputBP);

	for(int i = 1; i < refImages.size(); i++) {
		//Compare black pixel count of input image to reference image
		currDiff = abs(countBlackPixels(refImages.at(i)) - inputBP);
		if(currDiff < bestDiff) {
			bestDiff = currDiff;
			refIndex = i;
		}
	}

	return printChar(refIndex);
}

//Count the number of black pixels in an image
int OCR::countBlackPixels(Image input) {
	int count = 0;

	for(int x = 0; x < input.getHeight(); x++) {
		for(int y = 0; y < input.getWidth(); y++) {
			if(input.getPixel(x, y, Image::R) == 0 && input.getPixel(x, y, Image::G) == 0 && input.getPixel(x, y, Image::B) == 0) {
				count++;
			}
		}
	}

	return count;
}

//Map reference image index to character
char OCR::printChar(int index) {
	if(index >= 0 && index <= 25) {
		return 'a' + index;
	} else if(index >= 26 && index <= 51) {
		return 'A' + (index - 26);
	} else if(index >= 52 && index <= 60) {
		return '1' + (index - 52);
	} else if(index == 61) {
		return '0';
	} else {
		switch(index) {
			case 62:
				return '~';
			case 63:
				return '!';
			case 64:
				return '@';
			case 65:
				return '#';
			case 66:
				return '$';
			case 67:
				return '%';
			case 68:
				return '^';
			case 69:
				return '&';
			case 70:
				return '*';
			case 71:
				return '(';
			case 72:
				return ')';
			case 73:
				return '_';
			case 74:
				return '+';
			case 75:
				return '`';
			case 76:
				return '-';
			case 77:
				return '=';
			case 78:
				return '{';
			case 79:
				return '}';
			case 80:
				return '|';
			case 81:
				return '[';
			case 82:
				return ']';
			case 83:
				return '\\';
			case 84:
				return ':';
			case 85:
				return '"';
			case 86:
				return '<';
			case 87:
				return '>';
			case 88:
				return '?';
			case 89:
				return ';';
			case 90:
				return '\'';
			case 91:
				return ',';
			case 92:
				return '.';
			case 93:
				return '/';
			default:
				return ' ';
		}
	}
}
