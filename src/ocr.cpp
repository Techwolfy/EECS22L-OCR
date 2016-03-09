//OCR.cpp

//Includes
#include <vector>
#include "image.h"
#include "ocr.h"

//Include numeric constants
#include "averageIntensities.h"

//Constructor
OCR::OCR() : intensities(averageIntensities) {

}

//Desrtructor
OCR::~OCR() {

}

//Functions
//Finds the average intensity of an image
float OCR::avgInt(Image image) {
	float total = 0.0;
	
	for(int i = 0; i < image.getHeight(); i++) {
		for(int j = 0; j < image.getWidth(); j++) {
			total += image.getPixel(j, i, Image::R) + image.getPixel(j, i, Image::G) + image.getPixel(j, i, Image::B);
		}
	}
	
	return total / (3 * image.getHeight() * image.getWidth());
}

//Takes 30x56 segments of the image and compares to a reference library, stores characters in a 2d vector.
void OCR::charCrop(Image image, std::vector<std::vector<unsigned char>> &charVec) {
	Image newImage(30, 56);
	std::vector<unsigned char> text;
	
	for(int i = 0; i < image.getHeight(); i += 56) {
		for(int j = 0; j < image.getWidth(); j += 30) {
			for(int m = 0; m < 56; m++){
				for(int n = 0; n < 30; n++){
					newImage.setPixel(j, i, Image::R, image.getPixel(j, i, Image::R));
					newImage.setPixel(j, i, Image::G, image.getPixel(j, i, Image::G));
					newImage.setPixel(j, i, Image::B, image.getPixel(j, i, Image::B));
				}
			}
			text.push_back(charComp(newImage));
		}
		charVec.push_back(text);
		text.clear();
	}
}

//Compares an image to a reference library of characters and outputs the matching character
char OCR::charComp(Image image) {
	char output = '\0';
	float intensity = avgInt(image);
	float difference = 0.0;
	float best = 255.0;

	for(int i = 0; i < (127 - 32); i++) {
		if(intensities[i] - intensity > 0) {
			difference = intensities[i] - intensity;
		} else {
			difference = intensity - intensities[i];
		}
		if(difference < best) {
			best = difference;
			output = i + 32;
		}
	}

	return output;
}
