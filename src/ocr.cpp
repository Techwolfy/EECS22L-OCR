//--
//OCR.cpp

//Includes
#include <string>
#include "image.h"
#include "ocr.h"

//Include numeric constants
#include "averageIntensities.h"

//Constructor
OCR::OCR(Image input) : intensities(averageIntensities),
						image(input) {

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

//Takes 30x56 segments of the image and compares to a reference library, stores characters in a 2d vector.
std::string OCR::recognize() {
	
	std::string text;
	vector<Image> img = charCrop(image);	
	int newLine = 0;
        
	Image iCourierFont(Gdk::Pixbuf::create_from_file("/users/ugrad2/2015/winter/L16T12/ocr/src/CourierNew476_bw.jpg"));
        
        vector<Image> iList = charCrop(iCourierFont);
	
	for(int i = 0; i<img.size();i++){
		text += compareChar(img.at(i), iList);
		newLine++;
		if(newLine == img.at(i).getWidth()){
			text+= "\n"; 
			newLine = 0; 
		}

	return text;
}


//-----
char OCR::printLetter(int index){ 
	if(index == 0){
		return 'a';
	}
	if(index == 1){
		return 'b';
	}
	if(index == 2){
		return 'c';
		//cout<<"c";
	}
	if(index == 3){
		return 'd';
		//cout<<"d";
	}
	if(index == 4){
		return 'e';
		//cout<<"e";
	}
	if(index == 5){
		return 'f';
		//cout<<"f";
	}
	if(index == 6){
		return 'g';
		//cout<<"g";
	}
	if(index == 7){
		return 'h';
		//cout<<"h";
	}
	if(index == 8){
		return 'i';
		//cout<<"i";
	}
	if(index == 9){
		return 'j';
		//cout<<"j";
	}
	if(index == 10){
		return 'k';
		//cout<<"k";
	}
	if(index == 11){
		return 'l';
		//cout<<"l";
	}
	if(index == 12){
		return 'm';
		//cout<<"m";
	}
	if(index == 13){
		return 'n';
		//cout<<"n";
	}
	if(index == 14){
		return 'o';
		//cout<<"o";
	}
	if(index == 15){
		return 'p';
		//cout<<"p";
	}
	if(index == 16){
		return 'q';
		//cout<<"q";
	}
	if(index == 17){
		return 'r';
		//cout<<"r";
	}
	if(index == 18){
		return 's';
		//cout<<"s";
	}
	if(index == 19){
		return 't';
		//cout<<"t";
	}
	if(index == 20){
		return 'u';
		//cout<<"u";
	}
	if(index == 21){
		return 'v';
		//cout<<"v";
	}
	if(index == 22){
		return 'w';
		//cout<<"w";
	}
	if(index == 23){
		return 'x';
		//cout<<"x";
	}
	if(index == 24){
		return 'y';
		//cout<<"y";
	}
	if(index == 25){
		return 'z';
		//cout<<"z";
	}
	if(index == 26){
		return 'A';
		//cout<<"A";
	}
	if(index == 27){
		return 'B';
		//cout<<"B";
	}
	if(index == 28){
		return 'C';
		//cout<<"C";
	}
	if(index == 29){
		return 'D';
		//cout<<"D";
	}
	if(index == 30){
		return 'E';
		//cout<<"E";
	}
	if(index == 31){
		return 'F';
		//cout<<"F";
	}
	if(index == 32){
		return 'G';
		//cout<<"G";
	}
	if(index == 33){
		return 'H';
		//cout<<"H";
	}
	if(index == 34){
		return 'I';
		//cout<<"I";
	}
	if(index == 35){
		return 'J';
		//cout<<"J";
	}
	if(index == 36){
		return 'K';
		//cout<<"K";
	}
	if(index == 37){
		return 'L';
		//cout<<"L";
	}
	if(index == 38){
		return 'M';
		//cout<<"M";
	}
	if(index == 39){
		return 'N';
		//cout<<"N";
	}
	if(index == 40){
		return 'O';
		//cout<<"O";
	}
	if(index == 41){
		return 'P';
		//cout<<"P";
	}
	if(index == 42){
		return 'Q';
		//cout<<"Q";
	}
	if(index == 43){
		return 'R';
		//cout<<"R";
	}
	if(index == 44){
		return 'S';
		//cout<<"S";
	}
	if(index == 45){
		return 'T';
		//cout<<"T";
	}
	if(index == 46){
		return 'U';
		//cout<<"U";
	}
	if(index == 47){
		return 'V';
		//cout<<"V";
	}
	if(index == 48){
		return 'W';
		//cout<<"W";
	}
	if(index == 49){
		return 'X';
		//cout<<"X";
	}
	if(index == 50){
		return 'Y';
		//cout<<"Y";
	}
	if(index == 51){
		return 'Z';
		//cout<<"Z";
	}
	if(index == 52){
		return '1';
		//cout<<"1";
	}
	if(index == 53){
		return '2';
		//cout<<"2";
	}
	if(index == 54){
		return '3';
		//cout<<"3";
	}
	if(index == 55){
		return '4';
		//cout<<"4";
	}
	if(index == 56){
		return '5';
		//cout<<"5";
	}
	if(index == 57){
		return '6';
		//cout<<"6";
	}
	if(index == 58){
		return '7';
		//cout<<"7";
	}
	if(index == 59){
		return '8';
		//cout<<"8";
	}
	if(index == 60){
		return '9';
		//cout<<"9";
	}
	if(index == 61){
		return '0';
		//cout<<"0";
	}
	if(index == 62){
		return '~';
		//cout<<"~";
	}
	if(index == 63){
		return '!';
		//cout<<"!";
	}
	if(index == 64){
		return '@';
		//cout<<"@";
	}
	if(index == 65){
		return '#';
		//cout<<"#";
	}
	if(index == 66){
		return '$';
		//cout<<"$";
	}
	if(index == 67){
		return '%';
		//cout<<"%";
	}
	if(index == 68){
		return '^';
		//cout<<"^";
	}
	if(index == 69){
		return '&';
		//cout<<"&";
	}
	if(index == 70){
		return '*';
		//cout<<"*";
	}
	if(index == 71){
		return '(';
		//cout<<"(";
	}
	if(index == 72){
		return ')';
		//cout<<")";
	}
	if(index == 73){
		return '_';
		//cout<<"_";
	}
	if(index == 74){
		return '+';
		//cout<<"+";
	}
	if(index == 75){
		return '-';
		//cout<<"-";
	}
	if(index == 76){
		return '=';
		//cout<<"=";
	}
	if(index == 77){
		return '{';
		//cout<<"{";
	}
	if(index == 78){
		return '}';
		//cout<<"}";
	}
	if(index == 79){
		return '|';
		//cout<<"|";
	}
	if(index == 80){
		return '[';
		//cout<<"[";
	}
	if(index == 81){
		return ']';
		//cout<<"]";
	}
	if(index == 82){
		return '\\';
		//cout<<"\\";
	}
	if(index == 83){
		return ':';
		//cout<<":";
	}
	if(index == 84){
		return '"';
		//cout<<'"';
	}
	if(index == 85){
		return '<';
		//cout<<"<";
	}
	if(index == 86){
		return '>';
		//cout<<">";
	}
	if(index == 87){
		return '?';
		//cout<<"?";
	}
	if(index == 88){
		return ';';
		//cout<<";";
	}
	if(index == 89){
		return '7' + 32;
		//cout<<"'";
	}
	if(index == 90){
		return ',';
		//cout<<",";
	}
	if(index == 90){
		return '.';
		//cout<<".";
	}
	if (index == 91)
	{
		return '/';
		//cout<<"/";
	}
	else{
		return ' ';
	}
}
//Compares an image to a reference library of characters and outputs the matching character
char OCR::compareChar(Image croppedImage, vector<Image> iList) {
	int imgH = croppedImage.getHeight();
	int imgW = croppedImage.getWidth();
	int countBP1 = 0;
	int countBP2 = 0;
	int countBP3 = 0;
	int refIndex = 0;
	Image iRef;
	//count black pixels of input image
	for(int x=0; x<imgH; x++){
		for(int y = 0; y<imgW; y++){
			if(croppedImage.getPixel(y, x, Image::R) == 0 && croppedImage.getPixel(y, x, Image::G) == 0 && croppedImage.getPixel(y, x, Image::B) == 0){
				countBP1++;
			}
		}
	}
	//read first image of vector iList and assign to iRef
	iRef = iList.at(0);
	//count black pixels of reference image
	for(int i = 0; i < iRef.getHeight(); i++){
		for(int j = 0; j < iRef.getWidth(); j++){
			if(iRef.getPixel(j, i, Image::R) == 0 && iRef.getPixel(j, i, Image::G) == 0 && iRef.getPixel(j, i, Image::B) == 0){
				countBP2++;
			}
		}
	}
	
	int currDiff = 0;
	int bestDiff = countBP2 - countBP1;
	//loop through each reference image in iList
	for(int k = 1; k < iList.size(); k++){
		//read second image of vector iList and assign to iRef
		iRef = iList.at(k);
		//count black pixels of reference image
		for(int m = 0; m < iRef.getHeight(); m++){
			for(int n = 0; n < iRef.getWidth(); n++){
				//get R,G,B values of reference image and check if its a black pixel
				if(iRef.getPixel(n, m, Image::R) == 0 && iRef.getPixel(n, m, Image::G) == 0 && iRef.getPixel(n, m, Image::B) == 0){
					countBP3++; //increment black pixel count
				}
			}
		}
		//compare black pixel count of input image to reference image
		//
		currDiff = countBP3 - countBP1;
		if( abs(currDiff) < abs(bestDiff)  ){
			refIndex = k;
			bestDiff = currDiff;
			
		}
		//reset count for next reference image
		countBP3 = 0;
	}
	return(printLetter(refIndex));
}

//character cropping function 
vector<Image> OCR::charCrop(Image img){ 
	int wImg = img.getWidth();
	int hImg = img.getHeight();
	
	vector<Image> imgList;
	for(int i = 0; i < hImg; i += 56) {
		for(int j = 0; j < wImg; j += 30) {
			Image imge(30, 56);
			for(int m = 0; m < 56; m++){
				for(int n = 0; n < 30; n++){
					imge.setPixel( n, m, Image::R, img.getPixel(j+n, i+m, Image::R));
					imge.setPixel( n, m, Image::G, img.getPixel(j+n, i+m, Image::G));
					imge.setPixel( n, m, Image::B, img.getPixel(j+n, i+m, Image::B));
				}
			}
			imgList.push_back(imge);
		}
	}
	return imgList;
}
