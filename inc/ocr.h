#ifndef OCR_H
#define OCR_H

//Includes
#include <vector>
#include <string>
#include "image.h"

class OCR {
public:
	//Constructors
	OCR();
	OCR(Image image);

	//Destructor
	~OCR();
	
	//Functions
float avgInt(Image im);//Finds the average intensity of an image
char charComp(Image im);//compares an image to a reference library of characters and outputs the matching character
void charCrop(Image im, std::vector<std::vector<char> > &charVec);//takes 30x56 segments of the image and compares to a reference library, stores characters in a 2d vector. 
const char *getReference;

private:
	const char *reference;

	//Functions

};

#endif	//OCR_H
