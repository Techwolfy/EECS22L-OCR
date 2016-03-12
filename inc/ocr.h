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
	std::string recognize();

private:
	//Variables
	const float *intensities;
	Image image;
	
	//Functions
	float averageIntensity(Image croppedImage);
	char compareChar(Image croppedImage, std::vector<Image> iRefList);
	std::vector<Image> charCrop(Image image);
	char printLetter(int i);

};

#endif	//OCR_H
