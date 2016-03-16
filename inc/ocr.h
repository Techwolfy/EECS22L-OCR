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
    const Image reference;
  	std::vector<Image> refImages;
	  Image image;
	
	//Functions
    std::vector<Image> cropCharImages(Image input);
    char imageToChar(Image croppedImage);
    int countBlackPixels(Image input);
    char printChar(int index);
    Image imagePosition(Image im);
};

#endif	//OCR_H
