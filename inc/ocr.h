#ifndef OCR_H
#define OCR_H

//Includes
#include <string>
#include <vector>
#include "image.h"

class OCR {
public:
	//Constructors
	OCR(Image input);

	//Destructor
	~OCR();
	
	//Functions
	std::string recognize();

private:
	//Variables
	const float *intensities;
	const Image reference;
	std::vector<Image> refImages;
	Image image;
	
	//Functions
	float averageIntensity(Image croppedImage);
	std::vector<Image> cropCharImages(Image input);
	char imageToChar(Image croppedImage);
	int countBlackPixels(Image input);
	char printChar(int i);
};

#endif	//OCR_H
