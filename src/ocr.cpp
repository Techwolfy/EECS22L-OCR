//OCR.cpp

//Includes
#include <vector>
#include <string>
#include "image.h"
#include "ocr.h"
#include <fstream>
#include <iostream>

//Constructor
OCR::OCR(){
//reference = #include "averageIntensities.txt";
}

//Desrtructor
OCR::~OCR(){

}

//Functions

void OCR::charCrop(Image im, std::vector<std::vector<char> > &charVec){

  Image newImage(30,56);
  std::vector<char> text;
  
  for(int i=0; i<im.getHeight(); i+=56){
    for(int j=0;j<im.getWidth(); j+=30){
      for(int m=0;m<56;m++){
        for(int n=0;n<30;n++){
          newImage.setPixel(j,i,Image::R, im.getPixel(j,i,Image::R));
          newImage.setPixel(j,i,Image::G, im.getPixel(j,i,Image::G));
          newImage.setPixel(j,i,Image::B, im.getPixel(j,i,Image::B));
        }
      }
          text.push_back(charComp(newImage));
    }
    charVec.push_back(text);
    text.clear();
  }
}

char OCR::charComp(Image im){

  char output;
  float intensity;
  float refInt, difference, best=255.0;
  std::string line, value;
  intensity = avgInt(im); 
  std::ifstream reference ("../inc/averageIntensities.txt");
  if(reference.is_open()){
   while(getline (reference,line)){
   value = line.substr(0,7);
   refInt = atof(value.c_str());
   difference = (refInt-intensity> 0) ? (refInt-intensity) : (intensity - refInt);
   std::cout << difference;
   if(difference < best) {
     best = difference;
     output = line[7];
   }
     }
     reference.close();
   }
   return output;
 }
 
float OCR::avgInt(Image im){

  float total = 0.0;
  int i,j;
  
  for(i=0; i<im.getHeight(); i++){
    for(j=0;j<im.getWidth();j++){
      total +=  im.getPixel(j,i,Image::R)+ im.getPixel(j,i,Image::G) + im.getPixel(j,i,Image::B);
    }
  }
  
  return total/(3*1680.0);
}

const char *getReference() {
  //return reference;
}
