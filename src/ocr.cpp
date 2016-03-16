//OCR.cpp

//Includes
#include <string>
#include <vector>
#include <gdkmm/pixbuf.h>
#include "image.h"
#include "ocr.h"

//Include numeric constants and reference image resource

#include "couriernew.pixbuf"

//Constructor
OCR::OCR(Image input) : reference(Gdk::Pixbuf::create_from_inline(sizeof(couriernew_pixbuf), couriernew_pixbuf)),
						image(input) {
	refImages = cropCharImages(reference);
}

//Desrtructor
OCR::~OCR() {

}

//Functions

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
      Image resultant = imagePosition(charImage);
			images.push_back(resultant);
		}
	}

	return images;
}

//Compares an image to a reference library of characters and outputs the matching character 
char OCR::imageToChar(Image croppedImage) {
	char output = ' ';
	int same = 0, most = 0;
    for(int refIndex = 0; refIndex < refImages.size(); refIndex++) {
        for(int i = 0; i < croppedImage.getHeight(); i++) {
            for(int j = 0; j < croppedImage.getWidth(); j++){
			    if(abs(croppedImage.getPixel(j, i, Image::R) - refImages[refIndex].getPixel(j, i, Image::R)) < 100){
				      same++;							       
          }
          else{
              same--;
          }
			}  
		}  
		if(same > most) {
			most = same;
			output = printChar(refIndex);      
		}
     same = 0;
	}

	  return output;
}


//Map reference image index to character
char OCR::printChar(int index) {
	if(index >= 0 && index <= 25) {
		return 'a' + index;
	} else if(index >= 26 && index <= 51) {
		return 'A' + (index - 32);
  }  else if (index = 58) {
    return ' ';
	} else if(index >= 64 && index <= 72) {
		return '1' + (index - 64);
	} else if(index == 73) {
		return '0';
	} else {
		switch(index) {
			case 96:
				return '~';
        break;
			case 97:
				return '!';
        break;
			case 98:
				return '@';
        break;
			case 99:
				return '#';
        break;
			case 100:
				return '$';
        break;
			case 101:
				return '%';
        break;
			case 102:
				return '^';
        break;
			case 103:
				return '&';
        break;
			case 104:
				return '*';
        break;
			case 105:
				return '(';
        break;
			case 106:
				return ')';
        break;
			case 107:
				return '_';
        break;
			case 108:
				return '+';
        break;
			case 109:
				return '`';
        break;
			case 110:
				return '-';
        break;
			case 111:
				return '=';
        break;
			case 112:
				return '{';
        break;
			case 113:
				return '}';
        break;
			case 114:
				return '|';
        break;
			case 115:
				return '[';
        break;
			case 116:
				return ']';
        break;
			case 117:
				return '\\';
        break;
			case 118:
				return ':';
        break;
			case 119:
				return '"';
        break;
			case 120:
				return '<';
        break;
			case 121:
				return '>';
        break;
			case 122:
				return '?';
        break;
			case 123:
				return ';';
        break;
			case 124:
				return '\'';
        break;
			case 125:
				return ',';
        break;
			case 126:
				return '.';
        break;
			case 127:
				return '/';
        break;
			default:
				return ' ';
		}
	}
}
Image OCR::imagePosition(Image im){//repositions image to top left corner by setting topmost black pixel to row 0 and leftmost black pixel to col 0
    int top = 0,left = 0;
    Image resultant(30, 56);
	for(int i = 0; i < im.getHeight(); i++) {
	    for(int j = 0; j < im.getWidth(); j++) {
	        if((im.getPixel(j, i, Image::R) + im.getPixel(j, i, Image::G) + im.getPixel(j, i, Image::B))/3 < 5){
                top = i;
	            break;
            }
        }
        if(top != 0){
          break;
		}
	}
    for(int j = 0; j < im.getWidth(); j++) {
	    for(int i = 0; i < im.getHeight(); i++) {
	        if((im.getPixel(j, i, Image::R) + im.getPixel(j, i, Image::G) + im.getPixel(j, i, Image::B))/3 < 5){
                left = j;
	            break;
            }
        }
        if(left != 0){
          break;
		}
	}
	for(int i = 0; i < resultant.getHeight(); i++) {
	    for(int j = 0; j < resultant.getWidth(); j++) {
	        if((j + left) >= im.getWidth() || (i + top) >= im.getHeight()){
			        resultant.setPixel(j, i, Image::R, 255);
              resultant.setPixel(j, i, Image::G, 255);
              resultant.setPixel(j, i, Image::B, 255);
            }
            else{
              resultant.setPixel(j, i, Image::R, im.getPixel(j + left, i + top, Image::R));
	            resultant.setPixel(j, i, Image::G, im.getPixel(j + left, i + top, Image::G));
	            resultant.setPixel(j, i, Image::B, im.getPixel(j + left, i + top, Image::B));
            }
            }
        }
    return resultant;
}