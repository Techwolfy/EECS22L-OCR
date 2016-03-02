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
float avgInt(IMAGE im);//Finds the average intensity of an image
char charComp(IMAGE im);//compares an image to a reference library of characters and outputs the matching character
void charCrop(IMAGE im, vector<vector<char> > &charVec);//takes 30x56 segments of the image and compares to a reference library, stores characters in a 2d vector. 

private:
	//Variables

	//Functions

};

#endif	//OCR_H
