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
	char charComp(Image image);
	void charCrop(Image image, std::vector<std::vector<unsigned char>> &charVec);

private:
	//Variables
	const float *intensities;

	//Functions
	float avgInt(Image image);
};

#endif	//OCR_H
