#ifndef OCR_H
#define OCR_H

//Includes
#include <string>
#include "image.h"

class OCR {
public:
	//Constructors
	OCR(Image input);

	//Destructor
	~OCR();
	
	//Functions
	std::vector<Image> charCrop(Image image);
	char printLetter(int i);
	Image readImage(const char fname[80]);
	std::string recognize();

private:
	//Variables
	const float *intensities;
	Image image;

	//Functions
	float averageIntensity(Image croppedImage);
	char compareChar(Image croppedImage, std::vector<Image> iRefList);
};

#endif	//OCR_H
